#include "pch.h"
#include "Amf3Sequencer.h"
#include "AmfValue.h"
#include "AmfArray.h"
#include "AmfObject.h"
#include "amf3_type.h"

using namespace Mntone::Data::Amf;

Platform::Array<uint8>^ Amf3Sequencer::Sequencify( IAmfValue^ input )
{
	std::basic_ostringstream<uint8> stream;
	( ref new Amf3Sequencer() )->SequencifyValue( input, stream );
	const auto& sequence = stream.str();
	auto out = ref new Platform::Array<uint8>( static_cast<uint32>( sequence.length() ) );
	std::memcpy( out->Data, sequence.data(), sequence.size() );
	return out;
}

Amf3Sequencer::Amf3Sequencer( void )
{ }

void Amf3Sequencer::SequencifyValue( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	switch( input->ValueType )
	{
	case AmfValueType::Undefined: SequencifyUndefined( input, stream ); break;
	case AmfValueType::Null: SequencifyNull( input, stream ); break;
	case AmfValueType::Boolean: SequencifyBoolean( input, stream ); break;
	case AmfValueType::Number: SequencifyDouble( input, stream ); break;
	case AmfValueType::String: SequencifyString( input, stream ); break;
	case AmfValueType::Date: SequencifyDate( input, stream ); break;
	case AmfValueType::Xml: SequencifyXml( input, stream ); break;
	case AmfValueType::ByteArray: SequencifyByteArray( input, stream ); break;
	case AmfValueType::VectorInt: SequencifyVectorInt( input, stream ); break;
	case AmfValueType::VectorUint: SequencifyVectorUint( input, stream ); break;
	case AmfValueType::VectorDouble: SequencifyVectorDouble( input, stream ); break;
	case AmfValueType::VectorObject: SequencifyVectorObject( input, stream ); break;
	case AmfValueType::Object: SequencifyObject( input, stream ); break;
	case AmfValueType::EcmaArray: SequencifyEcmaArray( input, stream ); break;
	case AmfValueType::Array: SequencifyArray( input, stream ); break;
	default: throw ref new Platform::FailureException( "Invalid type." );
	}
}

void Amf3Sequencer::SequencifyUndefined( IAmfValue^ /*input*/, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_undefined );
}

void Amf3Sequencer::SequencifyNull( IAmfValue^ /*input*/, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_null );
}

void Amf3Sequencer::SequencifyBoolean( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	if( input->GetBoolean() )
		stream.put( amf3_type::amf3_true );
	else
		stream.put( amf3_type::amf3_false );
}

void Amf3Sequencer::SequencifyInteger( const float64 input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_interger );
	SequencifyUnsigned29bitInteger( 0x1fffffff & static_cast<size_t>( input ), stream );
}

void Amf3Sequencer::SequencifyDouble( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	const auto& data = input->GetNumber();
	if( data < 268435456 && data >= -268435456 && std::floor( data ) == data )
	{
		SequencifyInteger( data, stream );
		return;
	}

	stream.put( amf3_type::amf3_double );

	uint8 buf[8];
	ConvertBigEndian( &data, buf, 8 );
	stream.write( buf, 8 );
}

void Amf3Sequencer::SequencifyString( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_string );
	SequencifyStringBase( input->GetString(), stream );
}

void Amf3Sequencer::SequencifyStringBase( Platform::String^ input, std::basic_ostringstream<uint8>& stream )
{
	if( input == "" )
	{
		stream.put( 1 );
		return;
	}

	{
		const auto& length = stringReferenceBuffer_.size();
		for( size_t i = 0; i < length; ++i )
		{
			const auto& str = stringReferenceBuffer_[i];
			if( str == input )
			{
				SequencifyUnsigned28bitIntegerAndReference( i, true, stream );
				return;
			}
		}
	}

	{
		const auto& data = PlatformStringToCharUtf8( input );
		const auto& length = data.size();
		SequencifyUnsigned28bitIntegerAndReference( length, false, stream );
		stream.write( reinterpret_cast<const uint8*>( data.c_str() ), length );
	}

	stringReferenceBuffer_.push_back( input );
}

