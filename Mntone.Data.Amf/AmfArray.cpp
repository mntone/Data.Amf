#include "pch.h"
#include "AmfArray.h"
#include "Amf0Parser.h"
#include "Amf0Sequencer.h"

namespace Mntone { namespace Data { namespace Amf {

	AmfArray::AmfArray( void ) :
		_ValueType( AmfValueType::Array ),
		_vector( ref new Platform::Collections::Vector<IAmfValue^>( ) )
	{ }

	AmfArray::AmfArray( const std::vector<IAmfValue^>& data ) :
		_ValueType( AmfValueType::Array ),
		_vector( ref new Platform::Collections::Vector<IAmfValue^>( std::move( data ) ) )
	{ }

	Platform::Array<uint8>^ AmfArray::Sequenceify( void )
	{
		throw ref new Platform::NotImplementedException();
	}

	Platform::Array<uint8>^ AmfArray::Sequenceify( AmfEncodingType type )
	{
		if( type == AmfEncodingType::Amf0 )
			return Amf0Sequencer::Sequenceify( this );

		throw ref new Platform::NotImplementedException();
	}

	bool AmfArray::GetBoolean( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
	float64 AmfArray::GetDouble( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
	int32 AmfArray::GetInteger( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
	Platform::String^ AmfArray::GetString( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
	uint16 AmfArray::GetReference( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
	Windows::Foundation::DateTime AmfArray::GetDate( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
	AmfObject^ AmfArray::GetObject( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
	AmfArray^ AmfArray::GetArray( void ) { return safe_cast<AmfArray^>( this ); }

	bool AmfArray::GetBooleanAt( uint32 index ) { return _vector->GetAt( index )->GetBoolean(); }
	float64 AmfArray::GetDoubleAt( uint32 index ) { return _vector->GetAt( index )->GetDouble(); }
	int32 AmfArray::GetIntegerAt( uint32 index ) { return _vector->GetAt( index )->GetInteger(); }
	Platform::String^ AmfArray::GetStringAt( uint32 index ) { return _vector->GetAt( index )->GetString(); }
	uint16 AmfArray::GetReferenceAt( uint32 index ) { return _vector->GetAt( index )->GetReference(); }
	Windows::Foundation::DateTime AmfArray::GetDateAt( uint32 index ) { return _vector->GetAt( index )->GetDate(); }
	AmfObject^ AmfArray::GetObjectAt( uint32 index ) { return _vector->GetAt( index )->GetObject(); }
	AmfArray^ AmfArray::GetArrayAt( uint32 index ) { return _vector->GetAt( index )->GetArray(); }

	Windows::Foundation::Collections::IIterator<IAmfValue^>^ AmfArray::First( void ) { return _vector->First(); }

	IAmfValue^ AmfArray::GetAt( uint32 index ) { return _vector->GetAt( index ); }
	Windows::Foundation::Collections::IVectorView<IAmfValue^>^ AmfArray::GetView( void ) { return _vector->GetView(); }
	bool AmfArray::IndexOf( IAmfValue^ value, uint32 *index ) { return _vector->IndexOf( value, index ); }

	void AmfArray::SetAt( uint32 index, IAmfValue^ value ) { _vector->SetAt( index, value ); }
	void AmfArray::InsertAt( uint32 index, IAmfValue^ value ) { _vector->InsertAt( index, value ); }
	void AmfArray::RemoveAt( uint32 index ) { _vector->RemoveAt( index ); }
	void AmfArray::Append( IAmfValue^ value ) { _vector->Append( value ); }
	void AmfArray::RemoveAtEnd( void ) { _vector->RemoveAtEnd(); }
	void AmfArray::Clear( void ) { _vector->Clear(); }

	uint32 AmfArray::GetMany( uint32 startIndex, Platform::WriteOnlyArray<IAmfValue^>^ items ) { return _vector->GetMany( startIndex, items ); }
	void AmfArray::ReplaceAll( const Platform::Array<IAmfValue^>^ items ) { _vector->ReplaceAll( items ); }

	Platform::String^ AmfArray::ToString( void )
	{
		std::wstringstream buf;
		buf << '[';
		for each( auto item in _vector )
		{
			auto out = item->ToString();
			buf.write( out->Data(), out->Length() );
			buf.write( L", ", 2 );
		}
		buf << ']';
		return ref new Platform::String( buf.str().c_str() );
	}

	AmfArray^ AmfArray::Parse( const Platform::Array<uint8>^ input )
	{
		//return safe_cast<AmfArray^>( Amf3Parser::Parse( input ) );
		throw ref new Platform::NotImplementedException();
	}

	AmfArray^ AmfArray::Parse( const Platform::Array<uint8>^ input, AmfEncodingType type )
	{
		if( type == AmfEncodingType::Amf0 )
			return reinterpret_cast<AmfArray^>( Amf0Parser::Parse( input ) );

		//return safe_cast<AmfArray^>( Amf3Parser::Parse( input ) );
		throw ref new Platform::NotImplementedException();
	}

	bool AmfArray::TryParse( const Platform::Array<uint8>^ /*input*/, AmfArray^* /*result*/ )
	{
		//IAmfValue^ buf = *result;
		//return Amf3Parser::TryParse( input, &buf );
		throw ref new Platform::NotImplementedException();
	}

	bool AmfArray::TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfArray^* result )
	{
		auto buf = reinterpret_cast<IAmfValue^*>( result );
		if( type == AmfEncodingType::Amf0 )
			return Amf0Parser::TryParse( input, buf );

		//return Amf3Parser::TryParse( input, &buf );
		throw ref new Platform::NotImplementedException();
	}

} } }
