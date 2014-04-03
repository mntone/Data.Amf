#include "pch.h"
#include "AmfValue.h"
#include "AmfDictionary.h"
#include "amf0_parser.h"
#include "amf0_sequencer.h"
#include "amf3_parser.h"
#include "amf3_sequencer.h"
#include "com_exception_helper.h"

using namespace mntone::data::amf;
using namespace Mntone::Data::Amf;

AmfDictionary::AmfDictionary() :
	ValueType_( AmfValueType::Dictionary ),
	vector_( ref new Platform::Collections::Vector<AmfPair^>( ) )
{ }

Platform::Array<uint8>^ AmfDictionary::Sequencify()
{
	return amf0_sequencer::sequencify( this );
}

Platform::Array<uint8>^ AmfDictionary::Sequencify( AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf3 )
		return amf3_sequencer::sequencify( this );

	return amf0_sequencer::sequencify( this );
}

bool AmfDictionary::GetBoolean() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
float64 AmfDictionary::GetNumber() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
Platform::String^ AmfDictionary::GetString() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
Windows::Foundation::DateTime AmfDictionary::GetDate() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
Platform::Array<uint8>^ AmfDictionary::GetByteArray() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
Windows::Foundation::Collections::IVector<int32>^ AmfDictionary::GetVectorInt() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
Windows::Foundation::Collections::IVector<uint32>^ AmfDictionary::GetVectorUint() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
Windows::Foundation::Collections::IVector<float64>^ AmfDictionary::GetVectorDouble() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
Windows::Foundation::Collections::IVector<IAmfValue^>^ AmfDictionary::GetVectorObject() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
AmfObject^ AmfDictionary::GetObject() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }
AmfArray^ AmfDictionary::GetArray() { throw com_exception_helper::create_invalid_operation_exception( "Invalid value type." ); }

AmfDictionary^ AmfDictionary::GetDictionary()
{
	if( ValueType_ != AmfValueType::Dictionary )
		throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." );

	return safe_cast<AmfDictionary^>( this );
}

void AmfDictionary::SetPairAt( uint32 index, IAmfValue^ key, IAmfValue^ value ) { vector_->SetAt( index, ref new AmfPair( key, value ) ); }
void AmfDictionary::InsertPairAt( uint32 index, IAmfValue^ key, IAmfValue^ value ) { vector_->InsertAt( index, ref new AmfPair( key, value ) ); }
void AmfDictionary::AppendPair( IAmfValue^ key, IAmfValue^ value ) { vector_->Append( ref new AmfPair( key, value ) ); }

Windows::Foundation::Collections::IIterator<AmfPair^>^ AmfDictionary::First( ) { return vector_->First( ); }

AmfPair^ AmfDictionary::GetAt( uint32 index ) { return vector_->GetAt( index ); }
Windows::Foundation::Collections::IVectorView<AmfPair^>^ AmfDictionary::GetView( ) { return vector_->GetView( ); }
bool AmfDictionary::IndexOf( AmfPair^ value, uint32 *index ) { return vector_->IndexOf( value, index ); }

void AmfDictionary::SetAt( uint32 index, AmfPair^ value ) { vector_->SetAt( index, value ); }
void AmfDictionary::InsertAt( uint32 index, AmfPair^ value ) { vector_->InsertAt( index, value ); }
void AmfDictionary::RemoveAt( uint32 index ) { vector_->RemoveAt( index ); }
void AmfDictionary::Append( AmfPair^ value ) { vector_->Append( value ); }
void AmfDictionary::RemoveAtEnd() { vector_->RemoveAtEnd(); }
void AmfDictionary::Clear() { vector_->Clear(); }

uint32 AmfDictionary::GetMany( uint32 startIndex, Platform::WriteOnlyArray<AmfPair^>^ items ) { return vector_->GetMany( startIndex, items ); }
void AmfDictionary::ReplaceAll( const Platform::Array<AmfPair^>^ items ) { vector_->ReplaceAll( items ); }

#if !_WINDOWS_PHONE8
Platform::String^ AmfDictionary::ToString()
{
	std::wstring buf;
	buf += '{';
	for( const auto& item : vector_ )
	{
		const auto& str = item->ToString();
		buf += std::wstring( str->Data(), str->Length() );
		buf += L", ";
	}

	const auto& length = buf.length();
	if( length != 1 )
		buf.erase( length - 2 );
	buf += L'}';
	return Platform::StringReference( buf.c_str(), buf.length() );
}
#endif

AmfDictionary^ AmfDictionary::Parse( const Platform::Array<uint8>^ input )
{
	return reinterpret_cast<AmfDictionary^>( amf0_parser::parse( input ) );
}

AmfDictionary^ AmfDictionary::Parse( const Platform::Array<uint8>^ input, AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf3 )
		return reinterpret_cast<AmfDictionary^>( amf3_parser::parse( input ) );

	return reinterpret_cast<AmfDictionary^>( amf0_parser::parse( input ) );
}

bool AmfDictionary::TryParse( const Platform::Array<uint8>^ input, AmfDictionary^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	return amf0_parser::try_parse( input, buf );
}

bool AmfDictionary::TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfDictionary^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	if( type == AmfEncodingType::Amf3 )
		return amf3_parser::try_parse( input, buf );

	return amf0_parser::try_parse( input, buf );
}

void AmfDictionary::SetData( std::vector<AmfPair^> data )
{
	vector_ = ref new Platform::Collections::Vector<AmfPair^>( std::move( data ) );
}