void Amf3Sequencer::SequencifyDate( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_date );

	const auto& ref = IsObjectReference( input );
	if( ref != -1 )
	{
		SequencifyUnsigned28bitIntegerAndReference( ref, true, stream );
		return;
	}
	objectReferenceBuffer_.push_back( input );
	SequencifyUnsigned28bitIntegerAndReference( 0, false, stream );

	const auto& data = static_cast<float64>( DateTimeToUnixTime( input->GetDate() ) );
	uint8 buf[8];
	ConvertBigEndian( &data, buf, 8 );
	stream.write( buf, 8 );
}

void Amf3Sequencer::SequencifyXml( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_xml );

	const auto& ref = IsObjectReference( input );
	if( ref != -1 )
	{
		SequencifyUnsigned28bitIntegerAndReference( ref, true, stream );
		return;
	}
	objectReferenceBuffer_.push_back( input );

	const auto& data = PlatformStringToCharUtf8( input->GetString() );
	const auto& length = data.size();
	SequencifyUnsigned28bitIntegerAndReference( length, false, stream );
	stream.write( reinterpret_cast<const uint8*>( data.c_str() ), length );
}

void Amf3Sequencer::SequencifyByteArray( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_byte_array );

	const auto& ref = IsObjectReference( input );
	if( ref != -1 )
	{
		SequencifyUnsigned28bitIntegerAndReference( ref, true, stream );
		return;
	}
	objectReferenceBuffer_.push_back( input );

	const auto& data = input->GetByteArray();
	const auto& length = data->Length;
	SequencifyUnsigned28bitIntegerAndReference( length, false, stream );
	stream.write( data->Data, length );
}

void Amf3Sequencer::SequencifyVectorInt( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_vector_int );

	const auto& ref = IsObjectReference( input );
	if( ref != -1 )
	{
		SequencifyUnsigned28bitIntegerAndReference( ref, true, stream );
		return;
	}
	objectReferenceBuffer_.push_back( input );

	const auto& vector = input->GetVectorInt();
	SequencifyVectorBase<int32, 4>( vector, stream );
}

void Amf3Sequencer::SequencifyVectorUint( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_vector_uint );

	const auto& ref = IsObjectReference( input );
	if( ref != -1 )
	{
		SequencifyUnsigned28bitIntegerAndReference( ref, true, stream );
		return;
	}
	objectReferenceBuffer_.push_back( input );

	const auto& vector = input->GetVectorUint();
	SequencifyVectorBase<uint32, 4>( vector, stream );
}

void Amf3Sequencer::SequencifyVectorDouble( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_vector_double );

	const auto& ref = IsObjectReference( input );
	if( ref != -1 )
	{
		SequencifyUnsigned28bitIntegerAndReference( ref, true, stream );
		return;
	}
	objectReferenceBuffer_.push_back( input );

	const auto& vector = input->GetVectorDouble();
	SequencifyVectorBase<float64, 8>( vector, stream );
}

void Amf3Sequencer::SequencifyVectorObject( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_vector_object );

	const auto& ref = IsObjectReference( input );
	if( ref != -1 )
	{
		SequencifyUnsigned28bitIntegerAndReference( ref, true, stream );
		return;
	}
	objectReferenceBuffer_.push_back( input );

	const auto& vector = input->GetVectorObject();
	const auto& length = vector->Size;
	SequencifyUnsigned28bitIntegerAndReference( length, false, stream );

	stream.put( 0 );
	stream.put( 1 ); // no-ref, String ""

	for( uint32 i = 0u; i < length; ++i )
	{
		const auto& data = vector->GetAt( i );
		SequencifyValue( data, stream );
	}
}

