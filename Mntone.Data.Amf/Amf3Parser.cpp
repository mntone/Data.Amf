#include "pch.h"
#include "Amf3Parser.h"
#include "AmfValue.h"
#include "AmfArray.h"
#include "AmfObject.h"
#include "amf3_type.h"

using namespace Mntone::Data::Amf;

IAmfValue^ Amf3Parser::Parse( const Platform::Array<uint8>^ input )
{
	uint8* ptr( input->Data );
	size_t length( input->Length );
	return safe_cast<IAmfValue^>( ( ref new Amf3Parser() )->ParseValue( ptr, length ) );
}

bool Amf3Parser::TryParse( const Platform::Array<uint8>^ input, IAmfValue^* result )
{
	try { *result = Parse( input ); }
	catch( Platform::FailureException^ ) { return false; }
	catch( Platform::InvalidCastException^ ) { return false; }
	return true;
}

Amf3Parser::Amf3Parser( void )
{ }

IAmfValue^ Amf3Parser::ParseValue( uint8*& input, size_t& length )
{
	if( length < 1 )
		throw ref new Platform::FailureException( "Invalid data." );

	const auto type = input[0];
	++input;
	--length;

	switch( type )
	{
	case amf3_type::amf3_undefined: return ParseUndefined( input, length );
	case amf3_type::amf3_null: return ParseNull( input, length );
	case amf3_type::amf3_false: return ParseFalse( input, length );
	case amf3_type::amf3_true: return ParseTrue( input, length );
	case amf3_type::amf3_interger: return ParseInteger( input, length );
	case amf3_type::amf3_double: return ParseDouble( input, length );
	case amf3_type::amf3_string: return ParseString( input, length );
	case amf3_type::amf3_xml_document:
	case amf3_type::amf3_xml:
		return ParseXml( input, length );
	case amf3_type::amf3_date: return ParseDate( input, length );
	case amf3_type::amf3_array: return ParseArray( input, length );
	case amf3_type::amf3_object: return ParseObject( input, length );
	case amf3_type::amf3_byte_array: return ParseByteArray( input, length );
	case amf3_type::amf3_vector_int: return ParseVectorInt( input, length );
	case amf3_type::amf3_vector_uint: return ParseVectorUint( input, length );
	case amf3_type::amf3_vector_double: return ParseVectorDouble( input, length );
	case amf3_type::amf3_vector_object: return ParseVectorObject( input, length );
	//case amf3_type::amf3_dictionary: return ParseDictionary( input, length );
	default: throw ref new Platform::FailureException( "Invalid type." );
	}
}

IAmfValue^ Amf3Parser::ParseUndefined( uint8*& /*input*/, size_t& /*length*/ )
{
	return AmfValue::CreateUndefinedValue();
}

IAmfValue^ Amf3Parser::ParseNull( uint8*& /*input*/, size_t& /*length*/ )
{
	return ref new AmfValue();
}

IAmfValue^ Amf3Parser::ParseFalse( uint8*& /*input*/, size_t& /*length*/ )
{
	return AmfValue::CreateBooleanValue( false );
}

IAmfValue^ Amf3Parser::ParseTrue( uint8*& /*input*/, size_t& /*length*/ )
{
	return AmfValue::CreateBooleanValue( true );
}

IAmfValue^ Amf3Parser::ParseInteger( uint8*& input, size_t& length )
{
	const auto& data = ParseUnsigned29bitInteger( input, length );
	return AmfValue::CreateIntegerValue( data );
}

IAmfValue^ Amf3Parser::ParseDouble( uint8*& input, size_t& length )
{
	if( length < 8 )
		throw ref new Platform::FailureException( "Invalid double." );

	float64 data;
	ConvertBigEndian( input, &data, 8 );
	input += 8;
	length -= 8;

	return AmfValue::CreateDoubleValue( data );
}

IAmfValue^ Amf3Parser::ParseString( uint8*& input, size_t& length )
{
	return AmfValue::CreateStringValue( ParseStringBase( input, length ) );
}

Platform::String^ Amf3Parser::ParseStringBase( uint8*& input, size_t& length )
{
	const auto& value = ParseUnsigned29bitInteger( input, length );
	if( ( value & 1 ) == 0 )
	{
		const auto& ref = value >> 1;
		if( ref >= stringReferenceBuffer_.size() )
			throw ref new Platform::OutOfBoundsException();
		return stringReferenceBuffer_[ref];
	}

	const auto& textLength = value >> 1;
	if( textLength == 0 )
		return "";

	if( length < textLength )
		throw ref new Platform::FailureException( "Invalid string." );

	std::stringstream buf;
	buf.write( reinterpret_cast<char*>( input ), textLength );
	input += textLength;
	length -= textLength;

	const auto& str = CharUtf8ToPlatformString( buf.str() );
	stringReferenceBuffer_.push_back( str );
	return str;
}

