#include "pch.h"
#include "amf_exception.h"
#include "amf3_sequencer.h"
#include "amf3_type.h"
#include "AmfValue.h"
#include "AmfArray.h"
#include "AmfObject.h"
#include "AmfDictionary.h"

using namespace mntone::data::amf;
using namespace Mntone::Data::Amf;

Platform::Array<uint8>^ amf3_sequencer::sequencify( IAmfValue^ input )
{
	std::basic_ostringstream<uint8> stream;
	try
	{
#if _DEBUG
		( ref new amf3_sequencer() )->sequencify_value( input, stream );
#else
		amf3_sequencer().sequencify_value( input, stream );
#endif	
	}
	catch( const amf_exception& ex )
	{
		throw ref new Platform::FailureException( ex.get_message() );
	}
	const auto& sequence = stream.str();
	auto out = ref new Platform::Array<uint8>( static_cast<uint32>( sequence.length() ) );
	std::memcpy( out->Data, sequence.data(), sequence.size() );
	return out;
}

amf3_sequencer::amf3_sequencer()
{ }

void amf3_sequencer::sequencify_value( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	switch( input->ValueType )
	{
	case AmfValueType::Undefined: sequencify_undefined( input, stream ); break;
	case AmfValueType::Null: sequencify_null( input, stream ); break;
	case AmfValueType::Boolean: sequencify_boolean( input, stream ); break;
	case AmfValueType::Number: sequencify_double( input, stream ); break;
	case AmfValueType::String: sequencify_string( input, stream ); break;
	case AmfValueType::Date: sequencify_date( input, stream ); break;
	case AmfValueType::Xml: sequencify_xml( input, stream ); break;
	case AmfValueType::ByteArray: sequencify_byte_array( input, stream ); break;
	case AmfValueType::VectorInt: sequencify_vector_int( input, stream ); break;
	case AmfValueType::VectorUint: sequencify_vector_uint( input, stream ); break;
	case AmfValueType::VectorDouble: sequencify_vector_double( input, stream ); break;
	case AmfValueType::VectorObject: sequencify_vector_object( input, stream ); break;
	case AmfValueType::Object: sequencify_object( input, stream ); break;
	case AmfValueType::EcmaArray: sequencify_ecma_array( input, stream ); break;
	case AmfValueType::Array: sequencify_array( input, stream ); break;
	case AmfValueType::Dictionary: sequencify_dictionary( input, stream ); break;
	default: throw amf_exception( "Invalid type." );
	}
}

void amf3_sequencer::sequencify_undefined( IAmfValue^ /*input*/, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_undefined );
}

void amf3_sequencer::sequencify_null( IAmfValue^ /*input*/, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_null );
}

void amf3_sequencer::sequencify_boolean( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	if( input->GetBoolean() )
		stream.put( amf3_type::amf3_true );
	else
		stream.put( amf3_type::amf3_false );
}

void amf3_sequencer::sequencify_integer( const float64 input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_interger );
	sequencify_unsigned_29bit_integer( 0x1fffffff & static_cast<size_t>( input ), stream );
}

void amf3_sequencer::sequencify_double( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	const auto& data = input->GetNumber();
	if( data < 268435456 && data >= -268435456 && std::floor( data ) == data )
	{
		sequencify_integer( data, stream );
		return;
	}

	stream.put( amf3_type::amf3_double );

	uint8 buf[8];
	utility::convert_big_endian( &data, 8, buf );
	stream.write( buf, 8 );
}

void amf3_sequencer::sequencify_string( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_string );
	sequencify_string_base( input->GetString(), stream );
}

void amf3_sequencer::sequencify_string_base( Platform::String^ input, std::basic_ostringstream<uint8>& stream )
{
	if( input == "" )
	{
		stream.put( 1 );
		return;
	}

	{
		const auto& length = string_reference_buffer_.size();
		for( size_t i = 0; i < length; ++i )
		{
			const auto& str = string_reference_buffer_[i];
			if( str == input )
			{
				sequencify_unsigned_28bit_integer_and_reference( i, true, stream );
				return;
			}
		}
	}

	{
		const auto& data = utility::platform_string_to_char_utf8( input );
		const auto& length = data.size();
		sequencify_unsigned_28bit_integer_and_reference( length, false, stream );
		stream.write( reinterpret_cast<const uint8*>( data.c_str() ), length );
	}

	string_reference_buffer_.push_back( input );
}

void amf3_sequencer::sequencify_date( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_date );

	const auto& ref = index_of_object_identical_to( input );
	if( ref != -1 )
	{
		sequencify_unsigned_28bit_integer_and_reference( ref, true, stream );
		return;
	}
	object_reference_buffer_.push_back( input );
	sequencify_unsigned_28bit_integer_and_reference( 0, false, stream );

	const auto& data = static_cast<float64>( utility::date_time_to_unix_time( input->GetDate() ) );
	uint8 buf[8];
	utility::convert_big_endian( &data, 8, buf );
	stream.write( buf, 8 );
}

