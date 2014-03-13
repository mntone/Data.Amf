#include "pch.h"
#include "AmfValue.h"
#include "amf0_parser.h"
#include "amf0_sequencer.h"
#include "amf3_parser.h"
#include "amf3_sequencer.h"
#include "com_exception_helper.h"

using namespace mntone::data::amf;
using namespace Mntone::Data::Amf;

AmfValue::AmfValue() :
	ValueType_( AmfValueType::Null ),
	value_( nullptr )
{ }

Platform::Array<uint8>^ AmfValue::Sequencify()
{
	return amf0_sequencer::sequencify( this );
}

Platform::Array<uint8>^ AmfValue::Sequencify( AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf3 )
		return amf3_sequencer::sequencify( this );

	return amf0_sequencer::sequencify( this );
}

bool AmfValue::GetBoolean()
{
	if( ValueType_ != AmfValueType::Boolean )
		throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." );

	return safe_cast<bool>( value_ );
}

float64 AmfValue::GetNumber()
{
	if( ValueType_ != AmfValueType::Number )
		throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." );

	return safe_cast<float64>( value_ );
}

Platform::String^ AmfValue::GetString()
{
	if( ValueType_ != AmfValueType::String && ValueType_ != AmfValueType::Xml )
		throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." );

	return safe_cast<Platform::String^>( value_ );
}

Windows::Foundation::DateTime AmfValue::GetDate()
{
	if( ValueType_ != AmfValueType::Date )
		throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." );

	return safe_cast<Windows::Foundation::DateTime>( value_ );
}

Platform::Array<uint8>^ AmfValue::GetByteArray()
{
	if( ValueType_ != AmfValueType::ByteArray )
		throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." );

	return safe_cast<Platform::Array<uint8>^>( value_ );
}

Windows::Foundation::Collections::IVector<int32>^ AmfValue::GetVectorInt()
{
	if( ValueType_ != AmfValueType::VectorInt )
		throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." );

	return safe_cast<Platform::Collections::Vector<int32>^>( value_ );
}

Windows::Foundation::Collections::IVector<uint32>^ AmfValue::GetVectorUint()
{
	if( ValueType_ != AmfValueType::VectorUint ) 
		throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." );

	return safe_cast<Platform::Collections::Vector<uint32>^>( value_ );
}

Windows::Foundation::Collections::IVector<float64>^ AmfValue::GetVectorDouble()
{
	if( ValueType_ != AmfValueType::VectorDouble ) 
		throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." );

	return safe_cast<Platform::Collections::Vector<float64>^>( value_ );
}

Windows::Foundation::Collections::IVector<IAmfValue^>^ AmfValue::GetVectorObject()
{
	if( ValueType_ != AmfValueType::VectorObject )
		throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." );

	return safe_cast<Platform::Collections::Vector<IAmfValue^>^>( value_ );
}

AmfObject^ AmfValue::GetObject()
{
	throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." );
}

AmfArray^ AmfValue::GetArray()
{
	throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." );
}

AmfDictionary^ AmfValue::GetDictionary()
{
	throw com_exception_helper::create_invalid_operation_exception( L"Invalid value type." );
}

#if !_WINDOWS_PHONE
Platform::String^ AmfValue::ToString()
{
	switch( this->ValueType )
	{
	case AmfValueType::Null: return L"null";
	case AmfValueType::Undefined: return L"undefined";
	case AmfValueType::String:
	case AmfValueType::Xml:
		return L"\"" + value_->ToString() + L"\"";
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
			return Platform::StringReference( str.c_str(), str.length() );
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
			return Platform::StringReference( str.c_str(), str.length() );
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
			return Platform::StringReference( str.c_str(), str.length() );
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
			return Platform::StringReference( str.c_str(), str.length() );
		}
	case AmfValueType::VectorObject:
		{
			auto vo = GetVectorObject();

			std::wstring buf( L"[" );
			for( const auto& o : vo )
			{
				const auto& str = o->ToString();
				buf += std::wstring( str->Data(), str->Length() );
				buf += L", ";
			}

			const auto& length = buf.length();
			if( length != 1 )
				buf.erase( length - 2 );
			buf += L']';
			return Platform::StringReference( buf.c_str(), buf.length() );
		}
	default: return value_->ToString();
	}
}
#endif

AmfValue^ AmfValue::CreateUndefinedValue()
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

AmfValue^ AmfValue::CreateNumberValue( float64 input )
{
	auto out = ref new AmfValue();
	out->ValueType_ = AmfValueType::Number;
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

AmfValue^ AmfValue::CreateVectorObjectValue()
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
	return reinterpret_cast<AmfValue^>( amf0_parser::parse( input ) );
}

AmfValue^ AmfValue::Parse( const Platform::Array<uint8>^ input, AmfEncodingType type )
{
	if( type == AmfEncodingType::Amf3 )
		return reinterpret_cast<AmfValue^>( amf3_parser::parse( input ) );

	return reinterpret_cast<AmfValue^>( amf0_parser::parse( input ) );
}

bool AmfValue::TryParse( const Platform::Array<uint8> ^ input, AmfValue^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	return amf0_parser::try_parse( input, buf );
}

bool AmfValue::TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfValue^* result )
{
	auto buf = reinterpret_cast<IAmfValue^*>( result );
	if( type == AmfEncodingType::Amf3 )
		return amf3_parser::try_parse( input, buf );

	return amf0_parser::try_parse( input, buf );
}