#include "pch.h"
#include "AmfValue.h"
#include "AmfArray.h"
#include "AmfObject.h"
#include "Amf0Parser.h"

namespace Mntone { namespace Data { namespace Amf {

	AmfValue::AmfValue( void ):
		_ValueType( AmfValueType::Null ),
		_Value( nullptr )
	{ }

	Platform::Array<uint8>^ AmfValue::Sequenceify( void )
	{
		throw ref new Platform::NotImplementedException();
	}

	Platform::Array<uint8>^ AmfValue::Sequenceify( AmfEncodingType type )
	{
		throw ref new Platform::NotImplementedException();
	}

	bool AmfValue::GetBoolean( void ) { return safe_cast<bool>( _Value ); }
	float64 AmfValue::GetDouble( void ) { return safe_cast<float64>( _Value ); }
	int32 AmfValue::GetInteger( void ) { return safe_cast<int32>( _Value ); }
	Platform::String^ AmfValue::GetString( void ) { return safe_cast<Platform::String^>( _Value ); }
	uint16 AmfValue::GetReference( void ) { return safe_cast<uint16>( _Value ); }
	Windows::Foundation::DateTime AmfValue::GetDate( void ) { return safe_cast<Windows::Foundation::DateTime>( _Value ); }
	AmfObject^ AmfValue::GetObject( void ) { throw ref new Platform::FailureException(); }
	AmfArray^ AmfValue::GetArray( void ) { throw ref new Platform::FailureException(); }

	AmfValue^ AmfValue::CreateUndefinedValue( void )
	{
		auto out = ref new AmfValue();
		out->_ValueType = AmfValueType::Undefined;
		out->_Value = nullptr;
		return out;
	}

	AmfValue^ AmfValue::CreateBooleanValue( bool input )
	{
		auto out = ref new AmfValue();
		out->_ValueType = AmfValueType::Boolean;
		out->_Value = input;
		return out;
	}

	AmfValue^ AmfValue::CreateDoubleValue( float64 input )
	{
		auto out = ref new AmfValue();
		out->_ValueType = AmfValueType::Double;
		out->_Value = input;
		return out;
	}

	AmfValue^ AmfValue::CreateIntegerValue( int32 input )
	{
		auto out = ref new AmfValue();
		out->_ValueType = AmfValueType::Integer;
		out->_Value = input;
		return out;
	}

	AmfValue^ AmfValue::CreateStringValue( Platform::String^ input )
	{
		auto out = ref new AmfValue();
		out->_ValueType = AmfValueType::String;
		out->_Value = input;
		return out;
	}

	AmfValue^ AmfValue::CreateReferenceValue( uint16 input )
	{
		auto out = ref new AmfValue();
		out->_ValueType = AmfValueType::Reference;
		out->_Value = input;
		return out;
	}

	AmfValue^ AmfValue::CreateDateValue( Windows::Foundation::DateTime input )
	{
		auto out = ref new AmfValue();
		out->_ValueType = AmfValueType::Date;
		out->_Value = input;
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
			return safe_cast<AmfValue^>( Amf0Parser::Parse( input ) );

		//return safe_cast<AmfValue^>( Amf3Parser::Parse( input ) );
		throw ref new Platform::NotImplementedException();
	}

	bool AmfValue::TryParse( const Platform::Array<uint8>^ input, AmfValue^* result )
	{
		//IAmfValue^ buf = *result;
		//return Amf3Parser::TryParse( input, &buf );
		throw ref new Platform::NotImplementedException();
	}

	bool AmfValue::TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfValue^* result )
	{
		IAmfValue^ buf = *result;
		if( type == AmfEncodingType::Amf0 )
			return Amf0Parser::TryParse( input, &buf );

		//return Amf3Parser::TryParse( input, &buf );
		throw ref new Platform::NotImplementedException();
	}

} } }