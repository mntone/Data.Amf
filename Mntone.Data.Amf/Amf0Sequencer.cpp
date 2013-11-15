#include "pch.h"
#include "Amf0Sequencer.h"
#include "AmfValue.h"
#include "AmfArray.h"
#include "AmfObject.h"
#include "amf0_type.h"

using namespace Mntone::Data::Amf;

Platform::Array<uint8>^ Amf0Sequencer::Sequencify( IAmfValue^ input )
{
	std::basic_ostringstream<uint8> stream;
	( ref new Amf0Sequencer() )->SequencifyValue( input, stream );
	const auto& sequence = stream.str();
	auto out = ref new Platform::Array<uint8>( static_cast<uint32>( sequence.length() ) );
	std::memcpy( out->Data, sequence.data(), sequence.size() );
	return out;
}

Amf0Sequencer::Amf0Sequencer( void )
{ }

void Amf0Sequencer::SequencifyValue( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	switch( input->ValueType )
	{
	case AmfValueType::Undefined: SequencifyUndefined( input, stream ); break;
	case AmfValueType::Null: SequencifyNull( input, stream ); break;
	case AmfValueType::Boolean: SequencifyBoolean( input, stream ); break;
	case AmfValueType::Number: SequencifyNumber( input, stream ); break;
	case AmfValueType::String: SequencifyString( input, stream ); break;
	case AmfValueType::Date: SequencifyDate( input, stream ); break;
	case AmfValueType::Xml: SequencifyXml( input, stream ); break;
	case AmfValueType::Object: SequencifyObject( input, stream ); break;
	case AmfValueType::EcmaArray: SequencifyEcmaArray( input, stream ); break;
	case AmfValueType::Array: SequencifyStrictArray( input, stream ); break;
	default: throw ref new Platform::FailureException( "Invalid type." );
	}
}

void Amf0Sequencer::SequencifyUndefined( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_undefined );
}

void Amf0Sequencer::SequencifyNull( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_null );
}

void Amf0Sequencer::SequencifyBoolean( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_boolean );
	stream.put( static_cast<uint8>( input->GetBoolean() ) );
}

void Amf0Sequencer::SequencifyNumber( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_number );

	const auto& data = input->GetNumber();
	uint8 buf[8];
	ConvertBigEndian( &data, buf, 8 );
	stream.write( buf, 8 );
}

void Amf0Sequencer::SequencifyString( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	const auto& data = PlatformStringToCharUtf8( input->GetString() );
	if( data.length() > 0xffff )
	{
		stream.put( amf0_type::amf0_long_string );
		SequencifyUtf8Long( data, stream );
	}
	else
	{
		stream.put( amf0_type::amf0_string );
		SequencifyUtf8( data, stream );
	}
}

void Amf0Sequencer::SequencifyDate( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_date );

	const auto& data = static_cast<float64>( DateTimeToUnixTime( input->GetDate() ) );
	uint8 buf[10];
	ConvertBigEndian( &data, buf, 8 );

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
	ConvertBigEndian( &offset, buf + 8, 2 );
#endif

	stream.write( buf, 10 );
}

void Amf0Sequencer::SequencifyXml( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_xml_document );
	SequencifyUtf8Long( input, stream );
}

void Amf0Sequencer::SequencifyObject( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	const auto& obj = input->GetObject();
	const auto& ref = IndexOfObjectIdenticalTo( obj );
	if( ref != -1 )
	{
		SequencifyReference( ref, stream );
		return;
	}
	referenceBuffer_.push_back( input );

	const auto& className = obj->ClassName;
	if( className == "" )
	{
		stream.put( amf0_type::amf0_object );
	}
	else
	{
		stream.put( amf0_type::amf0_typed_object );
		SequencifyUtf8( className, stream );
	}

	SequencifyObjectBase( obj, stream );
}

