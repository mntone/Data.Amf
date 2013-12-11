#include "pch.h"
#include "AmfObject.h"
#include "amf0_parser.h"
#include "amf0_sequencer.h"
#include "amf3_parser.h"
#include "amf3_sequencer.h"
#include "com_exception_helper.h"

using namespace mntone::data::amf;
using namespace Mntone::Data::Amf;

AmfObject::AmfObject() :
	ValueType_( AmfValueType::Object ),
#if _WINDOWS_PHONE
	map_( ref new Platform::Collections::Map<Platform::String^, IAmfValue^>() ),
#else
	map_( ref new Platform::Collections::UnorderedMap<Platform::String^, IAmfValue^>() ),
#endif
	ClassName_( "" ),
	Externalizable_( false )
{ }

Platform::Array<uint8>^ AmfObject::Sequencify()
{
	return amf0_sequencer::sequencify( this );
}

Platform::Array<uint8>^ AmfObject::Sequencify( AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf3 )
		return amf3_sequencer::sequencify( this );

	return amf0_sequencer::sequencify( this );
}

bool AmfObject::GetBoolean() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
float64 AmfObject::GetNumber() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
Platform::String^ AmfObject::GetString() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
Windows::Foundation::DateTime AmfObject::GetDate() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
Platform::Array<uint8>^ AmfObject::GetByteArray() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
Windows::Foundation::Collections::IVector<int32>^ AmfObject::GetVectorInt() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
Windows::Foundation::Collections::IVector<uint32>^ AmfObject::GetVectorUint() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
Windows::Foundation::Collections::IVector<float64>^ AmfObject::GetVectorDouble() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
Windows::Foundation::Collections::IVector<IAmfValue^>^ AmfObject::GetVectorObject() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }

AmfObject^ AmfObject::GetObject()
{
	if( ValueType_ != AmfValueType::Object && ValueType_ != AmfValueType::EcmaArray )
		throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." );

	return safe_cast<AmfObject^>( this );
}

AmfArray^ AmfObject::GetArray() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
AmfDictionary^ AmfObject::GetDictionary() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }

IAmfValue^ AmfObject::GetNamedValue( Platform::String^ name ) { return safe_cast<IAmfValue^>( map_->Lookup( name ) ); }
void AmfObject::SetNamedValue( Platform::String^ name, IAmfValue^ value ) { map_->Insert( name, value ); }
bool AmfObject::GetNamedBoolean( Platform::String^ name ) { return map_->Lookup( name )->GetBoolean(); }
float64 AmfObject::GetNamedNumber( Platform::String^ name ) { return map_->Lookup( name )->GetNumber(); }
Platform::String^ AmfObject::GetNamedString( Platform::String^ name ) { return map_->Lookup( name )->GetString(); }
Windows::Foundation::DateTime AmfObject::GetNamedDate( Platform::String^ name ) { return map_->Lookup( name )->GetDate(); }
Platform::Array<uint8>^ AmfObject::GetNamedByteArray( Platform::String^ name ) { return map_->Lookup( name )->GetByteArray(); }
Windows::Foundation::Collections::IVector<int32>^ AmfObject::GetNamedVectorInt( Platform::String^ name ) { return map_->Lookup( name )->GetVectorInt(); }
Windows::Foundation::Collections::IVector<uint32>^ AmfObject::GetNamedVectorUint( Platform::String^ name ) { return map_->Lookup( name )->GetVectorUint(); }
Windows::Foundation::Collections::IVector<float64>^ AmfObject::GetNamedVectorDouble( Platform::String^ name ) { return map_->Lookup( name )->GetVectorDouble(); }
Windows::Foundation::Collections::IVector<IAmfValue^>^ AmfObject::GetNamedVectorObject( Platform::String^ name ) { return map_->Lookup( name )->GetVectorObject(); }
AmfObject^ AmfObject::GetNamedObject( Platform::String^ name ) { return map_->Lookup( name )->GetObject(); }
AmfArray^ AmfObject::GetNamedArray( Platform::String^ name ) { return map_->Lookup( name )->GetArray(); }
AmfDictionary^ AmfObject::GetNamedDictionary( Platform::String^ name ) { return map_->Lookup( name )->GetDictionary(); }

Windows::Foundation::Collections::IIterator<Windows::Foundation::Collections::IKeyValuePair<Platform::String^, IAmfValue^>^>^ AmfObject::First() { return map_->First(); }

IAmfValue^ AmfObject::Lookup( Platform::String^ key ) { return map_->Lookup( key ); }
bool AmfObject::HasKey( Platform::String^ key ) { return map_->HasKey( key ); }
Windows::Foundation::Collections::IMapView<Platform::String^, IAmfValue^>^ AmfObject::GetView() { return map_->GetView(); }

bool AmfObject::Insert( Platform::String^ key, IAmfValue^ value )
{
	if( key == "" )
		throw ref new Platform::InvalidArgumentException( "Invalid key." );

	return map_->Insert( key, value );
}
void AmfObject::Remove( Platform::String^ key ) { map_->Remove( key ); }
void AmfObject::Clear() { map_->Clear(); }

#if !_WINDOWS_PHONE
Platform::String^ AmfObject::ToString()
{
	std::wostringstream buf;
	buf << '{';
	for( const auto& item : map_ )
	{
		const auto& key = item->Key->ToString();
		const auto& value = item->Value->ToString();
		buf.put( L'"' );
		buf.write( key->Data(), key->Length() );
		buf.write( L"\": ", 3 );
		buf.write( value->Data(), value->Length() );
		buf.write( L", ", 2 );
	}
	auto str = buf.str();
	const auto& length = str.length();
	if( length != 1 )
		str.erase( length - 2 );
	str += L'}';
	return ref new Platform::String( str.c_str(), static_cast<uint32>( str.length() ) );
}
#endif

AmfObject^ AmfObject::CreateEcmaArray()
{
	auto out = ref new AmfObject();
	out->ValueType_ = AmfValueType::EcmaArray;
	return out;
}

AmfObject^ AmfObject::Parse( const Platform::Array<uint8>^ input )
{
	return reinterpret_cast<AmfObject^>( amf0_parser::parse( input ) );
}

AmfObject^ AmfObject::Parse( const Platform::Array<uint8>^ input, AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf3 )
		return reinterpret_cast<AmfObject^>( amf3_parser::parse( input ) );

	return reinterpret_cast<AmfObject^>( amf0_parser::parse( input ) );
}

bool AmfObject::TryParse( const Platform::Array<uint8>^ input, AmfObject^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	return amf0_parser::try_parse( input, buf );
}

bool AmfObject::TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfObject^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	if( type == AmfEncodingType::Amf3 )
		return amf3_parser::try_parse( input, buf );

	return amf0_parser::try_parse( input, buf );
}

#if _WINDOWS_PHONE
void AmfObject::SetData( std::map<Platform::String^, IAmfValue^> data )
{
	map_ = ref new Platform::Collections::Map<Platform::String^, IAmfValue^>( data );
}
#else
void AmfObject::SetData( std::unordered_map<Platform::String^, IAmfValue^> data )
{
	map_ = ref new Platform::Collections::UnorderedMap<Platform::String^, IAmfValue^>( data );
}
#endif