#include "pch.h"
#include "amf_exception.h"
#include "amf0_sequencer.h"
#include "amf0_type.h"
#include "AmfValue.h"
#include "AmfArray.h"
#include "AmfObject.h"

using namespace mntone::data::amf;
using namespace Mntone::Data::Amf;

Platform::Array<uint8>^ amf0_sequencer::sequencify( IAmfValue^ input )
{
	std::basic_ostringstream<uint8> stream;
	try
	{
#if _DEBUG
	( ref new amf0_sequencer() )->sequencify_value( input, stream );
#else
	amf0_sequencer().sequencify_value( input, stream );
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

amf0_sequencer::amf0_sequencer( void )
{ }

void amf0_sequencer::sequencify_value( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	switch( input->ValueType )
	{
	case AmfValueType::Undefined: sequencify_undefined( input, stream ); break;
	case AmfValueType::Null: sequencify_null( input, stream ); break;
	case AmfValueType::Boolean: sequencify_boolean( input, stream ); break;
	case AmfValueType::Number: sequencify_number( input, stream ); break;
	case AmfValueType::String: sequencify_string( input, stream ); break;
	case AmfValueType::Date: sequencify_date( input, stream ); break;
	case AmfValueType::Xml: sequencify_xml( input, stream ); break;
	case AmfValueType::Object: sequencify_object( input, stream ); break;
	case AmfValueType::EcmaArray: sequencify_ecma_array( input, stream ); break;
	case AmfValueType::Array: sequencify_strict_array( input, stream ); break;
	default: throw amf_exception( "Invalid type." );
	}
}

void amf0_sequencer::sequencify_undefined( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_undefined );
}

void amf0_sequencer::sequencify_null( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_null );
}

void amf0_sequencer::sequencify_boolean( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_boolean );
	stream.put( static_cast<uint8>( input->GetBoolean() ) );
}

void amf0_sequencer::sequencify_number( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_number );

	const auto& data = input->GetNumber();
	uint8 buf[8];
	utilities::convert_big_endian( &data, buf, 8 );
	stream.write( buf, 8 );
}

void amf0_sequencer::sequencify_string( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	const auto& data = utilities::platform_string_to_char_utf8( input->GetString() );
	if( data.length() > 0xffff )
	{
		stream.put( amf0_type::amf0_long_string );
		sequencify_utf8_long( data, stream );
	}
	else
	{
		stream.put( amf0_type::amf0_string );
		sequencify_utf8( data, stream );
	}
}

void amf0_sequencer::sequencify_date( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_date );

	const auto& data = static_cast<float64>( utilities::date_time_to_unix_time( input->GetDate() ) );
	uint8 buf[10];
	utilities::convert_big_endian( &data, buf, 8 );

#if _WINDOWS_PHONE
	buf[8] = 0;
	buf[9] = 0;
#else
	const auto& calendar = ref new Windows::Globalization::Calendar();
	calendar->SetToNow();
	const auto& ltDay = calendar->Day;
	const int16& ltHour = static_cast<int16>( calendar->Hour );
	const int16& ltMinute = static_cast<int16>( calendar->Minute );
	calendar->ChangeTimeZone( "UTC" );
	int16 offset = 60 * ( static_cast<int16>( calendar->Hour ) - ltHour ) + static_cast<int16>( calendar->Minute ) - ltMinute;
	if( calendar->Day != ltDay )
		offset -= 60 * 24;
	utilities::convert_big_endian( &offset, buf + 8, 2 );
#endif

	stream.write( buf, 10 );
}

void amf0_sequencer::sequencify_xml( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_xml_document );
	sequencify_utf8_long( input, stream );
}

void amf0_sequencer::sequencify_object( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	const auto& obj = input->GetObject();
	const auto& ref = index_of_object_identical_to( obj );
	if( ref != -1 )
	{
		sequencify_reference( ref, stream );
		return;
	}
	reference_buffer_.push_back( input );

	const auto& class_name = obj->ClassName;
	if( class_name == "" )
	{
		stream.put( amf0_type::amf0_object );
	}
	else
	{
		stream.put( amf0_type::amf0_typed_object );
		sequencify_utf8( class_name, stream );
	}

	sequencify_object_base( obj, stream );
}