IAmfValue^ Amf3Parser::ParseXml( uint8*& input, size_t& length )
{
	const auto& value = ParseUnsigned29bitInteger( input, length );
	if( ( value & 1 ) == 0 )
		return GetObject( value );

	const auto& textLength = value >> 1;
	const auto& xml = AmfValue::CreateXmlValue( ParseUtf8( input, length, textLength ) );
	objectReferenceBuffer_.push_back( xml );
	return xml;
}

IAmfValue^ Amf3Parser::ParseDate( uint8*& input, size_t& length )
{
	const auto& value = ParseUnsigned29bitInteger( input, length );
	if( ( value & 1 ) == 0 )
		return GetObject( value );

	if( length < 8 )
		throw ref new Platform::FailureException( "Invalid date." );

	float64 data( 0.0 );
	ConvertBigEndian( input, &data, 8 );
	input += 8;
	length -= 8;

	const auto& date = AmfValue::CreateDateValue( UnixTimeToDateTime( static_cast<uint64>( data ) ) );
	objectReferenceBuffer_.push_back( date );
	return date;
}

IAmfValue^ Amf3Parser::ParseArray( uint8*& input, size_t& length )
{
	const auto& value = ParseUnsigned29bitInteger( input, length );
	if( ( value & 1 ) == 0 )
		return GetObject( value );

	AmfObject^ obj;
#if _WINDOWS_PHONE
	std::map<Platform::String^, IAmfValue^> map;
#else
	std::unordered_map<Platform::String^, IAmfValue^> map;
#endif

	const auto& count = value >> 1;
	while( length > 0 )
	{
		const auto& key = ParseStringBase( input, length );
		if( key->Length() == 0 )
			break;

		if( obj == nullptr )
		{
			obj = AmfObject::CreateEcmaArray();
			objectReferenceBuffer_.push_back( obj );
		}
		const auto& value = ParseValue( input, length );
		map.emplace( key, value );
	}

	if( obj != nullptr )
	{
		for( size_t i = 0; i < count; ++i )
			map.emplace( i.ToString(), ParseValue( input, length ) );

		obj->SetData( std::move( map ) );
		return obj;
	}

	// dense array only
	const auto& ary = ref new AmfArray();
	objectReferenceBuffer_.push_back( ary );

	std::vector<IAmfValue^> vector( count );
	for( size_t i = 0; i < count; ++i )
		vector[i] = ParseValue( input, length );

	ary->SetData( std::move( vector ) );
	return ary;
}

IAmfValue^ Amf3Parser::ParseObject( uint8*& input, size_t& length )
{
	const auto& value = ParseUnsigned29bitInteger( input, length );
	if( ( value & 1 ) == 0 )
		return GetObject( value );

	std::shared_ptr<amf3_traits_info> info;
	if( ( value & 3 ) == 1 )
	{
		const auto& traitsRef = value >> 2;
		if( traitsRef >= traitsInfoBuffer_.size() )
			throw ref new Platform::OutOfBoundsException();
		info = traitsInfoBuffer_[traitsRef];
	}
	else
	{
		info = std::make_shared<amf3_traits_info>();
		info->externalizable = ( value & 4 ) == 4;
		info->dynamic = ( value & 8 ) == 8;
		info->class_name = ParseStringBase( input, length );

		const auto& count = value >> 4;
		for( size_t i = 0; i < count; ++i )
			info->properites.push_back( ParseStringBase( input, length ) );

		traitsInfoBuffer_.push_back( info );
	}

	AmfObject^ obj;
	if( info->class_name->Length() != 0 )
	{
		obj = ref new AmfObject( info->class_name );
		obj->Externalizable = true;
	}
	else
		obj = ref new AmfObject();
	objectReferenceBuffer_.push_back( obj );

#if _WINDOWS_PHONE
	std::map<Platform::String^, IAmfValue^> map;
#else
	std::unordered_map<Platform::String^, IAmfValue^> map;
#endif
	for( const auto& key : info->properites )
		map.emplace( key, ParseValue( input, length ) );

	if( info->dynamic )
	{
		while( length > 0 )
		{
			const auto& key = ParseStringBase( input, length );
			if( key->Length() == 0 )
				break;

			const auto& value = ParseValue( input, length );
			map.emplace( key, value );
		}
	}

	obj->SetData( std::move( map ) );
	return obj;
}

IAmfValue^ Amf3Parser::ParseByteArray( uint8*& input, size_t& length )
{
	const auto& value = ParseUnsigned29bitInteger( input, length );
	if( ( value & 1 ) == 0 )
		return GetObject( value );

	const size_t& arrayLength = value >> 1;
	std::vector<uint8> data( arrayLength );
	memcpy( data.data(), input, arrayLength );

	input += arrayLength;
	length -= arrayLength;

	const auto& ba = AmfValue::CreateByteArrayValue( std::move( data ) );
	objectReferenceBuffer_.push_back( ba );
	return ba;
}

