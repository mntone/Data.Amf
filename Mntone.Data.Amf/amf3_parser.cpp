#include "pch.h"
#include "amf_exception.h"
#include "amf3_parser.h"
#include "amf3_type.h"
#include "AmfValue.h"
#include "AmfArray.h"
#include "AmfObject.h"

using namespace mntone::data::amf;
using namespace Mntone::Data::Amf;

IAmfValue^ amf3_parser::parse( const Platform::Array<uint8>^ input )
{
	uint8* ptr( input->Data );
	size_t length( input->Length );
	try
	{
#if _DEBUG
		return safe_cast<IAmfValue^>( ( ref new amf3_parser() )->parse_value( ptr, length ) );
#else
		return safe_cast<IAmfValue^>( amf3_parser().parse_value( ptr, length ) );
#endif
	}
	catch( const amf_exception& ex )
	{
		throw ref new Platform::FailureException( ex.get_message() );
	}
}

bool amf3_parser::try_parse( const Platform::Array<uint8>^ input, IAmfValue^* result )
{
	uint8* ptr( input->Data );
	size_t length( input->Length );
	try
	{
#if _DEBUG
		*result = safe_cast<IAmfValue^>( ( ref new amf3_parser() )->parse_value( ptr, length ) );
#else
		*result = safe_cast<IAmfValue^>( amf3_parser().parse_value( ptr, length ) );
#endif
	}
	catch( const amf_exception& /*ex*/ ) { return false; }
	return true;
}

amf3_parser::amf3_parser( void )
{ }

IAmfValue^ amf3_parser::parse_value( uint8*& input, size_t& length )
{
	if( length < 1 )
		throw amf_exception( "Invalid data." );

	const auto type = input[0];
	++input;
	--length;

	switch( type )
	{
	case amf3_type::amf3_undefined: return parse_undefined( input, length );
	case amf3_type::amf3_null: return parse_null( input, length );
	case amf3_type::amf3_false: return parse_false( input, length );
	case amf3_type::amf3_true: return parse_true( input, length );
	case amf3_type::amf3_interger: return parse_integer( input, length );
	case amf3_type::amf3_double: return parse_double( input, length );
	case amf3_type::amf3_string: return parse_string( input, length );
	case amf3_type::amf3_xml_document:
	case amf3_type::amf3_xml:
		return parse_xml( input, length );
	case amf3_type::amf3_date: return parse_date( input, length );
	case amf3_type::amf3_array: return parse_array( input, length );
	case amf3_type::amf3_object: return parse_object( input, length );
	case amf3_type::amf3_byte_array: return parse_byte_array( input, length );
	case amf3_type::amf3_vector_int: return parse_vector_int( input, length );
	case amf3_type::amf3_vector_uint: return parse_vector_uint( input, length );
	case amf3_type::amf3_vector_double: return parse_vector_double( input, length );
	case amf3_type::amf3_vector_object: return parse_vector_object( input, length );
	//case amf3_type::amf3_dictionary: return ParseDictionary( input, length );
	default: throw amf_exception( "Invalid type." );
	}
}

IAmfValue^ amf3_parser::parse_undefined( uint8*& /*input*/, size_t& /*length*/ )
{
	return AmfValue::CreateUndefinedValue();
}

IAmfValue^ amf3_parser::parse_null( uint8*& /*input*/, size_t& /*length*/ )
{
	return ref new AmfValue();
}

IAmfValue^ amf3_parser::parse_false( uint8*& /*input*/, size_t& /*length*/ )
{
	return AmfValue::CreateBooleanValue( false );
}

IAmfValue^ amf3_parser::parse_true( uint8*& /*input*/, size_t& /*length*/ )
{
	return AmfValue::CreateBooleanValue( true );
}

IAmfValue^ amf3_parser::parse_integer( uint8*& input, size_t& length )
{
	const auto& data = parse_unsigned_29bit_integer( input, length );
	return AmfValue::CreateNumberValue( static_cast<float64>( static_cast<int32>( data & 0x10000000 ? 0xe0000000 | data : data ) ) );
}

IAmfValue^ amf3_parser::parse_double( uint8*& input, size_t& length )
{
	if( length < 8 )
		throw amf_exception( "Invalid double." );

	float64 data;
	utilities::convert_big_endian( input, &data, 8 );
	input += 8;
	length -= 8;

	return AmfValue::CreateNumberValue( data );
}

IAmfValue^ amf3_parser::parse_string( uint8*& input, size_t& length )
{
	return AmfValue::CreateStringValue( parse_string_base( input, length ) );
}

