#include "pch.h"
#include "Amf0Parser.h"
#include "AmfValue.h"
#include "AmfArray.h"
#include "AmfObject.h"
#include "amf0_type.h"

using namespace Mntone::Data::Amf;

IAmfValue^ Amf0Parser::Parse( const Platform::Array<uint8>^ input )
{
	uint8 *ptr( input->Data );
	uint32 length( input->Length );
	return ParseValue( ptr, length );
}

bool Amf0Parser::TryParse( const Platform::Array<uint8>^ input, IAmfValue^* result )
{
	try { *result = Parse( input ); }
	catch( Platform::FailureException^ ) { return false; }
	catch( Platform::InvalidCastException^ ) { return false; }
	return true;
}

IAmfValue^ Amf0Parser::ParseValue( uint8*& input, uint32& length )
{
	if( length < 1 )
		throw ref new Platform::FailureException( "Invalid data." );

	auto type = input[0];
	++input;
	--length;

	switch( type )
	{
	case amf0_type::amf0_number: return ParseNumber( input, length );
	case amf0_type::amf0_boolean: return ParseBoolean( input, length );
	case amf0_type::amf0_string: return ParseString( input, length );
	case amf0_type::amf0_object: return ParseObject( input, length );
	case amf0_type::amf0_null: return ParseNull( input, length );
	case amf0_type::amf0_undefined: return ParseUndefined( input, length );
	case amf0_type::amf0_reference: return ParseReference( input, length );
	case amf0_type::amf0_ecma_array: return ParseEcmaArray( input, length );
	case amf0_type::amf0_strict_array: return ParseStrictArray( input, length );
	case amf0_type::amf0_date: return ParseDate( input, length );
	case amf0_type::amf0_long_string: return ParseLongString( input, length );
	case amf0_type::amf0_xml_document: return ParseXmlDocument( input, length );
	case amf0_type::amf0_typed_object: return ParseTypedObject( input, length );
	case amf0_type::_amf0_flexible_array: return ParseFlexibleArray( input, length );
	default: throw ref new Platform::FailureException( "Invalid type." );
	}
}

IAmfValue^ Amf0Parser::ParseNumber( uint8*& input, uint32& length )
{
	if( length < 8 )
		throw ref new Platform::FailureException( "Invalid number." );

	float64 data;
	ConvertBigEndian( input, &data, 8 );
	input += 8;
	length -= 8;

	return AmfValue::CreateDoubleValue( data );
}

IAmfValue^ Amf0Parser::ParseBoolean( uint8*& input, uint32& length )
{
	if( length < 1 )
		throw ref new Platform::FailureException( "Invalid boolean." );

	auto data = input[0] != 0 ? true : false;
	input += 1;
	length -= 1;

	return AmfValue::CreateBooleanValue( data );
}

IAmfValue^ Amf0Parser::ParseNull( uint8*& /*input*/, uint32& /*length*/ )
{
	return ref new AmfValue();
}

IAmfValue^ Amf0Parser::ParseUndefined( uint8*& /*input*/, uint32& /*length*/ )
{
	return AmfValue::CreateUndefinedValue();
}

IAmfValue^ Amf0Parser::ParseReference( uint8*& input, uint32& length )
{
	if( length < 2 )
		throw ref new Platform::FailureException( "Invalid reference." );

	uint16 data;
	ConvertBigEndian( input, &data, 2 );
	input += 2;
	length -= 2;

	return AmfValue::CreateReferenceValue( data );
}

IAmfValue^ Amf0Parser::ParseStrictArray( uint8*& input, uint32& length )
{
	if( length < 4 )
		throw ref new Platform::FailureException( "Invalid strictArray." );

	uint32 count;
	ConvertBigEndian( input, &count, 4 );
	input += 4;
	length -= 4;

	std::vector<IAmfValue^> data;
	for( auto i = 0u; i < count; ++i )
		data.emplace_back( ParseValue( input, length ) );

	return ref new AmfArray( std::move( data ) );
}

IAmfValue^ Amf0Parser::ParseDate( uint8*& input, uint32& length )
{
	if( length < 10 )
		throw ref new Platform::FailureException( "Invalid date." );

	float64 data;
	ConvertBigEndian( input, &data, 8 );
	input += 10;
	length -= 10;

	return AmfValue::CreateDateValue( UnixTimeToDateTime( static_cast<uint64>( data ) ) );
}

IAmfValue^ Amf0Parser::ParseString( uint8*& input, uint32& length )
{
	return AmfValue::CreateStringValue( ParseUtf8( input, length ) );
}

IAmfValue^ Amf0Parser::ParseLongString( uint8*& input, uint32& length )
{
	return AmfValue::CreateStringValue( ParseUtf8Long( input, length ) );
}