IAmfValue^ Amf3Parser::ParseVectorInt( uint8*& input, size_t& length )
{
	const auto& value = ParseUnsigned29bitInteger( input, length );
	if( ( value & 1 ) == 0 )
		return GetObject( value );

	const size_t& arrayLength = value >> 1;
	const auto& vector = ParseVectorBase<int32>( input, length, arrayLength );
	const auto& vi = AmfValue::CreateVectorIntValue( ref new Platform::Collections::Vector<int32>( std::move( vector ) ) );
	objectReferenceBuffer_.push_back( vi );
	return vi;
}

IAmfValue^ Amf3Parser::ParseVectorUint( uint8*& input, size_t& length )
{
	const auto& value = ParseUnsigned29bitInteger( input, length );
	if( ( value & 1 ) == 0 )
		return GetObject( value );

	const size_t& arrayLength = value >> 1;
	const auto& vector = ParseVectorBase<uint32>( input, length, arrayLength );
	const auto& vu = AmfValue::CreateVectorUintValue( ref new Platform::Collections::Vector<uint32>( std::move( vector ) ) );
	objectReferenceBuffer_.push_back( vu );
	return vu;
}

IAmfValue^ Amf3Parser::ParseVectorDouble( uint8*& input, size_t& length )
{
	const auto& value = ParseUnsigned29bitInteger( input, length );
	if( ( value & 1 ) == 0 )
		return GetObject( value );

	const size_t& arrayLength = value >> 1;
	const auto& vector = ParseVectorBase<float64>( input, length, arrayLength );
	const auto& vd = AmfValue::CreateVectorDoubleValue( ref new Platform::Collections::Vector<float64>( std::move( vector ) ) );
	objectReferenceBuffer_.push_back( vd );
	return vd;
}

template<typename T>
std::vector<T> Amf3Parser::ParseVectorBase( uint8*& input, size_t& length, const size_t arrayLength )
{
	//const auto& fixed = *value;
	input += 1;
	length -= 1;

	const auto& size = sizeof( T );
	std::vector<T> vector( arrayLength );
	for( size_t i = 0; i < arrayLength; ++i, input += size, length -= size )
	{
		T data;
		ConvertBigEndian( input, &data, size );
		vector[i] = data;
	} 

	return std::move( vector );
}

IAmfValue^ Amf3Parser::ParseVectorObject( uint8*& input, size_t& length )
{
	const auto& value = ParseUnsigned29bitInteger( input, length );
	if( ( value & 1 ) == 0 )
		return GetObject( value );

	const auto& vo = AmfValue::CreateVectorObjectValue();
	objectReferenceBuffer_.push_back( vo );

	//const auto& fixed = *value;
	input += 1;
	length -= 1;

	/*const auto& typeName =*/ ParseStringBase( input, length );

	const size_t& arrayLength = value >> 1;
	std::vector<IAmfValue^> vector( arrayLength );
	for( size_t i = 0; i < arrayLength; ++i )
		vector[i] = ParseValue( input, length );

	vo->SetData( ref new Platform::Collections::Vector<IAmfValue^>( std::move( vector ) ) );
	return vo;
}

Platform::String^ Amf3Parser::ParseUtf8( uint8*& input, size_t& length, const uint32 textLength )
{
	if( textLength == 0 )
		return "";

	if( length < textLength )
		throw ref new Platform::FailureException( "Invalid utf8." );

	std::stringstream buf;
	buf.write( reinterpret_cast<char*>( input ), textLength );
	input += textLength;
	length -= textLength;

	return CharUtf8ToPlatformString( buf.str() );
}

uint32 Amf3Parser::ParseUnsigned29bitInteger( uint8*& input, size_t& length )
{
	if( length == 0 )
		throw ref new Platform::FailureException( "Invalid unsigned 29-bit integer." );

	uint32 ret = input[0] & 0x7f;
	if( input[0] <= 0x7f )
	{
		input += 1;
		length -= 1;
		return ret;
	}

	if( length == 1 )
		throw ref new Platform::FailureException( "Invalid unsigned 29-bit integer." );

	ret = ( ret << 7 ) | ( input[1] & 0x7f );
	if( input[1] <= 0x7f )
	{
		input += 2;
		length -= 2;
		return ret;
	}

	if( length == 2 )
		throw ref new Platform::FailureException( "Invalid unsigned 29-bit integer." );

	ret = ( ret << 7 ) | ( input[2] & 0x7f );
	if( input[2] <= 0x7f )
	{
		input += 3;
		length -= 3;
		return ret;
	}

	if( length == 3 )
		throw ref new Platform::FailureException( "Invalid unsigned 29-bit integer." );

	ret = ( ret << 8 ) | input[3];
	input += 4;
	length -= 4;
	return ret;
}

IAmfValue^ Amf3Parser::GetObject( const size_t input )
{
	const auto& ref = input >> 1;
	if( ref >= objectReferenceBuffer_.size() )
		throw ref new Platform::OutOfBoundsException();
	return objectReferenceBuffer_[ref];
}