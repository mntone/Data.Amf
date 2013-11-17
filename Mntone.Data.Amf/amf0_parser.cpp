#include "pch.h"
#include "amf_exception.h"
#include "amf0_parser.h"
#include "amf0_type.h"
#include "amf3_parser.h"
#include "AmfValue.h"
#include "AmfArray.h"
#include "AmfObject.h"

using namespace mntone::data::amf;
using namespace Mntone::Data::Amf;

IAmfValue^ amf0_parser::parse( const Platform::Array<uint8>^ input )
{
	uint8* ptr( input->Data );
	size_t length( input->Length );
	try
	{
#if _DEBUG
		return safe_cast<IAmfValue^>( ( ref new amf0_parser() )->parse_value( ptr, length ) );
#else
		return safe_cast<IAmfValue^>( amf0_parser().parse_value( ptr, length ) );
#endif
	}
	catch( const amf_exception& ex )
	{
		throw ref new Platform::FailureException( ex.get_message() );
	}
}

bool amf0_parser::try_parse( const Platform::Array<uint8>^ input, IAmfValue^* result )
{
	uint8* ptr( input->Data );
	size_t length( input->Length );
	try
	{
#if _DEBUG
		*result = safe_cast<IAmfValue^>( ( ref new amf0_parser() )->parse_value( ptr, length ) );
#else
		*result = safe_cast<IAmfValue^>( amf0_parser().parse_value( ptr, length ) );
#endif
	}
	catch( const amf_exception& /*ex*/ ) { return false; }
	return true;
}

amf0_parser::amf0_parser( void )
{ }

IAmfValue^ amf0_parser::parse_value( uint8*& input, size_t& length )
{
	if( length < 1 )
		throw amf_exception( "Invalid data." );

	const auto type = input[0];
	++input;
	--length;

	switch( type )
	{
	case amf0_type::amf0_number: return parse_number( input, length );
	case amf0_type::amf0_boolean: return parse_boolean( input, length );
	case amf0_type::amf0_string: return parse_string( input, length );
	case amf0_type::amf0_object: return parse_object( input, length );
	case amf0_type::amf0_null: return parse_null( input, length );
	case amf0_type::amf0_undefined: return parse_undefined( input, length );
	case amf0_type::amf0_reference: return parse_reference( input, length );
	case amf0_type::amf0_ecma_array: return parse_ecma_array( input, length );
	case amf0_type::amf0_strict_array: return parse_strict_array( input, length );
	case amf0_type::amf0_date: return parse_date( input, length );
	case amf0_type::amf0_long_string: return parse_long_string( input, length );
	case amf0_type::amf0_xml_document: return parse_xml_document( input, length );
	case amf0_type::amf0_typed_object: return parse_typed_object( input, length );
	case amf0_type::amf0_avmplus_object: return parse_avmplus_object( input, length );
	case amf0_type::_amf0_flexible_array: return parse_flexible_array( input, length );
	default: throw amf_exception( "Invalid type." );
	}
}

IAmfValue^ amf0_parser::parse_number( uint8*& input, size_t& length )
{
	if( length < 8 )
		throw amf_exception( "Invalid number." );

	float64 data;
	utilities::convert_big_endian( input, &data, 8 );
	input += 8;
	length -= 8;

	return AmfValue::CreateNumberValue( data );
}

IAmfValue^ amf0_parser::parse_boolean( uint8*& input, size_t& length )
{
	if( length < 1 )
		throw amf_exception( "Invalid boolean." );

	auto data = input[0] != 0 ? true : false;
	input += 1;
	length -= 1;

	return AmfValue::CreateBooleanValue( data );
}

IAmfValue^ amf0_parser::parse_null( uint8*& /*input*/, size_t& /*length*/ )
{
	return ref new AmfValue();
}

IAmfValue^ amf0_parser::parse_undefined( uint8*& /*input*/, size_t& /*length*/ )
{
	return AmfValue::CreateUndefinedValue();
}

IAmfValue^ amf0_parser::parse_reference( uint8*& input, size_t& length )
{
	if( length < 2 )
		throw amf_exception( "Invalid reference." );

	uint16 data( 0 );
	utilities::convert_big_endian( input, &data, 2 );
	input += 2;
	length -= 2;

	if( data >= reference_buffer_.size() )
		throw amf_exception( "Invalid reference." );

	return reference_buffer_[data];
}

IAmfValue^ amf0_parser::parse_date( uint8*& input, size_t& length )
{
	if( length < 10 )
		throw amf_exception( "Invalid date." );

	float64 data( 0.0 );
	utilities::convert_big_endian( input, &data, 8 );
	input += 10;
	length -= 10;

	return AmfValue::CreateDateValue( utilities::unix_time_to_date_time( static_cast<uint64>( data ) ) );
}

IAmfValue^ amf0_parser::parse_string( uint8*& input, size_t& length )
{
	return AmfValue::CreateStringValue( parse_utf8( input, length ) );
}

IAmfValue^ amf0_parser::parse_long_string( uint8*& input, size_t& length )
{
	return AmfValue::CreateStringValue( parse_utf8_long( input, length ) );
}

IAmfValue^ amf0_parser::parse_xml_document( uint8*& input, size_t& length )
{
	return AmfValue::CreateXmlValue( parse_utf8_long( input, length ) );
}

