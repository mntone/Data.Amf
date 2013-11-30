#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfBooleanValueUnitTest )
{
public:
	TEST_METHOD( AmfBooleanValue_CreateTest )
	{
		const auto& val = CreateDefaultBoolean();
		Assert::IsTrue( val->ValueType == AmfValueType::Boolean );
	}

	TEST_METHOD( AmfBooleanValue_GetBooleanTest )
	{
		const auto& val = CreateDefaultBoolean();
		auto booleanValue = val->GetBoolean();
		Assert::AreEqual( generalTestValue_, booleanValue );
	}

	TEST_METHOD( AmfBooleanValue_GetNumberTest )
	{
		const auto& val = CreateDefaultBoolean();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetNumber();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetStringTest )
	{
		const auto& val = CreateDefaultBoolean();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetString();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetDateTest )
	{
		const auto& val = CreateDefaultBoolean();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDate();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetByteArrayTest )
	{
		const auto& val = CreateDefaultBoolean();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetByteArray();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetVectorIntTest )
	{
		const auto& val = CreateDefaultBoolean();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetVectorUintTest )
	{
		const auto& val = CreateDefaultBoolean();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetVectorDoubleTest )
	{
		const auto& val = CreateDefaultBoolean();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetVectorObjectTest )
	{
		const auto& val = CreateDefaultBoolean();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetObjectTest )
	{
		const auto& val = CreateDefaultBoolean();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetObject();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetArrayTest )
	{
		const auto& val = CreateDefaultBoolean();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetArray();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetDictionaryTest )
	{
		const auto& val = CreateDefaultBoolean();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDictionary();
		} );
	}

	TEST_METHOD( AmfBooleanValue_ToStringTest )
	{
		const auto& val = CreateDefaultBoolean();
		auto toStringValue = val->ToString();
		Assert::AreEqual( generalTestValue_.ToString(), toStringValue );
	}

private:
	AmfValue^ CreateDefaultBoolean()
	{
		return AmfValue::CreateBooleanValue( generalTestValue_ );
	}

	bool generalTestValue_ = false;
};