Platform::String^ amf3_parser::parse_string_base( uint8*& input, size_t& length )
{
	const auto& value = parse_unsigned_29bit_integer( input, length );
	if( ( value & 1 ) == 0 )
	{
		const auto& ref = value >> 1;
		if( ref >= string_reference_buffer_.size() )
			throw amf_exception( "Invalid string reference." );
		return string_reference_buffer_[ref];
	}

	const auto& text_length = value >> 1;
	if( text_length == 0 )
		return "";

	if( length < text_length )
		throw amf_exception( "Invalid string." );

	std::stringstream buf;
	buf.write( reinterpret_cast<char*>( input ), text_length );
	input += text_length;
	length -= text_length;

	const auto& str = utilities::char_utf8_to_platform_string( buf.str() );
	string_reference_buffer_.push_back( str );
	return str;
}

IAmfValue^ amf3_parser::parse_xml( uint8*& input, size_t& length )
{
	const auto& value = parse_unsigned_29bit_integer( input, length );
	if( ( value & 1 ) == 0 )
		return get_object( value );

	const auto& text_length = value >> 1;
	const auto& xml = AmfValue::CreateXmlValue( parse_utf8( input, length, text_length ) );
	object_reference_buffer_.push_back( xml );
	return xml;
}

IAmfValue^ amf3_parser::parse_date( uint8*& input, size_t& length )
{
	const auto& value = parse_unsigned_29bit_integer( input, length );
	if( ( value & 1 ) == 0 )
		return get_object( value );

	if( length < 8 )
		throw amf_exception( "Invalid date." );

	float64 data( 0.0 );
	utilities::convert_big_endian( input, &data, 8 );
	input += 8;
	length -= 8;

	const auto& date = AmfValue::CreateDateValue( utilities::unix_time_to_date_time( static_cast<uint64>( data ) ) );
	object_reference_buffer_.push_back( date );
	return date;
}

IAmfValue^ amf3_parser::parse_array( uint8*& input, size_t& length )
{
	const auto& value = parse_unsigned_29bit_integer( input, length );
	if( ( value & 1 ) == 0 )
		return get_object( value );

	AmfObject^ obj;
	std::map<Platform::String^, IAmfValue^> map;
	const auto& count = value >> 1;
	while( length > 0 )
	{
		const auto& key = parse_string_base( input, length );
		if( key->Length() == 0 )
			break;

		if( obj == nullptr )
		{
			obj = AmfObject::CreateEcmaArray();
			object_reference_buffer_.push_back( obj );
		}
		const auto& value = parse_value( input, length );
		map.emplace( key, value );
	}

	if( obj != nullptr )
	{
		for( size_t i = 0; i < count; ++i )
			map.emplace( i.ToString(), parse_value( input, length ) );

		obj->SetData( std::move( map ) );
		return obj;
	}

	// dense array only
	const auto& ary = ref new AmfArray();
	object_reference_buffer_.push_back( ary );

	std::vector<IAmfValue^> vector( count );
	for( size_t i = 0; i < count; ++i )
		vector[i] = parse_value( input, length );

	ary->SetData( std::move( vector ) );
	return ary;
}

IAmfValue^ amf3_parser::parse_object( uint8*& input, size_t& length )
{
	const auto& value = parse_unsigned_29bit_integer( input, length );
	if( ( value & 1 ) == 0 )
		return get_object( value );

	std::shared_ptr<amf3_traits_info> info;
	if( ( value & 3 ) == 1 )
	{
		const auto& traitsRef = value >> 2;
		if( traitsRef >= traits_info_buffer_.size() )
			throw amf_exception( "Invalid object." );
		info = traits_info_buffer_[traitsRef];
	}
	else
	{
		info = std::make_shared<amf3_traits_info>();
		info->externalizable = ( value & 4 ) == 4;
		info->dynamic = ( value & 8 ) == 8;
		info->class_name = parse_string_base( input, length );

		const auto& count = value >> 4;
		for( size_t i = 0; i < count; ++i )
			info->properites.push_back( parse_string_base( input, length ) );

		traits_info_buffer_.push_back( info );
	}

	AmfObject^ obj;
	if( info->class_name->Length() != 0 )
		obj = ref new AmfObject( info->class_name );
	else
		obj = ref new AmfObject();
	obj->Externalizable = info->externalizable;
	object_reference_buffer_.push_back( obj );

	std::map<Platform::String^, IAmfValue^> map;
	for( const auto& key : info->properites )
		map.emplace( key, parse_value( input, length ) );

	if( info->dynamic )
	{
		while( length > 0 )
		{
			const auto& key = parse_string_base( input, length );
			if( key->Length() == 0 )
				break;

			const auto& value = parse_value( input, length );
			map.emplace( key, value );
		}
	}

	obj->SetData( std::move( map ) );
	return obj;
}

