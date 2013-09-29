#include "pch.h"
#include "AmfObject.h"
#include "Amf0Parser.h"
#include "Amf0Sequencer.h"

using namespace Mntone::Data::Amf;

AmfObject::AmfObject( void ) :
	_ValueType( AmfValueType::Object ),
	_map( ref new Platform::Collections::Map<Platform::String^, IAmfValue^>( ) )
{ }

AmfObject::AmfObject( std::map<Platform::String^, IAmfValue^> data ) :
	_ValueType( AmfValueType::Object ),
	_map( ref new Platform::Collections::Map<Platform::String^, IAmfValue^>( std::move( data ) ) )
{ }

Platform::Array<uint8>^ AmfObject::Sequenceify( void )
{
	throw ref new Platform::NotImplementedException();
}

Platform::Array<uint8>^ AmfObject::Sequenceify( AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf0 )
		return Amf0Sequencer::Sequenceify( this );

	throw ref new Platform::NotImplementedException();
}

bool AmfObject::GetBoolean( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
float64 AmfObject::GetDouble( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
int32 AmfObject::GetInteger( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
Platform::String^ AmfObject::GetString( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
uint16 AmfObject::GetReference( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
Windows::Foundation::DateTime AmfObject::GetDate( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
AmfObject^ AmfObject::GetObject( void ) { return safe_cast<AmfObject^>( this ); }
AmfArray^ AmfObject::GetArray( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }

AmfValue^ AmfObject::GetNamedValue( Platform::String^ name ) { return safe_cast<AmfValue^>( _map->Lookup( name ) ); }
void AmfObject::SetNamedValue( Platform::String^ name, IAmfValue^ value ) { _map->Insert( name, value ); }
bool AmfObject::GetNamedBoolean( Platform::String^ name ) { return _map->Lookup( name )->GetBoolean(); }
float64 AmfObject::GetNamedDouble( Platform::String^ name ) { return _map->Lookup( name )->GetDouble(); }
int32 AmfObject::GetNamedInteger( Platform::String^ name ) { return _map->Lookup( name )->GetInteger(); }
Platform::String^ AmfObject::GetNamedString( Platform::String^ name ) { return _map->Lookup( name )->GetString(); }
uint16 AmfObject::GetNamedReference( Platform::String^ name ) { return _map->Lookup( name )->GetReference(); }
Windows::Foundation::DateTime AmfObject::GetNamedDate( Platform::String^ name ) { return _map->Lookup( name )->GetDate(); }
AmfObject^ AmfObject::GetNamedObject( Platform::String^ name ) { return _map->Lookup( name )->GetObject(); }
AmfArray^ AmfObject::GetNamedArray( Platform::String^ name ) { return _map->Lookup( name )->GetArray(); }

Windows::Foundation::Collections::IIterator<Windows::Foundation::Collections::IKeyValuePair<Platform::String^, IAmfValue^>^>^ AmfObject::First( void ) { return _map->First(); }

IAmfValue^ AmfObject::Lookup( Platform::String^ key ) { return _map->Lookup( key ); }
bool AmfObject::HasKey( Platform::String^ key ) { return _map->HasKey( key ); }
Windows::Foundation::Collections::IMapView<Platform::String^, IAmfValue^>^ AmfObject::GetView( void ) { return _map->GetView(); }

bool AmfObject::Insert( Platform::String^ key, IAmfValue^ value ) { return _map->Insert( key, value ); }
void AmfObject::Remove( Platform::String^ key ) { _map->Remove( key ); }
void AmfObject::Clear( void ) { _map->Clear(); }

Platform::String^ AmfObject::ToString( void )
{
	std::wstringstream buf;
	buf << '{';
	for each( auto item in _map )
	{
		auto key = item->Key->ToString();
		auto value = item->Value->ToString();
		buf.put( L'"' );
		buf.write( key->Data(), key->Length() );
		buf.write( L"\": ", 3 );
		buf.write( value->Data(), value->Length() );
		buf.write( L", ", 2 );
	}
	buf << '}';
	return ref new Platform::String( buf.str().c_str() );
}

AmfObject^ AmfObject::Parse( const Platform::Array<uint8>^ input )
{
	//return safe_cast<AmfArray^>( Amf3Parser::Parse( input ) );
	throw ref new Platform::NotImplementedException();
}

AmfObject^ AmfObject::Parse( const Platform::Array<uint8>^ input, AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf0 )
		return reinterpret_cast<AmfObject^>( Amf0Parser::Parse( input ) );

	//return safe_cast<AmfArray^>( Amf3Parser::Parse( input ) );
	throw ref new Platform::NotImplementedException();
}

bool AmfObject::TryParse( const Platform::Array<uint8> ^ /*input*/, AmfObject^* /*result*/ )
{
	//IAmfValue^ buf = *result;
	//return Amf3Parser::TryParse( input, &buf );
	throw ref new Platform::NotImplementedException();
}

bool AmfObject::TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfObject^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	if( type == AmfEncodingType::Amf0 )
		return Amf0Parser::TryParse( input, buf );

	//return Amf3Parser::TryParse( input, &buf );
	throw ref new Platform::NotImplementedException();
}