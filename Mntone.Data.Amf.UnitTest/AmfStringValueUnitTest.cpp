#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfStringValueUnitTest )
{
public:
	TEST_METHOD( AmfStringValue_CreateTest )
	{
		const auto& val = CreateDefaultString();
		Assert::IsTrue( val->ValueType == AmfValueType::String );
	}

	TEST_METHOD( AmfStringValue_GetBooleanTest )
	{
		const auto& val = CreateDefaultString();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetBoolean();
		} );
	}

	TEST_METHOD( AmfStringValue_GetNumberTest )
	{
		const auto& val = CreateDefaultString();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetNumber();
		} );
	}

	TEST_METHOD( AmfStringValue_GetStringTest )
	{
		const auto& val = CreateDefaultString();
		Assert::AreEqual( generalTestValue_, val->GetString() );
	}

	TEST_METHOD( AmfStringValue_GetDateTest )
	{
		const auto& val = CreateDefaultString();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDate();
		} );
	}

	TEST_METHOD( AmfStringValue_GetByteArrayTest )
	{
		const auto& val = CreateDefaultString();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetByteArray();
		} );
	}

	TEST_METHOD( AmfStringValue_GetVectorIntTest )
	{
		const auto& val = CreateDefaultString();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfStringValue_GetVectorUintTest )
	{
		const auto& val = CreateDefaultString();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfStringValue_GetVectorDoubleTest )
	{
		const auto& val = CreateDefaultString();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfStringValue_GetVectorObjectTest )
	{
		const auto& val = CreateDefaultString();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfStringValue_GetObjectTest )
	{
		const auto& val = CreateDefaultString();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetObject();
		} );
	}

	TEST_METHOD( AmfStringValue_GetArrayTest )
	{
		const auto& val = CreateDefaultString();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetArray();
		} );
	}

	TEST_METHOD( AmfStringValue_GetDictionaryTest )
	{
		const auto& val = CreateDefaultString();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDictionary();
		} );
	}

	TEST_METHOD( AmfStringValue_ToStringTest )
	{
		const auto& val = CreateDefaultString();
		Assert::AreEqual( L"\"" + generalTestValue_ + L"\"", val->ToString() );
	}

private:
	AmfValue^ CreateDefaultString()
	{
		return AmfValue::CreateStringValue( generalTestValue_ );
	}

	Platform::String^ generalTestValue_ = ref new Platform::String( L"testValue" );
};