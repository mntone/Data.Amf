#include "pch.h"
#include "AmfObject.h"
#include "AmfArray.h"
#include "Amf0Parser.h"

namespace Mntone { namespace Data { namespace Amf {

	AmfObject::AmfObject( void ) :
		_ValueType( AmfValueType::Object ),
		_Value( ref new Platform::Collections::Map<Platform::String^, IAmfValue^>() )
	{ }

	AmfObject::AmfObject( const std::map<Platform::String^, IAmfValue^>& data ) :
		_ValueType( AmfValueType::Object ),
		_Value( ref new Platform::Collections::Map<Platform::String^, IAmfValue^>( std::move( data ) ) )
	{ }

	Platform::Array<uint8>^ AmfObject::Sequenceify( void )
	{
		throw ref new Platform::NotImplementedException();
	}

	Platform::Array<uint8>^ AmfObject::Sequenceify( AmfEncodingType type )
	{
		throw ref new Platform::NotImplementedException();
	}

	bool AmfObject::GetBoolean( void ) { return safe_cast<bool>( _Value ); }
	float64 AmfObject::GetDouble( void ) { return safe_cast<float64>( _Value ); }
	int32 AmfObject::GetInteger( void ) { return safe_cast<int32>( _Value ); }
	Platform::String^ AmfObject::GetString( void ) { return safe_cast<Platform::String^>( _Value ); }
	uint16 AmfObject::GetReference( void ) { return safe_cast<uint16>( _Value ); }
	Windows::Foundation::DateTime AmfObject::GetDate( void ) { return safe_cast<Windows::Foundation::DateTime>( _Value ); }
	AmfObject^ AmfObject::GetObject( void ) { return safe_cast<AmfObject^>( this ); }
	AmfArray^ AmfObject::GetArray( void ) { throw ref new Platform::FailureException(); }

	AmfValue^ AmfObject::GetNamedValue( Platform::String^ name ) { return safe_cast<AmfValue^>( Map->Lookup( name ) ); }
	void AmfObject::SetNamedValue( Platform::String^ name, IAmfValue^ value ) { Map->Insert( name, value ); }
	bool AmfObject::GetNamedBoolean( Platform::String^ name ) { return Map->Lookup( name )->GetBoolean(); }
	float64 AmfObject::GetNamedDouble( Platform::String^ name ) { return Map->Lookup( name )->GetDouble(); }
	int32 AmfObject::GetNamedInteger( Platform::String^ name ) { return Map->Lookup( name )->GetInteger(); }
	Platform::String^ AmfObject::GetNamedString( Platform::String^ name ) { return Map->Lookup( name )->GetString(); }
	uint16 AmfObject::GetNamedReference( Platform::String^ name ) { return Map->Lookup( name )->GetReference(); }
	Windows::Foundation::DateTime AmfObject::GetNamedDate( Platform::String^ name ) { return Map->Lookup( name )->GetDate(); }
	AmfObject^ AmfObject::GetNamedObject( Platform::String^ name ) { return Map->Lookup( name )->GetObject(); }
	AmfArray^ AmfObject::GetNamedArray( Platform::String^ name ) { return Map->Lookup( name )->GetArray(); }

	Windows::Foundation::Collections::IIterator<Windows::Foundation::Collections::IKeyValuePair<Platform::String^, IAmfValue^>^>^ AmfObject::First( void ) { return Map->First(); }

	IAmfValue^ AmfObject::Lookup( Platform::String^ key ) { return Map->Lookup( key ); }
	bool AmfObject::HasKey( Platform::String^ key ) { return Map->HasKey( key ); }
	Windows::Foundation::Collections::IMapView<Platform::String^, IAmfValue^>^ AmfObject::GetView( void ) { return Map->GetView(); }

	bool AmfObject::Insert( Platform::String^ key, IAmfValue^ value ) { return Map->Insert( key, value ); }
	void AmfObject::Remove( Platform::String^ key ) { Map->Remove( key ); }
	void AmfObject::Clear( void ) { Map->Clear(); }

	AmfObject^ AmfObject::Parse( const Platform::Array<uint8>^ input )
	{
		//return safe_cast<AmfArray^>( Amf3Parser::Parse( input ) );
		throw ref new Platform::NotImplementedException();
	}

	AmfObject^ AmfObject::Parse( const Platform::Array<uint8>^ input, AmfEncodingType type )
	{
		if( type == AmfEncodingType::Amf0 )
			return safe_cast<AmfObject^>( Amf0Parser::Parse( input ) );

		//return safe_cast<AmfArray^>( Amf3Parser::Parse( input ) );
		throw ref new Platform::NotImplementedException();
	}

	bool AmfObject::TryParse( const Platform::Array<uint8>^ input, AmfObject^* result )
	{
		//IAmfValue^ buf = *result;
		//return Amf3Parser::TryParse( input, &buf );
		throw ref new Platform::NotImplementedException();
	}

	bool AmfObject::TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfObject^* result )
	{
		IAmfValue^ buf = *result;
		if( type == AmfEncodingType::Amf0 )
			return Amf0Parser::TryParse( input, &buf );

		//return Amf3Parser::TryParse( input, &buf );
		throw ref new Platform::NotImplementedException();
	}

} } }
