#include "pch.h"
#include "Amf3Sequencer.h"
#include "AmfValue.h"
#include "AmfArray.h"
#include "AmfObject.h"
#include "amf3_type.h"

using namespace Mntone::Data::Amf;

Platform::Array<uint8>^ Amf3Sequencer::Sequenceify( IAmfValue^ input )
{
	std::basic_stringstream<uint8> stream;
	( ref new Amf3Sequencer() )->SequenceifyValue( input, stream );
	const auto& sequence = stream.str();
	auto out = ref new Platform::Array<uint8>( static_cast<uint32>( sequence.length() ) );
	memcpy( out->Data, sequence.c_str(), sequence.length() );
	return out;
}

Amf3Sequencer::Amf3Sequencer( void )
{ }

void Amf3Sequencer::SequenceifyValue( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	switch( input->ValueType )
	{
	case AmfValueType::Undefined: SequenceifyUndefined( input, stream ); break;
	case AmfValueType::Null: SequenceifyNull( input, stream ); break;
	case AmfValueType::Boolean: SequenceifyBoolean( input, stream ); break;
	case AmfValueType::Double: SequenceifyDouble( input, stream ); break;
	case AmfValueType::Integer: SequenceifyInteger( input, stream ); break;
	//case AmfValueType::String: SequenceifyString( input, stream ); break;
	//case AmfValueType::Date: SequenceifyDate( input, stream ); break;
	//case AmfValueType::Xml: SequenceifyXml( input, stream ); break;
	//case AmfValueType::ByteArray: SequenceifyByteArray( input, stream ); break;
	//case AmfValueType::VectorInt: SequenceifyVectorInt( input, stream ); break;
	//case AmfValueType::VectorUint: SequenceifyVectorUint( input, stream ); break;
	//case AmfValueType::VectorDouble: SequenceifyVectorDouble( input, stream ); break;
	//case AmfValueType::VectorObject: SequenceifyVectorObject( input, stream ); break;
	//case AmfValueType::Object: SequenceifyObject( input, stream ); break;
	//case AmfValueType::EcmaArray: SequenceifyEcmaArray( input, stream ); break;
	//case AmfValueType::Array: SequenceifyStrictArray( input, stream ); break;
	default: throw ref new Platform::FailureException( "Invalid type." );
	}
}

void Amf3Sequencer::SequenceifyUndefined( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_undefined );
}

void Amf3Sequencer::SequenceifyNull( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_null );
}

void Amf3Sequencer::SequenceifyBoolean( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	if( input->GetBoolean() )
		stream.put( amf3_type::amf3_true );
	else
		stream.put( amf3_type::amf3_false );
}

void Amf3Sequencer::SequenceifyInteger( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_interger );

	const auto& data = input->GetInteger();
	SequenceifyUnsigned29bitInteger( data, stream );
}

void Amf3Sequencer::SequenceifyDouble( IAmfValue^ input, std::basic_stringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_double );

	const auto& data = input->GetDouble();
	uint8 buf[8];
	ConvertBigEndian( &data, buf, 8 );
	stream.write( buf, 8 );
}

void Amf3Sequencer::SequenceifyUnsigned29bitInteger( uint32 input, std::basic_stringstream<uint8>& stream )
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
	else if( input < 0x40000000 )
	{
		stream.put( static_cast<uint8>( 0x80 | ( input >> 22 ) & 0x7f ) );
		stream.put( static_cast<uint8>( 0x80 | ( input >> 15 ) & 0x7f ) );
		stream.put( static_cast<uint8>( 0x80 | ( input >> 8 ) & 0x7f ) );
		stream.put( static_cast<uint8>( input & 0xff ) );
	}
	else
		throw ref new Platform::FailureException( "Invalid unsigned 29-bit integer." );
}