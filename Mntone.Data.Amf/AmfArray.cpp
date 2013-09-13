#include "pch.h"
#include "AmfArray.h"
#include "AmfObject.h"
#include "Amf0Parser.h"

namespace Mntone { namespace Data { namespace Amf {

	AmfArray::AmfArray( void ) :
		_ValueType( AmfValueType::Array ),
		_Value( ref new Platform::Collections::Vector<IAmfValue^>( ) )
	{ }

	AmfArray::AmfArray( const std::vector<IAmfValue^>& data ) :
		_ValueType( AmfValueType::Array ),
		_Value( ref new Platform::Collections::Vector<IAmfValue^>( std::move( data ) ) )
	{ }

	Platform::Array<uint8>^ AmfArray::Sequenceify( void )
	{
		throw ref new Platform::NotImplementedException();
	}

	Platform::Array<uint8>^ AmfArray::Sequenceify( AmfEncodingType type )
	{
		throw ref new Platform::NotImplementedException();
	}

	bool AmfArray::GetBoolean( void ) { return safe_cast<bool>( _Value ); }
	float64 AmfArray::GetDouble( void ) { return safe_cast<float64>( _Value ); }
	int32 AmfArray::GetInteger( void ) { return safe_cast<int32>( _Value ); }
	Platform::String^ AmfArray::GetString( void ) { return safe_cast<Platform::String^>( _Value ); }
	uint16 AmfArray::GetReference( void ) { return safe_cast<uint16>( _Value ); }
	Windows::Foundation::DateTime AmfArray::GetDate( void ) { return safe_cast<Windows::Foundation::DateTime>( _Value ); }
	AmfObject^ AmfArray::GetObject( void ) { throw ref new Platform::FailureException(); }
	AmfArray^ AmfArray::GetArray( void ) { return safe_cast<AmfArray^>( this ); }

	bool AmfArray::GetBooleanAt( uint32 index ) { return Vector->GetAt( index )->GetBoolean(); }
	float64 AmfArray::GetDoubleAt( uint32 index ) { return Vector->GetAt( index )->GetDouble(); }
	int32 AmfArray::GetIntegerAt( uint32 index ) { return Vector->GetAt( index )->GetInteger(); }
	Platform::String^ AmfArray::GetStringAt( uint32 index ) { return Vector->GetAt( index )->GetString(); }
	uint16 AmfArray::GetReferenceAt( uint32 index ) { return Vector->GetAt( index )->GetReference(); }
	Windows::Foundation::DateTime AmfArray::GetDateAt( uint32 index ) { return Vector->GetAt( index )->GetDate(); }
	AmfObject^ AmfArray::GetObjectAt( uint32 index ) { return Vector->GetAt( index )->GetObject(); }
	AmfArray^ AmfArray::GetArrayAt( uint32 index ) { return Vector->GetAt( index )->GetArray(); }

	Windows::Foundation::Collections::IIterator<IAmfValue^>^ AmfArray::First( void ) { return Vector->First(); }

	IAmfValue^ AmfArray::GetAt( uint32 index ) { return Vector->GetAt( index ); }
	Windows::Foundation::Collections::IVectorView<IAmfValue^>^ AmfArray::GetView( void ) { return Vector->GetView(); }
	bool AmfArray::IndexOf( IAmfValue^ value, uint32 *index ) { return Vector->IndexOf( value, index ); }

	void AmfArray::SetAt( uint32 index, IAmfValue^ value ) { Vector->SetAt( index, value ); }
	void AmfArray::InsertAt( uint32 index, IAmfValue^ value ) { Vector->InsertAt( index, value ); }
	void AmfArray::RemoveAt( uint32 index ) { Vector->RemoveAt( index ); }
	void AmfArray::Append( IAmfValue^ value ) { Vector->Append( value ); }
	void AmfArray::RemoveAtEnd( void ) { Vector->RemoveAtEnd(); }
	void AmfArray::Clear( void ) { Vector->Clear(); }

	uint32 AmfArray::GetMany( uint32 startIndex, Platform::WriteOnlyArray<IAmfValue^>^ items ) { return Vector->GetMany( startIndex, items ); }
	void AmfArray::ReplaceAll( const Platform::Array<IAmfValue^>^ items ) { Vector->ReplaceAll( items ); }

	AmfArray^ AmfArray::Parse( const Platform::Array<uint8>^ input )
	{
		//return safe_cast<AmfArray^>( Amf3Parser::Parse( input ) );
		throw ref new Platform::NotImplementedException();
	}

	AmfArray^ AmfArray::Parse( const Platform::Array<uint8>^ input, AmfEncodingType type )
	{
		if( type == AmfEncodingType::Amf0 )
			return safe_cast<AmfArray^>( Amf0Parser::Parse( input ) );

		//return safe_cast<AmfArray^>( Amf3Parser::Parse( input ) );
		throw ref new Platform::NotImplementedException();
	}

	bool AmfArray::TryParse( const Platform::Array<uint8>^ input, AmfArray^* result )
	{
		//IAmfValue^ buf = *result;
		//return Amf3Parser::TryParse( input, &buf );
		throw ref new Platform::NotImplementedException();
	}

	bool AmfArray::TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfArray^* result )
	{
		IAmfValue^ buf = *result;
		if( type == AmfEncodingType::Amf0 )
			return Amf0Parser::TryParse( input, &buf );

		//return Amf3Parser::TryParse( input, &buf );
		throw ref new Platform::NotImplementedException();
	}

} } }
