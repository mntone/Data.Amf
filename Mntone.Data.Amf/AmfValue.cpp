#include "pch.h"
#include "AmfValue.h"
#include "Amf0Parser.h"
#include "Amf0Sequencer.h"
#include "Amf3Parser.h"
#include "Amf3Sequencer.h"
#include "COMExceptionHelper.h"

using namespace Mntone::Data::Amf;

AmfValue::AmfValue( void ) :
ValueType_( AmfValueType::Null ),
	value_( nullptr )
{ }

Platform::Array<uint8>^ AmfValue::Sequencify( void )
{
	return Amf3Sequencer::Sequencify( this );
}

Platform::Array<uint8>^ AmfValue::Sequencify( AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf0 )
		return Amf0Sequencer::Sequencify( this );

	return Amf3Sequencer::Sequencify( this );
}

bool AmfValue::GetBoolean( void )
{
	if( ValueType_ != AmfValueType::Boolean )
		throw COMExceptionHelper::CreateInvalidOperationException( L"Invalid value type." );

	return safe_cast<bool>( value_ );
}

float64 AmfValue::GetDouble( void )
{
	if( ValueType_ != AmfValueType::Double )
		throw COMExceptionHelper::CreateInvalidOperationException( L"Invalid value type." );

	return safe_cast<float64>( value_ );
}

uint32 AmfValue::GetInteger( void )
{
	if( ValueType_ != AmfValueType::Integer )
		throw COMExceptionHelper::CreateInvalidOperationException( L"Invalid value type." );

	return safe_cast<uint32>( value_ );
}

Platform::String^ AmfValue::GetString( void )
{
	if( ValueType_ != AmfValueType::String && ValueType_ != AmfValueType::Xml )
		throw COMExceptionHelper::CreateInvalidOperationException( L"Invalid value type." );

	return safe_cast<Platform::String^>( value_ );
}

Windows::Foundation::DateTime AmfValue::GetDate( void )
{
	if( ValueType_ != AmfValueType::Date )
		throw COMExceptionHelper::CreateInvalidOperationException( L"Invalid value type." );

	return safe_cast<Windows::Foundation::DateTime>( value_ );
}

Platform::Array<uint8>^ AmfValue::GetByteArray( void )
{
	if( ValueType_ != AmfValueType::ByteArray )
		throw COMExceptionHelper::CreateInvalidOperationException( L"Invalid value type." );

	return safe_cast<Platform::Array<uint8>^>( value_ );
}

Windows::Foundation::Collections::IVector<int32>^ AmfValue::GetVectorInt( void )
{
	if( ValueType_ != AmfValueType::VectorInt )
		throw COMExceptionHelper::CreateInvalidOperationException( L"Invalid value type." );

	return safe_cast<Platform::Collections::Vector<int32>^>( value_ );
}

Windows::Foundation::Collections::IVector<uint32>^ AmfValue::GetVectorUint( void )
{
	if( ValueType_ != AmfValueType::VectorUint ) 
		throw COMExceptionHelper::CreateInvalidOperationException( L"Invalid value type." );

	return safe_cast<Platform::Collections::Vector<uint32>^>( value_ );
}

Windows::Foundation::Collections::IVector<float64>^ AmfValue::GetVectorDouble( void )
{
	if( ValueType_ != AmfValueType::VectorDouble ) 
		throw COMExceptionHelper::CreateInvalidOperationException( L"Invalid value type." );

	return safe_cast<Platform::Collections::Vector<float64>^>( value_ );
}

Windows::Foundation::Collections::IVector<IAmfValue^>^ AmfValue::GetVectorObject( void )
{
	if( ValueType_ != AmfValueType::VectorObject )
		throw COMExceptionHelper::CreateInvalidOperationException( L"Invalid value type." );

	return safe_cast<Platform::Collections::Vector<IAmfValue^>^>( value_ );
}

AmfObject^ AmfValue::GetObject( void )
{
	throw COMExceptionHelper::CreateInvalidOperationException( L"Invalid value type." );
}

