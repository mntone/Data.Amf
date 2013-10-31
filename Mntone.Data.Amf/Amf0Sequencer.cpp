#include "pch.h"
#include "Amf0Sequencer.h"
#include "AmfValue.h"
#include "AmfArray.h"
#include "AmfObject.h"
#include "amf0_type.h"

using namespace Mntone::Data::Amf;

Platform::Array<uint8>^ Amf0Sequencer::Sequenceify( IAmfValue^ input )
{
	std::basic_stringstream<uint8> stream;
	SequenceifyValue( input, stream );
	auto sequence = stream.str();
	auto out = ref new Platform::Array<uint8>( static_cast<uint32>( sequence.length() ) );
	memcpy( out->Data, sequence.c_str(), sequence.length() );
	return out;
}

void Amf0Sequencer::SequenceifyValue( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	switch( input->ValueType )
	{
	case AmfValueType::Undefined: SequenceifyUndefined( input, stream ); break;
	case AmfValueType::Null: SequenceifyNull( input, stream ); break;
	case AmfValueType::Boolean: SequenceifyBoolean( input, stream ); break;
	case AmfValueType::Double: SequenceifyDouble( input, stream ); break;
	case AmfValueType::Integer: SequenceifyInteger( input, stream ); break;
	case AmfValueType::String: SequenceifyString( input, stream ); break;
	case AmfValueType::Reference: SequenceifyReference( input, stream ); break;
	case AmfValueType::Date: SequenceifyDate( input, stream ); break;
	case AmfValueType::Xml: SequenceifyXml( input, stream ); break;
	case AmfValueType::Object: SequenceifyObject( input, stream ); break;
	case AmfValueType::EcmaArray: SequenceifyEcmaArray( input, stream ); break;
	case AmfValueType::TypedObject: SequenceifyTypedObject( input, stream ); break;
	case AmfValueType::Array: SequenceifyArray( input, stream ); break;
	default: throw ref new Platform::FailureException( "Invalid type." );
	}
}

void Amf0Sequencer::SequenceifyUndefined( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_undefined );
}

void Amf0Sequencer::SequenceifyNull( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_null );
}

void Amf0Sequencer::SequenceifyBoolean( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_boolean );
	stream.put( static_cast<uint8>( input->GetBoolean() ) );
}

void Amf0Sequencer::SequenceifyDouble( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_number );

	const auto& data = input->GetDouble();
	uint8 buf[8];
	ConvertBigEndian( &data, buf, 8 );
	stream.write( buf, 8 );
}

void Amf0Sequencer::SequenceifyInteger( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_number );

	const auto& data = static_cast<float64>( input->GetDouble() );
	uint8 buf[8];
	ConvertBigEndian( &data, buf, 8 );
	stream.write( buf, 8 );
}

void Amf0Sequencer::SequenceifyString( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	const auto& data = PlatformStringToCharUtf8( input->GetString() );
	if( data.length() > 0xffff )
	{
		stream.put( amf0_type::amf0_long_string );
		SequenceifyUtf8Long( data, stream );
	}
	else
	{
		stream.put( amf0_type::amf0_string );
		SequenceifyUtf8( data, stream );
	}
}

void Amf0Sequencer::SequenceifyReference( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_reference );

	const auto& data = input->GetReference();
	uint8 buf[2];
	ConvertBigEndian( &data, buf, 2 );
	stream.write( buf, 2 );
}

void Amf0Sequencer::SequenceifyDate( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_date );

	const auto& data = static_cast<float64>( DateTimeToUnixTime( input->GetDate() ) );
	uint8 buf[10];
	ConvertBigEndian( &data, buf, 8 );

	// Set to timezone 0x0000
	buf[8] = 0;
	buf[9] = 0;

	stream.write( buf, 10 );
}

void Amf0Sequencer::SequenceifyXml( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_xml_document );
	SequenceifyUtf8Long( input, stream );
}

void Amf0Sequencer::SequenceifyObject( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	const auto& obj = input->GetObject();
	stream.put( amf0_type::amf0_object );
	SequenceifyObjectBase( std::move( obj ), stream );
}

void Amf0Sequencer::SequenceifyEcmaArray( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	const auto& obj = input->GetObject();
	stream.put( amf0_type::amf0_ecma_array );

	const auto& associativeCount = obj->GetAssociativeCount();
	uint8 buf[4];
	ConvertBigEndian( &associativeCount, buf, 4 );
	stream.write( buf, 4 );

	SequenceifyObjectBase( std::move( obj ), stream );
}

void Amf0Sequencer::SequenceifyTypedObject( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	const auto& obj = input->GetObject();
	stream.put( amf0_type::amf0_typed_object );
	SequenceifyUtf8( obj->GetClassName(), stream );
	SequenceifyObjectBase( std::move( obj ), stream );
}

void Amf0Sequencer::SequenceifyObjectBase( AmfObject^ input, std::basic_stringstream<uint8>& stream )
{
	for( const auto& item : input->GetView() )
	{
		SequenceifyUtf8( item->Key, stream );
		SequenceifyValue( item->Value, stream );
	}

	stream.put( 0 );
	stream.put( 0 );
	stream.put( 9 );
}

void Amf0Sequencer::SequenceifyArray( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	stream.put( amf0_type::amf0_strict_array );

	const auto& ary = input->GetArray();
	const auto& vec = ary->GetView();
	const auto& size = vec->Size;

	uint8 buf[4];
	ConvertBigEndian( &size, buf, 4 );
	stream.write( buf, 4 );

	for( const auto& item : vec )
		SequenceifyValue( item, stream );
}

void Amf0Sequencer::SequenceifyUtf8( const std::string& input, std::basic_stringstream<uint8>& stream )
{
	const auto& length = static_cast<uint16>( input.length() );

	uint8 buf[2];
	ConvertBigEndian( &length, buf, 2 );
	stream.write( buf, 2 );

	if( length != 0 )
		stream.write( reinterpret_cast<const uint8*>( input.c_str() ), input.length() );
}

void Amf0Sequencer::SequenceifyUtf8( Platform::String^ input, std::basic_stringstream<uint8>& stream )
{
	SequenceifyUtf8( PlatformStringToCharUtf8( input ), stream );
}

void Amf0Sequencer::SequenceifyUtf8( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	SequenceifyUtf8( input->GetString(), stream );
}

void Amf0Sequencer::SequenceifyUtf8Long( const std::string& input, std::basic_stringstream<uint8>& stream )
{
	const auto& length = static_cast<uint32>( input.length() );

	uint8 buf[4];
	ConvertBigEndian( &length, buf, 4 );
	stream.write( buf, 4 );

	stream.write( reinterpret_cast<const uint8 *>( input.c_str() ), input.length() );
}

void Amf0Sequencer::SequenceifyUtf8Long( Platform::String^ input, std::basic_stringstream<uint8>& stream )
{
	SequenceifyUtf8Long( PlatformStringToCharUtf8( input ), stream );
}

void Amf0Sequencer::SequenceifyUtf8Long( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	SequenceifyUtf8Long( input->GetString(), stream );
}