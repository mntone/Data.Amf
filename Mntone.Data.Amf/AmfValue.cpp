#include "pch.h"
#include "AmfValue.h"
#include "Amf0Parser.h"
#include "Amf0Sequencer.h"

using namespace Mntone::Data::Amf;

AmfValue::AmfValue( void ) :
	ValueType_( AmfValueType::Null ),
	value_( nullptr )
{ }

Platform::Array<uint8>^ AmfValue::Sequenceify( void )
{
	throw ref new Platform::NotImplementedException();
}

Platform::Array<uint8>^ AmfValue::Sequenceify( AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf0 )
		return Amf0Sequencer::Sequenceify( this );

	throw ref new Platform::NotImplementedException();
}

bool AmfValue::GetBoolean( void ) { return safe_cast<bool>( value_ ); }
float64 AmfValue::GetDouble( void ) { return safe_cast<float64>( value_ ); }
int32 AmfValue::GetInteger( void ) { return safe_cast<int32>( value_ ); }
Platform::String^ AmfValue::GetString( void ) { return safe_cast<Platform::String^>( value_ ); }
Windows::Foundation::DateTime AmfValue::GetDate( void ) { return safe_cast<Windows::Foundation::DateTime>( value_ ); }
Platform::Array<uint8>^ AmfValue::GetByteArray( void ) { return safe_cast<Platform::Array<uint8>^>( value_ ); }
Windows::Foundation::Collections::IVector<int32>^ AmfValue::GetVectorInt( void ) { return safe_cast<Platform::Collections::Vector<int32>^>( value_ ); }
Windows::Foundation::Collections::IVector<uint32>^ AmfValue::GetVectorUint( void ) { return safe_cast<Platform::Collections::Vector<uint32>^>( value_ ); }
Windows::Foundation::Collections::IVector<float64>^ AmfValue::GetVectorDouble( void ) { return safe_cast<Platform::Collections::Vector<float64>^>( value_ ); }
Windows::Foundation::Collections::IVector<IAmfValue^>^ AmfValue::GetVectorObject( void ) { return safe_cast<Platform::Collections::Vector<IAmfValue^>^>( value_ ); }
AmfObject^ AmfValue::GetObject( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
AmfArray^ AmfValue::GetArray( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }

#if !_WINDOWS_PHONE
Platform::String^ AmfValue::ToString( void ) { return value_->ToString(); }
#endif

AmfValue^ AmfValue::CreateUndefinedValue( void )
{
	auto out = ref new AmfValue();
	out->ValueType_ = AmfValueType::Undefined;
	out->value_ = nullptr;
	return out;
}

AmfValue^ AmfValue::CreateBooleanValue( bool input )
{
	auto out = ref new AmfValue();
	out->ValueType_ = AmfValueType::Boolean;
	out->value_ = input;
	return out;
}

AmfValue^ AmfValue::CreateDoubleValue( float64 input )
{
	auto out = ref new AmfValue();
	out->ValueType_ = AmfValueType::Double;
	out->value_ = input;
	return out;
}

AmfValue^ AmfValue::CreateIntegerValue( int32 input )
{
	auto out = ref new AmfValue();
	out->ValueType_ = AmfValueType::Integer;
	out->value_ = input;
	return out;
}

AmfValue^ AmfValue::CreateStringValue( Platform::String^ input )
{
	auto out = ref new AmfValue();
	out->ValueType_ = AmfValueType::String;
	out->value_ = input;
	return out;
}

AmfValue^ AmfValue::CreateDateValue( Windows::Foundation::DateTime input )
{
	auto out = ref new AmfValue();
	out->ValueType_ = AmfValueType::Date;
	out->value_ = input;
	return out;
}

AmfValue^ AmfValue::CreateXmlValue( Platform::String^ input )
{
	auto out = ref new AmfValue();
	out->ValueType_ = AmfValueType::Xml;
	out->value_ = input;
	return out;
}

AmfValue^ AmfValue::CreateByteArrayValue( const Platform::Array<uint8>^ input )
{
	auto out = ref new AmfValue();
	out->ValueType_ = AmfValueType::ByteArray;
	out->value_ = ref new Platform::Array<uint8>( input );
	return out;
}

AmfValue^ AmfValue::CreateByteArrayValue( std::vector<uint8> input )
{
	auto out = ref new AmfValue();
	out->ValueType_ = AmfValueType::ByteArray;
	out->value_ = ref new Platform::Array<uint8>( input.data(), static_cast<uint32>( input.size() ) );
	return out;
}

AmfValue^ AmfValue::CreateVectorIntValue( Windows::Foundation::Collections::IVector<int32>^ input )
{
	auto out = ref new AmfValue();
	out->ValueType_ = AmfValueType::VectorInt;
	out->value_ = input;
	return out;
}

AmfValue^ AmfValue::CreateVectorUintValue( Windows::Foundation::Collections::IVector<uint32>^ input )
{
	auto out = ref new AmfValue();
	out->ValueType_ = AmfValueType::VectorUint;
	out->value_ = input;
	return out;
}

AmfValue^ AmfValue::CreateVectorDoubleValue( Windows::Foundation::Collections::IVector<float64>^ input )
{
	auto out = ref new AmfValue();
	out->ValueType_ = AmfValueType::VectorDouble;
	out->value_ = input;
	return out;
}

AmfValue^ AmfValue::CreateVectorObjectValue( Windows::Foundation::Collections::IVector<IAmfValue^>^ input )
{
	auto out = ref new AmfValue();
	out->ValueType_ = AmfValueType::VectorObject;
	out->value_ = input;
	return out;
}

AmfValue^ AmfValue::CreateVectorObjectValue( void )
{
	auto out = ref new AmfValue( );
	out->ValueType_ = AmfValueType::VectorObject;
	return out;
}

void AmfValue::SetData( Platform::Object^ input )
{
	value_ = input;
}

AmfValue^ AmfValue::Parse( const Platform::Array<uint8>^ input )
{
	//return safe_cast<AmfValue^>( Amf3Parser::Parse( input ) );
	throw ref new Platform::NotImplementedException();
}

AmfValue^ AmfValue::Parse( const Platform::Array<uint8>^ input, AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf0 )
		return reinterpret_cast<AmfValue^>( Amf0Parser::Parse( input ) );

	//return safe_cast<AmfValue^>( Amf3Parser::Parse( input ) );
	throw ref new Platform::NotImplementedException();
}

bool AmfValue::TryParse( const Platform::Array<uint8> ^ /*input*/, AmfValue^* /*result*/ )
{
	//IAmfValue^ buf = *result;
	//return Amf3Parser::TryParse( input, &buf );
	throw ref new Platform::NotImplementedException();
}

bool AmfValue::TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfValue^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	if( type == AmfEncodingType::Amf0 )
		return Amf0Parser::TryParse( input, buf );

	//return Amf3Parser::TryParse( input, &buf );
	throw ref new Platform::NotImplementedException();
}