void Amf0Sequencer::SequencifyEcmaArray( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	const auto& obj = input->GetObject();
	const auto& ref = IndexOfObjectIdenticalTo( obj );
	if( ref != -1 )
	{
		SequencifyReference( ref, stream );
		return;
	}
	referenceBuffer_.push_back( input );

	stream.put( amf0_type::amf0_ecma_array );

	const auto& associativeCount = obj->Size;
	uint8 buf[4];
	ConvertBigEndian( &associativeCount, buf, 4 );
	stream.write( buf, 4 );

	SequencifyObjectBase( obj, stream );
}

void Amf0Sequencer::SequencifyObjectBase( AmfObject^ input, std::basic_ostringstream<uint8>& stream )
{
	const auto& view = input->GetView();
	for( const auto& item : view )
	{
		SequencifyUtf8( item->Key, stream );
		SequencifyValue( item->Value, stream );
	}

	stream.put( 0 );
	stream.put( 0 );
	stream.put( 9 );
}

void Amf0Sequencer::SequencifyStrictArray( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	const auto& ary = input->GetArray();
	const auto& ref = IndexOfObjectIdenticalTo( ary );
	if( ref != -1 )
	{
		SequencifyReference( ref, stream );
		return;
	}
	referenceBuffer_.push_back( input );

	stream.put( amf0_type::amf0_strict_array );

	const auto& length = ary->Size;
	uint8 buf[4];
	ConvertBigEndian( &length, buf, 4 );
	stream.write( buf, 4 );

	for( const auto& item : ary )
		SequencifyValue( item, stream );
}

void Amf0Sequencer::SequencifyUtf8( const std::string& input, std::basic_ostringstream<uint8>& stream )
{
	const auto& fullLength = input.length();
	if( fullLength > UINT16_MAX )
		throw ref new Platform::FailureException( "Invalid Utf8 length." );
	const auto& length = static_cast<uint16>( fullLength );

	uint8 buf[2];
	ConvertBigEndian( &length, buf, 2 );
	stream.write( buf, 2 );

	if( length != 0 )
		stream.write( reinterpret_cast<const uint8*>( input.c_str() ), fullLength );
}

void Amf0Sequencer::SequencifyUtf8( Platform::String^ input, std::basic_ostringstream<uint8>& stream )
{
	SequencifyUtf8( PlatformStringToCharUtf8( input ), stream );
}

void Amf0Sequencer::SequencifyUtf8( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	SequencifyUtf8( input->GetString(), stream );
}

void Amf0Sequencer::SequencifyUtf8Long( const std::string& input, std::basic_ostringstream<uint8>& stream )
{
	const auto& fullLength = input.length();
	if( fullLength > UINT32_MAX )
		throw ref new Platform::FailureException( "Invalid Utf8 length." );
	const auto& length = static_cast<uint32>( fullLength );

	uint8 buf[4];
	ConvertBigEndian( &length, buf, 4 );
	stream.write( buf, 4 );

	if( length != 0 )
		stream.write( reinterpret_cast<const uint8*>( input.c_str() ), fullLength );
}

void Amf0Sequencer::SequencifyUtf8Long( Platform::String^ input, std::basic_ostringstream<uint8>& stream )
{
	SequencifyUtf8Long( PlatformStringToCharUtf8( input ), stream );
}

void Amf0Sequencer::SequencifyUtf8Long( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	SequencifyUtf8Long( input->GetString(), stream );
}

int32 Amf0Sequencer::IndexOfObjectIdenticalTo( IAmfValue^ input )
{
	const int32& length = static_cast<int32>( referenceBuffer_.size() );
	for( int32 i = 0u; i < length; ++i )
	{
		if( i > UINT16_MAX )
			break;

		const auto& value = referenceBuffer_[i];
		if( value == input )
			return static_cast<int32>( i );
	}
	return -1;
}

void Amf0Sequencer::SequencifyReference( int32 input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_reference );

	const auto& data = static_cast<uint16>( input );
	uint8 buf[2];
	ConvertBigEndian( &data, buf, 2 );
	stream.write( buf, 2 );
}