IAmfValue^ amf0_parser::parse_strict_array( uint8*& input, size_t& length )
{
	if( length < 4 )
		throw amf_exception( "Invalid strictArray." );

	const auto& out = ref new AmfArray();
	reference_buffer_.push_back( out );

	uint32 arrayCount( 0 );
	utilities::convert_big_endian( input, &arrayCount, 4 );
	input += 4;
	length -= 4;

	std::vector<IAmfValue^> data( arrayCount );
	for( size_t i = 0u; i < arrayCount; ++i )
		data[i] = parse_value( input, length );

	out->SetData( std::move( data ) );
	return out;
}

IAmfValue^ amf0_parser::parse_flexible_array( uint8*& input, size_t& length )
{
	// *Prop (min 0) | Utf8-empty (U16) | Object-end-maker (U8 = 0x09) -> min 3 bytes
	if( length < 3 )
		throw amf_exception( "Invalid flexibleArray." );

	std::vector<IAmfValue^> data;
	while( length >= 3 && ( input[0] != 0x00 || input[1] != 0x00 || input[2] != 0x09 ) )
		data.emplace_back( parse_value( input, length ) );

	if( length < 3 || input[0] != 0x00 || input[1] != 0x00 || input[2] != 0x09 )
		throw amf_exception( "Invalid flexibleArray." );

	input += 3;
	length -= 3;

	const auto& out = ref new AmfArray();
	out->SetData( std::move( data ) );
	return out;
}

IAmfValue^ amf0_parser::parse_object( uint8*& input, size_t& length )
{
	// Utf8-empty (U16) | Object-end-maker (U8 = 0x09) -> min 3 bytes
	if( length < 3 )
		throw amf_exception( "Invalid object." );

	const auto& out = ref new AmfObject();
	reference_buffer_.push_back( out );

	const auto& data = parse_object_base( input, length );
	out->SetData( std::move( data ) );
	return out;
}

IAmfValue^ amf0_parser::parse_ecma_array( uint8*& input, size_t& length )
{
	// associative_count (U32) | Utf8-empty (U16) | Object-end-maker (U8 = 0x09) -> min 7 bytes
	if( length < 7 )
		throw amf_exception( "Invalid ecmaArray." );

	const auto& out = AmfObject::CreateEcmaArray();
	reference_buffer_.push_back( out );

	//uint32 associative_count( 0 );
	//utilities::convert_big_endian( input, &associative_count, 4 );
	input += 4;
	length -= 4;

	const auto& data = parse_object_base( input, length );
	out->SetData( std::move( data ) );
	return out;
}

IAmfValue^ amf0_parser::parse_typed_object( uint8*& input, size_t& length )
{
	// ClassName (min U16+U8) | Utf8-empty (U16) | Object-end-maker (U8 = 0x09) -> min 6 bytes
	if( length < 6 )
		throw amf_exception( "Invalid typedObject." );

	const auto& class_name = parse_utf8( input, length );
	const auto& out = ref new AmfObject( class_name );
	reference_buffer_.push_back( out );

	const auto& data = parse_object_base( input, length );
	out->SetData( std::move( data ) );
	return out;
}

std::map<Platform::String^, IAmfValue^> amf0_parser::parse_object_base( uint8*& input, size_t& length )
{
	std::map<Platform::String^, IAmfValue^> data;
	while( length >= 3 && ( input[0] != 0x00 || input[1] != 0x00 || input[2] != 0x09 ) )
	{
		const auto& prop = parse_property( input, length );
		data.emplace( std::move( prop ) );
	}

	if( length < 3 || input[0] != 0x00 || input[1] != 0x00 || input[2] != 0x09 )
		throw amf_exception( "Invalid object." );

	input += 3;
	length -= 3;
	return std::move( data );
}

std::pair<Platform::String^, IAmfValue^> amf0_parser::parse_property( uint8*& input, size_t& length )
{
	const auto& key = parse_utf8( input, length );
	const auto& value = parse_value( input, length );
	return std::make_pair( std::move( key ), std::move( value ) );
}

IAmfValue^ amf0_parser::parse_avmplus_object( uint8*& input, size_t& length )
{
#if _DEBUG
	return ( ref new amf3_parser() )->parse_value( input, length );
#else
	return amf3_parser().parse_value( input, length );
#endif
}

Platform::String^ amf0_parser::parse_utf8( uint8*& input, size_t& length )
{
	if( length < 2 )
		throw amf_exception( "Invalid string." );

	uint32 text_length( 0 );
	utilities::convert_big_endian( input, &text_length, 2 );
	input += 2;
	length -= 2;

	return parse_utf8_base( input, length, text_length );
}

Platform::String^ amf0_parser::parse_utf8_long( uint8*& input, size_t& length )
{
	if( length < 4 )
		throw amf_exception( "Invalid string." );

	uint32 text_length( 0 );
	utilities::convert_big_endian( input, &text_length, 4 );
	input += 4;
	length -= 4;

	return parse_utf8_base( input, length, text_length );
}

Platform::String^ amf0_parser::parse_utf8_base( uint8*& input, size_t& length, const size_t text_length )
{
	if( text_length == 0 )
		return "";

	if( length < text_length )
		throw amf_exception( "Invalid string." );

	std::ostringstream buf;
	buf.write( reinterpret_cast<char*>( input ), text_length );
	input += text_length;
	length -= text_length;
	return utilities::char_utf8_to_platform_string( buf.str() );
}