void amf0_sequencer::sequencify_ecma_array( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	const auto& obj = input->GetObject();
	const auto& ref = index_of_object_identical_to( obj );
	if( ref != -1 )
	{
		sequencify_reference( ref, stream );
		return;
	}
	reference_buffer_.push_back( input );

	stream.put( amf0_type::amf0_ecma_array );

	const auto& associativeCount = obj->Size;
	uint8 buf[4];
	utilities::convert_big_endian( &associativeCount, buf, 4 );
	stream.write( buf, 4 );

	sequencify_object_base( obj, stream );
}

void amf0_sequencer::sequencify_object_base( AmfObject^ input, std::basic_ostringstream<uint8>& stream )
{
	const auto& view = input->GetView();
	for( const auto& item : view )
	{
		sequencify_utf8( item->Key, stream );
		sequencify_value( item->Value, stream );
	}

	stream.put( 0 );
	stream.put( 0 );
	stream.put( 9 );
}

void amf0_sequencer::sequencify_strict_array( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	const auto& ary = input->GetArray();
	const auto& ref = index_of_object_identical_to( ary );
	if( ref != -1 )
	{
		sequencify_reference( ref, stream );
		return;
	}
	reference_buffer_.push_back( input );

	stream.put( amf0_type::amf0_strict_array );

	const auto& length = ary->Size;
	uint8 buf[4];
	utilities::convert_big_endian( &length, buf, 4 );
	stream.write( buf, 4 );

	for( const auto& item : ary )
		sequencify_value( item, stream );
}

void amf0_sequencer::sequencify_utf8( const std::string& input, std::basic_ostringstream<uint8>& stream )
{
	const auto& full_length = input.length();
	if( full_length > UINT16_MAX )
		throw amf_exception( "Invalid Utf8 length." );
	const auto& length = static_cast<uint16>( full_length );

	uint8 buf[2];
	utilities::convert_big_endian( &length, buf, 2 );
	stream.write( buf, 2 );

	if( length != 0 )
		stream.write( reinterpret_cast<const uint8*>( input.c_str() ), full_length );
}

void amf0_sequencer::sequencify_utf8( Platform::String^ input, std::basic_ostringstream<uint8>& stream )
{
	sequencify_utf8( utilities::platform_string_to_char_utf8( input ), stream );
}

void amf0_sequencer::sequencify_utf8( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	sequencify_utf8( input->GetString(), stream );
}

void amf0_sequencer::sequencify_utf8_long( const std::string& input, std::basic_ostringstream<uint8>& stream )
{
	const auto& full_length = input.length();
	if( full_length > UINT32_MAX )
		throw amf_exception( "Invalid Utf8 length." );
	const auto& length = static_cast<uint32>( full_length );

	uint8 buf[4];
	utilities::convert_big_endian( &length, buf, 4 );
	stream.write( buf, 4 );

	if( length != 0 )
		stream.write( reinterpret_cast<const uint8*>( input.c_str() ), full_length );
}

void amf0_sequencer::sequencify_utf8_long( Platform::String^ input, std::basic_ostringstream<uint8>& stream )
{
	sequencify_utf8_long( utilities::platform_string_to_char_utf8( input ), stream );
}

void amf0_sequencer::sequencify_utf8_long( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	sequencify_utf8_long( input->GetString(), stream );
}

int32 amf0_sequencer::index_of_object_identical_to( IAmfValue^ input )
{
	const int32& length = static_cast<int32>( reference_buffer_.size() );
	for( int32 i = 0u; i < length; ++i )
	{
		if( i > UINT16_MAX )
			break;

		const auto& value = reference_buffer_[i];
		if( value == input )
			return static_cast<int32>( i );
	}
	return -1;
}

void amf0_sequencer::sequencify_reference( int32 input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_reference );

	const auto& data = static_cast<uint16>( input );
	uint8 buf[2];
	utilities::convert_big_endian( &data, buf, 2 );
	stream.write( buf, 2 );
}