void amf3_sequencer::sequencify_xml( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_xml );

	const auto& ref = index_of_object_identical_to( input );
	if( ref != -1 )
	{
		sequencify_unsigned_28bit_integer_and_reference( ref, true, stream );
		return;
	}
	object_reference_buffer_.push_back( input );

	const auto& data = utility::platform_string_to_char_utf8( input->GetString() );
	const auto& length = data.size();
	sequencify_unsigned_28bit_integer_and_reference( length, false, stream );
	stream.write( reinterpret_cast<const uint8*>( data.c_str() ), length );
}

void amf3_sequencer::sequencify_byte_array( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_byte_array );

	const auto& ref = index_of_object_identical_to( input );
	if( ref != -1 )
	{
		sequencify_unsigned_28bit_integer_and_reference( ref, true, stream );
		return;
	}
	object_reference_buffer_.push_back( input );

	const auto& data = input->GetByteArray();
	const auto& length = data->Length;
	sequencify_unsigned_28bit_integer_and_reference( length, false, stream );
	stream.write( data->Data, length );
}

void amf3_sequencer::sequencify_vector_int( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_vector_int );

	const auto& ref = index_of_object_identical_to( input );
	if( ref != -1 )
	{
		sequencify_unsigned_28bit_integer_and_reference( ref, true, stream );
		return;
	}
	object_reference_buffer_.push_back( input );

	const auto& vector = input->GetVectorInt();
	sequencify_vector_base<int32, 4>( vector, stream );
}

void amf3_sequencer::sequencify_vector_uint( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_vector_uint );

	const auto& ref = index_of_object_identical_to( input );
	if( ref != -1 )
	{
		sequencify_unsigned_28bit_integer_and_reference( ref, true, stream );
		return;
	}
	object_reference_buffer_.push_back( input );

	const auto& vector = input->GetVectorUint();
	sequencify_vector_base<uint32, 4>( vector, stream );
}

void amf3_sequencer::sequencify_vector_double( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_vector_double );

	const auto& ref = index_of_object_identical_to( input );
	if( ref != -1 )
	{
		sequencify_unsigned_28bit_integer_and_reference( ref, true, stream );
		return;
	}
	object_reference_buffer_.push_back( input );

	const auto& vector = input->GetVectorDouble();
	sequencify_vector_base<float64, 8>( vector, stream );
}

void amf3_sequencer::sequencify_vector_object( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_vector_object );

	const auto& ref = index_of_object_identical_to( input );
	if( ref != -1 )
	{
		sequencify_unsigned_28bit_integer_and_reference( ref, true, stream );
		return;
	}
	object_reference_buffer_.push_back( input );

	const auto& vector = input->GetVectorObject();
	const auto& length = vector->Size;
	sequencify_unsigned_28bit_integer_and_reference( length, false, stream );

	stream.put( 0 );
	stream.put( 1 ); // no-ref, String ""

	for( uint32 i = 0u; i < length; ++i )
	{
		const auto& data = vector->GetAt( i );
		sequencify_value( data, stream );
	}
}

void amf3_sequencer::sequencify_object( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_object );

	const auto& ref = index_of_object_identical_to( input );
	if( ref != -1 )
	{
		sequencify_unsigned_28bit_integer_and_reference( ref, true, stream );
		return;
	}
	object_reference_buffer_.push_back( input );

	const auto& obj = input->GetObject();
	const auto& class_name = obj->ClassName;

	std::shared_ptr<amf3_traits_info> info;
	{
		size_t i = 0u;
		const auto& length = traits_info_buffer_.size();
		while( i != length )
		{
			const auto& item = traits_info_buffer_[i];
			if( item->class_name == class_name )
			{
				info = item;
				break;
			}
			++i;
		}
		if( info != nullptr )
		{
			sequencify_unsigned_29bit_integer( i << 2 | 1, stream );
			goto skip;
		}

		info = std::make_shared<amf3_traits_info>();
		info->externalizable = obj->Externalizable;
		if( obj->ClassName != "" )
		{
			info->dynamic = false;
			for( const auto& item : obj )
				info->properites.push_back( item->Key );
		}
		else
			info->dynamic = true;
		info->class_name = class_name;
		traits_info_buffer_.push_back( info );
	}

	size_t data = info->properites.size() << 4 | 3;
	if( info->externalizable )
		data |= 4;
	if( info->dynamic )
		data |= 8;
	sequencify_unsigned_29bit_integer( data, stream );
	sequencify_string_base( info->class_name, stream );
	for( const auto& key : info->properites )
		sequencify_string_base( key, stream );

skip:
	for( const auto& key : info->properites )
		sequencify_value( obj->GetNamedValue( key ), stream );

	if( info->dynamic )
	{
		for( const auto& item : obj )
		{
			sequencify_string_base( item->Key, stream );
			sequencify_value( item->Value, stream );
		}
		stream.put( 1 ); // no-ref, String ""
	}
}