void Amf3Sequencer::SequencifyObject( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_object );

	const auto& ref = IsObjectReference( input );
	if( ref != -1 )
	{
		SequencifyUnsigned28bitIntegerAndReference( ref, true, stream );
		return;
	}
	objectReferenceBuffer_.push_back( input );

	const auto& obj = input->GetObject();
	const auto& className = obj->ClassName;

	std::shared_ptr<amf3_traits_info> info;
	{
		size_t i = 0u;
		const auto& length = traitsInfoBuffer_.size();
		while( i != length )
		{
			const auto& item = traitsInfoBuffer_[i];
			if( item->class_name == className )
			{
				info = item;
				break;
			}
			++i;
		}
		if( info != nullptr )
		{
			SequencifyUnsigned29bitInteger( i << 2 | 1, stream );
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
		info->class_name = className;
		traitsInfoBuffer_.push_back( info );
	}

	size_t data = info->properites.size() << 4 | 3;
	if( info->externalizable )
		data |= 4;
	if( info->dynamic )
		data |= 8;
	SequencifyUnsigned29bitInteger( data, stream );
	SequencifyStringBase( info->class_name, stream );
	for( const auto& key : info->properites )
		SequencifyStringBase( key, stream );

skip:
	for( const auto& key : info->properites )
		SequencifyValue( obj->GetNamedValue( key ), stream );

	if( info->dynamic )
	{
		for( const auto& item : obj )
		{
			SequencifyStringBase( item->Key, stream );
			SequencifyValue( item->Value, stream );
		}
		stream.put( 1 ); // no-ref, String ""
	}
}

void Amf3Sequencer::SequencifyEcmaArray( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_array );

	const auto& ref = IsObjectReference( input );
	if( ref != -1 )
	{
		SequencifyUnsigned28bitIntegerAndReference( ref, true, stream );
		return;
	}
	objectReferenceBuffer_.push_back( input );

	const auto& obj = input->GetObject();

	std::map<size_t, IAmfValue^> numericKeysItem;
	std::unordered_map<Platform::String^, IAmfValue^> stringKeysItem;
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

			stringKeysItem.emplace( key, item->Value );
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
			stringKeysItem.emplace( item.first.ToString(), item.second );
		}
	}

	SequencifyUnsigned28bitIntegerAndReference( numericKeysItem.size(), false, stream );
	for( const auto& item : stringKeysItem )
	{
		SequencifyStringBase( item.first, stream );
		SequencifyValue( item.second, stream );
	}
	stream.put( 1 );
	for( const auto& item : numericKeysItem )
		SequencifyValue( item.second, stream );
}

void Amf3Sequencer::SequencifyArray( IAmfValue^ input, std::basic_ostringstream<uint8>& stream )
{
	stream.put( amf3_type::amf3_array );

	const auto& ref = IsObjectReference( input );
	if( ref != -1 )
	{
		SequencifyUnsigned28bitIntegerAndReference( ref, true, stream );
		return;
	}
	objectReferenceBuffer_.push_back( input );

	const auto& ary = input->GetArray();
	const auto& length = ary->Size;
	SequencifyUnsigned28bitIntegerAndReference( length, false, stream );

	stream.put( 1 ); // no-ref, String ""

	for( const auto& item : ary )
		SequencifyValue( item, stream );
}

void Amf3Sequencer::SequencifyUnsigned28bitIntegerAndReference( const size_t input, const bool reference, std::basic_ostringstream<uint8>& stream )
{
	if( input > 0x10000000 )
		throw ref new Platform::FailureException( "Invalid unsigned 28-bit integer and reference." );

	SequencifyUnsigned29bitInteger( reference ? input << 1 : ( input << 1 ) | 1, stream );
}

void Amf3Sequencer::SequencifyUnsigned29bitInteger( const size_t input, std::basic_ostringstream<uint8>& stream )
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
		throw ref new Platform::FailureException( "Invalid unsigned 29-bit integer." );
}

int32 Amf3Sequencer::IsObjectReference( IAmfValue^ input )
{
	const int32& length = static_cast<int32>( objectReferenceBuffer_.size() );
	for( int32 i = 0u; i < length; ++i )
	{
		if( i > 0x10000000 )
			break;

		const auto& value = objectReferenceBuffer_[i];
		if( value == input )
			return i;
	}
	return -1;
}