AmfArray^ AmfValue::GetArray( void )
{
	throw COMExceptionHelper::CreateInvalidOperationException( L"Invalid value type." );
}

#if !_WINDOWS_PHONE
Platform::String^ AmfValue::ToString( void )
{
	switch( this->ValueType )
	{
	case AmfValueType::Undefined: return L"undefined";
	case AmfValueType::String: return L"\"" + value_->ToString() + L"\"";
	case AmfValueType::ByteArray:
		{
			auto ba = GetByteArray();
			std::wostringstream buf;
			buf.put( '[' );
			for( const auto& b : ba )
				buf << L"0x" << std::hex << b << L", ";
			auto str = buf.str();
			const auto& length = str.length();
			if( length != 1 )
				str.erase( length - 2 );
			str += L']';
			return ref new Platform::String( str.c_str(), static_cast<uint32>( str.length() ) );
		}
	case AmfValueType::VectorInt:
		{
			auto vi = GetVectorInt();
			std::wostringstream buf;
			buf.put( '[' );
			for( const auto& i : vi )
				buf << i << L", ";
			auto str = buf.str();
			const auto& length = str.length();
			if( length != 1 )
				str.erase( length - 2 );
			str += L']';
			return ref new Platform::String( str.c_str(), static_cast<uint32>( str.length() ) );
	}
	case AmfValueType::VectorUint:
		{
			auto vu = GetVectorUint();
			std::wostringstream buf;
			buf.put( '[' );
			for( const auto& u : vu )
				buf << u << L", ";
			auto str = buf.str();
			const auto& length = str.length();
			if( length != 1 )
				str.erase( length - 2 );
			str += L']';
			return ref new Platform::String( str.c_str(), static_cast<uint32>( str.length() ) );
		}
	case AmfValueType::VectorDouble:
		{
			auto vd = GetVectorDouble();
			std::wostringstream buf;
			buf.put( '[' );
			for( const auto& d : vd )
				buf << d << L", ";
			auto str = buf.str();
			const auto& length = str.length();
			if( length != 1 )
				str.erase( length - 2 );
			str += L']';
			return ref new Platform::String( str.c_str(), static_cast<uint32>( str.length() ) );
		}
	case AmfValueType::VectorObject:
		{
			auto vo = GetVectorObject();
			std::wostringstream buf;
			buf.put( '[' );
			for( const auto& o : vo )
			{
				const auto& str = o->ToString();
				buf.write( str->Data(), str->Length() );
				buf.put( L',' );
				buf.put( L' ' );
			}
			auto str = buf.str();
			const auto& length = str.length();
			if( length != 1 )
				str.erase( length - 2 );
			str += L']';
			return ref new Platform::String( str.c_str(), static_cast<uint32>( str.length() ) );
		}
	default: return value_->ToString();
	}
}
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

AmfValue^ AmfValue::CreateIntegerValue( uint32 input )
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
	auto out = ref new AmfValue();
	out->ValueType_ = AmfValueType::VectorObject;
	return out;
}

void AmfValue::SetData( Platform::Object^ input )
{
	value_ = input;
}

AmfValue^ AmfValue::Parse( const Platform::Array<uint8>^ input )
{
	return reinterpret_cast<AmfValue^>( Amf3Parser::Parse( input ) );
}

AmfValue^ AmfValue::Parse( const Platform::Array<uint8>^ input, AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf0 )
		return reinterpret_cast<AmfValue^>( Amf0Parser::Parse( input ) );

	return reinterpret_cast<AmfValue^>( Amf3Parser::Parse( input ) );
}

bool AmfValue::TryParse( const Platform::Array<uint8> ^ input, AmfValue^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	return Amf3Parser::TryParse( input, buf );
}

bool AmfValue::TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfValue^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	if( type == AmfEncodingType::Amf0 )
		return Amf0Parser::TryParse( input, buf );

	return Amf3Parser::TryParse( input, buf );
}