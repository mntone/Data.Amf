#include "pch.h"
#include "AmfObject.h"
#include "Amf0Parser.h"
#include "Amf0Sequencer.h"
#include "Amf3Parser.h"
#include "Amf3Sequencer.h"
#include "COMExceptionHelper.h"

using namespace Mntone::Data::Amf;

AmfObject::AmfObject( void ) :
	ValueType_( AmfValueType::Object ),
#if _WINDOWS_PHONE
	map_( ref new Platform::Collections::Map<Platform::String^, IAmfValue^>() ),
#else
	map_( ref new Platform::Collections::UnorderedMap<Platform::String^, IAmfValue^>() ),
#endif
	ClassName_( "" ),
	Externalizable_( false )
{ }

AmfObject::AmfObject( Platform::String^ className ):
	ValueType_( AmfValueType::Object ),
#if _WINDOWS_PHONE
	map_( ref new Platform::Collections::Map<Platform::String^, IAmfValue^>() ),
#else
	map_( ref new Platform::Collections::UnorderedMap<Platform::String^, IAmfValue^>() ),
#endif
	ClassName_( className ),
	Externalizable_( false )
{ }

Platform::Array<uint8>^ AmfObject::Sequencify( void )
{
	return Amf0Sequencer::Sequencify( this );
}

Platform::Array<uint8>^ AmfObject::Sequencify( AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf3 )
		return Amf3Sequencer::Sequencify( this );

	return Amf0Sequencer::Sequencify( this );
}

bool AmfObject::GetBoolean( void ) { throw COMExceptionHelper::CreateInvalidOperationException( "Invalid value type." ); }
int32 AmfObject::GetInteger( void ) { throw COMExceptionHelper::CreateInvalidOperationException( "Invalid value type." ); }
float64 AmfObject::GetDouble( void ) { throw COMExceptionHelper::CreateInvalidOperationException( "Invalid value type." ); }
Platform::String^ AmfObject::GetString( void ) { throw COMExceptionHelper::CreateInvalidOperationException( "Invalid value type." ); }
Windows::Foundation::DateTime AmfObject::GetDate( void ) { throw COMExceptionHelper::CreateInvalidOperationException( "Invalid value type." ); }
Platform::Array<uint8>^ AmfObject::GetByteArray( void ) { throw COMExceptionHelper::CreateInvalidOperationException( "Invalid value type." ); }
Windows::Foundation::Collections::IVector<int32>^ AmfObject::GetVectorInt( void ) { throw COMExceptionHelper::CreateInvalidOperationException( "Invalid value type." ); }
Windows::Foundation::Collections::IVector<uint32>^ AmfObject::GetVectorUint( void ) { throw COMExceptionHelper::CreateInvalidOperationException( "Invalid value type." ); }
Windows::Foundation::Collections::IVector<float64>^ AmfObject::GetVectorDouble( void ) { throw COMExceptionHelper::CreateInvalidOperationException( "Invalid value type." ); }
Windows::Foundation::Collections::IVector<IAmfValue^>^ AmfObject::GetVectorObject( void ) { throw COMExceptionHelper::CreateInvalidOperationException( "Invalid value type." ); }

AmfObject^ AmfObject::GetObject( void )
{
	if( ValueType_ != AmfValueType::Object && ValueType_ != AmfValueType::EcmaArray )
		throw COMExceptionHelper::CreateInvalidOperationException( L"Invalid value type." );

	return safe_cast<AmfObject^>( this );
}

AmfArray^ AmfObject::GetArray( void ) { throw COMExceptionHelper::CreateInvalidOperationException( "Invalid value type." ); }

AmfValue^ AmfObject::GetNamedValue( Platform::String^ name ) { return safe_cast<AmfValue^>( map_->Lookup( name ) ); }
void AmfObject::SetNamedValue( Platform::String^ name, IAmfValue^ value ) { map_->Insert( name, value ); }
bool AmfObject::GetNamedBoolean( Platform::String^ name ) { return map_->Lookup( name )->GetBoolean(); }
int32 AmfObject::GetNamedInteger( Platform::String^ name ) { return map_->Lookup( name )->GetInteger( ); }
float64 AmfObject::GetNamedDouble( Platform::String^ name ) { return map_->Lookup( name )->GetDouble(); }
Platform::String^ AmfObject::GetNamedString( Platform::String^ name ) { return map_->Lookup( name )->GetString(); }
Windows::Foundation::DateTime AmfObject::GetNamedDate( Platform::String^ name ) { return map_->Lookup( name )->GetDate(); }
Platform::Array<uint8>^ AmfObject::GetNamedByteArray( Platform::String^ name ) { return map_->Lookup( name )->GetByteArray(); }
Windows::Foundation::Collections::IVector<int32>^ AmfObject::GetNamedVectorInt( Platform::String^ name ) { return map_->Lookup( name )->GetVectorInt(); }
Windows::Foundation::Collections::IVector<uint32>^ AmfObject::GetNamedVectorUint( Platform::String^ name ) { return map_->Lookup( name )->GetVectorUint(); }
Windows::Foundation::Collections::IVector<float64>^ AmfObject::GetNamedVectorDouble( Platform::String^ name ) { return map_->Lookup( name )->GetVectorDouble(); }
Windows::Foundation::Collections::IVector<IAmfValue^>^ AmfObject::GetNamedVectorObject( Platform::String^ name ) { return map_->Lookup( name )->GetVectorObject(); }
AmfObject^ AmfObject::GetNamedObject( Platform::String^ name ) { return map_->Lookup( name )->GetObject(); }
AmfArray^ AmfObject::GetNamedArray( Platform::String^ name ) { return map_->Lookup( name )->GetArray(); }

Windows::Foundation::Collections::IIterator<Windows::Foundation::Collections::IKeyValuePair<Platform::String^, IAmfValue^>^>^ AmfObject::First( void ) { return map_->First(); }

IAmfValue^ AmfObject::Lookup( Platform::String^ key ) { return map_->Lookup( key ); }
bool AmfObject::HasKey( Platform::String^ key ) { return map_->HasKey( key ); }
Windows::Foundation::Collections::IMapView<Platform::String^, IAmfValue^>^ AmfObject::GetView( void ) { return map_->GetView(); }

bool AmfObject::Insert( Platform::String^ key, IAmfValue^ value ) { return map_->Insert( key, value ); }
void AmfObject::Remove( Platform::String^ key ) { map_->Remove( key ); }
void AmfObject::Clear( void ) { map_->Clear(); }

#if !_WINDOWS_PHONE
Platform::String^ AmfObject::ToString( void )
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

AmfObject^ AmfObject::CreateEcmaArray( void )
{
	auto out = ref new AmfObject();
	out->ValueType_ = AmfValueType::EcmaArray;
	return out;
}

AmfObject^ AmfObject::Parse( const Platform::Array<uint8>^ input )
{
	return reinterpret_cast<AmfObject^>( Amf0Parser::Parse( input ) );
}

AmfObject^ AmfObject::Parse( const Platform::Array<uint8>^ input, AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf3 )
		return reinterpret_cast<AmfObject^>( Amf3Parser::Parse( input ) );

	return reinterpret_cast<AmfObject^>( Amf0Parser::Parse( input ) );
}

bool AmfObject::TryParse( const Platform::Array<uint8>^ input, AmfObject^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	return Amf0Parser::TryParse( input, buf );
}

bool AmfObject::TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfObject^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	if( type == AmfEncodingType::Amf3 )
		return Amf3Parser::TryParse( input, buf );

	return Amf0Parser::TryParse( input, buf );
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