IAmfValue^ Amf0Parser::ParseXmlDocument( uint8*& input, uint32& length )
{
	return AmfValue::CreateXmlValue( ParseUtf8Long( input, length ) );
}

IAmfValue^ Amf0Parser::ParseFlexibleArray( uint8*& input, uint32& length )
{
	// *Prop (min 0) | Utf8-empty (U16) | Object-end-maker (U8 = 0x09) -> min 3 bytes
	if( length < 3 )
		throw ref new Platform::FailureException( "Invalid flexibleArray." );

	std::vector<IAmfValue^> data;
	while( length >= 3 && ( input[0] != 0x00 || input[1] != 0x00 || input[2] != 0x09 ) )
		data.emplace_back( ParseValue( input, length ) );

	if( length < 3 || input[0] != 0x00 || input[1] != 0x00 || input[2] != 0x09 )
		throw ref new Platform::FailureException( "Invalid flexibleArray." );

	input += 3;
	length -= 3;

	return ref new AmfArray( std::move( data ) );
}

Platform::String^ Amf0Parser::ParseUtf8( uint8*& input, uint32& length )
{
	if( length < 2 )
		throw ref new Platform::FailureException( "Invalid string." );

	uint32 textLength( 0 );
	ConvertBigEndian( input, &textLength, 2 );
	input += 2;
	length -= 2;

	return ParseUtf8Base( input, length, textLength );
}

Platform::String^ Amf0Parser::ParseUtf8Long( uint8*& input, uint32& length )
{
	if( length < 4 )
		throw ref new Platform::FailureException( "Invalid string." );

	uint32 textLength( 0 );
	ConvertBigEndian( input, &textLength, 4 );
	input += 4;
	length -= 4;

	return ParseUtf8Base( input, length, textLength );
}

Platform::String^ Amf0Parser::ParseUtf8Base( uint8*& input, uint32& length, const uint32 textLength )
{
	if( textLength == 0 )
		return "";

	if( length < textLength )
		throw ref new Platform::FailureException( "Invalid string." );

	std::stringstream buf;
	buf.write( reinterpret_cast<char*>( input ), textLength );
	input += textLength;
	length -= textLength;
	return CharUtf8ToPlatformString( buf.str() );
}

IAmfValue^ Amf0Parser::ParseObject( uint8*& input, uint32& length )
{
	// *Prop (min 0) | Utf8-empty (U16) | Object-end-maker (U8 = 0x09) -> min 3 bytes
	if( length < 3 )
		throw ref new Platform::FailureException( "Invalid object." );

	const auto& data = ParseObjectBase( input, length );
	return ref new AmfObject( std::move( data ) );
}

IAmfValue^ Amf0Parser::ParseEcmaArray( uint8*& input, uint32& length )
{
	// associativeCount (U32) | Utf8-empty (U16) | Object-end-maker (U8 = 0x09) -> min 7 bytes
	if( length < 7 )
		throw ref new Platform::FailureException( "Invalid ecmaArray." );

	uint32 associativeCount( 0 );
	ConvertBigEndian( input, &associativeCount, 4 );
	input += 4;
	length -= 4;

	const auto& data = ParseObjectBase( input, length );
	return AmfObject::CreateEcmaArray( associativeCount, std::move( data ) );
}

IAmfValue^ Amf0Parser::ParseTypedObject( uint8*& input, uint32& length )
{
	// ClassName (min U16+U8) | Utf8-empty (U16) | Object-end-maker (U8 = 0x09) -> min 6 bytes
	if( length < 6 )
		throw ref new Platform::FailureException( "Invalid typedObject." );

	const auto& className = ParseUtf8( input, length );
	const auto& data = ParseObjectBase( input, length );
	return AmfObject::CreateTypedObject( className, std::move( data ) );
}

std::map<Platform::String^, IAmfValue^> Amf0Parser::ParseObjectBase( uint8*& input, uint32& length )
{
	std::map<Platform::String^, IAmfValue^> data;
	while( length >= 3 && ( input[0] != 0x00 || input[1] != 0x00 || input[2] != 0x09 ) )
	{
		const auto& prop = ParseProperty( input, length );
		data.emplace( std::move( prop ) );
	}

	if( length < 3 || input[0] != 0x00 || input[1] != 0x00 || input[2] != 0x09 )
		throw ref new Platform::FailureException( "Invalid object." );

	input += 3;
	length -= 3;
	return std::move( data );
}

std::pair<Platform::String^, IAmfValue^> Amf0Parser::ParseProperty( uint8*& input, uint32& length )
{
	const auto& key = ParseUtf8( input, length );
	const auto& value = ParseValue( input, length );
	return std::make_pair( std::move( key ), std::move( value ) );
}