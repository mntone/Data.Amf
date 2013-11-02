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
AmfObject^ AmfValue::GetObject( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }
AmfArray^ AmfValue::GetArray( void ) { throw ref new Platform::FailureException( "Invalid operation." ); }

Platform::String^ AmfValue::ToString( void ) { return value_->ToString(); }

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