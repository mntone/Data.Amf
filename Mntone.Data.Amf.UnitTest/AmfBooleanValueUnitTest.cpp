#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfBooleanValueUnitTest )
{
public:
	TEST_METHOD( AmfBooleanValue_CreateTest )
	{
		const auto& val = GeneralCareteAmfValue();
		Assert::IsTrue( AmfValueType::Boolean == val->ValueType );
	}

	TEST_METHOD( AmfBooleanValue_GetBooleanTest )
	{
		const auto& val = GeneralCareteAmfValue();
		auto booleanValue = val->GetBoolean();
		Assert::AreEqual( generalTestValue_, booleanValue );
	}

	TEST_METHOD( AmfBooleanValue_GetNumberTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetNumber();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetStringTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetString();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetDateTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDate();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetByteArrayTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetByteArray();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetVectorIntTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetVectorUintTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetVectorDoubleTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetVectorObjectTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetObjectTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetObject();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetArrayTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetArray();
		} );
	}

	TEST_METHOD( AmfBooleanValue_GetDictionaryTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDictionary();
		} );
	}

	TEST_METHOD( AmfBooleanValue_ToStringTest )
	{
		const auto& val = GeneralCareteAmfValue();
		auto toStringValue = val->ToString();
		Assert::AreEqual( generalTestValue_.ToString(), toStringValue );
	}

private:
	AmfValue^ GeneralCareteAmfValue()
	{
		return AmfValue::CreateBooleanValue( generalTestValue_ );
	}

	bool generalTestValue_ = false;
};