IAmfValue^ amf3_parser::parse_byte_array( uint8*& input, size_t& length )
{
	const auto& value = parse_unsigned_29bit_integer( input, length );
	if( ( value & 1 ) == 0 )
		return get_object( value );

	const size_t& array_length = value >> 1;
	std::vector<uint8> data( array_length );
	memcpy( data.data(), input, array_length );

	input += array_length;
	length -= array_length;

	const auto& ba = AmfValue::CreateByteArrayValue( std::move( data ) );
	object_reference_buffer_.push_back( ba );
	return ba;
}

IAmfValue^ amf3_parser::parse_vector_int( uint8*& input, size_t& length )
{
	const auto& value = parse_unsigned_29bit_integer( input, length );
	if( ( value & 1 ) == 0 )
		return get_object( value );

	const size_t& array_length = value >> 1;
	const auto& vi = AmfValue::CreateVectorIntValue( parse_vector_base<int32>( input, length, array_length ) );
	object_reference_buffer_.push_back( vi );
	return vi;
}

IAmfValue^ amf3_parser::parse_vector_uint( uint8*& input, size_t& length )
{
	const auto& value = parse_unsigned_29bit_integer( input, length );
	if( ( value & 1 ) == 0 )
		return get_object( value );

	const size_t& array_length = value >> 1;
	const auto& vu = AmfValue::CreateVectorUintValue( parse_vector_base<uint32>( input, length, array_length ) );
	object_reference_buffer_.push_back( vu );
	return vu;
}

IAmfValue^ amf3_parser::parse_vector_double( uint8*& input, size_t& length )
{
	const auto& value = parse_unsigned_29bit_integer( input, length );
	if( ( value & 1 ) == 0 )
		return get_object( value );

	const size_t& array_length = value >> 1;
	const auto& vd = AmfValue::CreateVectorDoubleValue( parse_vector_base<float64>( input, length, array_length ) );
	object_reference_buffer_.push_back( vd );
	return vd;
}

IAmfValue^ amf3_parser::parse_vector_object( uint8*& input, size_t& length )
{
	const auto& value = parse_unsigned_29bit_integer( input, length );
	if( ( value & 1 ) == 0 )
		return get_object( value );

	const auto& vo = AmfValue::CreateVectorObjectValue();
	object_reference_buffer_.push_back( vo );

	//const auto& fixed = *value;
	input += 1;
	length -= 1;

	/*const auto& typeName =*/ parse_string_base( input, length );

	const size_t& array_length = value >> 1;
	std::vector<IAmfValue^> vector( array_length );
	for( size_t i = 0; i < array_length; ++i )
		vector[i] = parse_value( input, length );

	vo->SetData( ref new Platform::Collections::Vector<IAmfValue^>( std::move( vector ) ) );
	return vo;
}

Platform::String^ amf3_parser::parse_utf8( uint8*& input, size_t& length, const uint32 text_length )
{
	if( text_length == 0 )
		return "";

	if( length < text_length )
		throw amf_exception( "Invalid utf8." );

	std::ostringstream buf;
	buf.write( reinterpret_cast<char*>( input ), text_length );
	input += text_length;
	length -= text_length;

	return utilities::char_utf8_to_platform_string( buf.str() );
}

uint32 amf3_parser::parse_unsigned_29bit_integer( uint8*& input, size_t& length )
{
	if( length == 0 )
		throw amf_exception( "Invalid unsigned 29-bit integer." );

	uint32 ret = input[0] & 0x7f;
	if( input[0] <= 0x7f )
	{
		input += 1;
		length -= 1;
		return ret;
	}

	if( length == 1 )
		throw amf_exception( "Invalid unsigned 29-bit integer." );

	ret = ( ret << 7 ) | ( input[1] & 0x7f );
	if( input[1] <= 0x7f )
	{
		input += 2;
		length -= 2;
		return ret;
	}

	if( length == 2 )
		throw amf_exception( "Invalid unsigned 29-bit integer." );

	ret = ( ret << 7 ) | ( input[2] & 0x7f );
	if( input[2] <= 0x7f )
	{
		input += 3;
		length -= 3;
		return ret;
	}

	if( length == 3 )
		throw amf_exception( "Invalid unsigned 29-bit integer." );

	ret = ( ret << 8 ) | input[3];
	input += 4;
	length -= 4;
	return ret;
}

IAmfValue^ amf3_parser::get_object( const size_t input )
{
	const auto& ref = input >> 1;
	if( ref >= object_reference_buffer_.size() )
		throw amf_exception( "Invalid reference." );
	return object_reference_buffer_[ref];
}