void amf3_sequencer::sequencify_ecma_array( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_array );

	const auto& ref = index_of_object_identical_to( input );
	if( ref != -1 )
	{
		sequencify_unsigned_28bit_integer_and_reference( ref, true, stream );
		return;
	}
	object_reference_buffer_.push_back( input );

	const auto& obj = input->GetObject();

	std::map<size_t, IAmfValue^> numericKeysItem;
	std::vector<std::pair<Platform::String^, IAmfValue^>> stringKeysItem;
	{
		std::locale locale;
		for( const auto& item : obj )
		{
			const auto& key = item->Key;
			if( std::all_of( key->Begin(), key->End(), [locale]( char16 c ) { return std::isdigit( c, locale ); } ) )
			{
				numericKeysItem.emplace( std::wcstol( key->Data(), nullptr, 10 ), item->Value );
				continue;
			}

			stringKeysItem.push_back( std::make_pair( key, item->Value ) );
		}
	}

	{
		std::vector<std::pair<size_t, IAmfValue^>> list;
		size_t i = numericKeysItem.size() - 1;
#if _WINDOWS_PHONE
		auto itr = numericKeysItem.rbegin();
		while( itr != numericKeysItem.rend() )
#else
		auto itr = std::rbegin( numericKeysItem );
		while( itr != std::rend( numericKeysItem ) )
#endif
		{
			if( itr->first == i )
				break;

			list.push_back( *itr );
			--i; ++itr;
		}
		for( const auto& item : list )
		{
			numericKeysItem.erase( item.first );
			stringKeysItem.push_back( std::make_pair( item.first.ToString(), item.second ) );
		}
	}

	sequencify_unsigned_28bit_integer_and_reference( numericKeysItem.size(), false, stream );
	for( const auto& item : stringKeysItem )
	{
		sequencify_string_base( item.first, stream );
		sequencify_value( item.second, stream );
	}
	stream.put( 1 );
	for( const auto& item : numericKeysItem )
		sequencify_value( item.second, stream );
}

void amf3_sequencer::sequencify_array( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_array );

	const auto& ref = index_of_object_identical_to( input );
	if( ref != -1 )
	{
		sequencify_unsigned_28bit_integer_and_reference( ref, true, stream );
		return;
	}
	object_reference_buffer_.push_back( input );

	const auto& ary = input->GetArray();
	const auto& length = ary->Size;
	sequencify_unsigned_28bit_integer_and_reference( length, false, stream );

	stream.put( 1 ); // no-ref, String ""

	for( const auto& item : ary )
		sequencify_value( item, stream );
}

void amf3_sequencer::sequencify_dictionary( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_dictionary );

	const auto& ref = index_of_object_identical_to( input );
	if( ref != -1 )
	{
		sequencify_unsigned_28bit_integer_and_reference( ref, true, stream );
		return;
	}
	object_reference_buffer_.push_back( input );

	const auto& dic = input->GetDictionary();
	const auto& length = dic->Size;
	sequencify_unsigned_28bit_integer_and_reference( length, false, stream );

	stream.put( 0 ); // not using weakly-referenced key

	for( const auto& item : dic )
	{
		sequencify_value( item->Key, stream );
		sequencify_value( item->Value, stream );
	}
}

void amf3_sequencer::sequencify_unsigned_28bit_integer_and_reference( const size_t input, const bool reference, std::basic_ostringstream<uint8>& stream )
{
	if( input > 0x10000000 )
		throw ref new Platform::FailureException( "Invalid unsigned 28-bit integer and reference." );

	sequencify_unsigned_29bit_integer( reference ? input << 1 : ( input << 1 ) | 1, stream );
}

void amf3_sequencer::sequencify_unsigned_29bit_integer( const size_t input, std::basic_ostringstream<uint8>& stream )
{
	if( input < 0x80 )
		stream.put( static_cast<uint8>( input ) );
	else if( input < 0x4000 )
	{
		stream.put( static_cast<uint8>( 0x80 | ( input >> 7 ) & 0x7f ) );
		stream.put( static_cast<uint8>( input & 0x7f ) );
	}
	else if( input < 0x200000 )
	{
		stream.put( static_cast<uint8>( 0x80 | ( input >> 14 ) & 0x7f ) );
		stream.put( static_cast<uint8>( 0x80 | ( input >> 7 ) & 0x7f ) );
		stream.put( static_cast<uint8>( input & 0x7f ) );
	}
	else if( input < 0x20000000 )
	{
		stream.put( static_cast<uint8>( 0x80 | ( input >> 22 ) & 0x7f ) );
		stream.put( static_cast<uint8>( 0x80 | ( input >> 15 ) & 0x7f ) );
		stream.put( static_cast<uint8>( 0x80 | ( input >> 8 ) & 0x7f ) );
		stream.put( static_cast<uint8>( input & 0xff ) );
	}
	else
		throw amf_exception( "Invalid unsigned 29-bit integer." );
}

int32 amf3_sequencer::index_of_object_identical_to( IAmfValue^ input )
{
	const int32& length = static_cast<int32>( object_reference_buffer_.size() );
	for( int32 i = 0u; i < length; ++i )
	{
		if( i > 0x10000000 )
			break;

		const auto& value = object_reference_buffer_[i];
		if( value == input )
			return i;
	}
	return -1;
}