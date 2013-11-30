#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfDateValueUnitTest )
{
public:
	TEST_METHOD( AmfDateValue_CreateTest )
	{
		const auto& val = CreateDefaultDate();
		Assert::IsTrue( val->ValueType == AmfValueType::Date );
	}

	TEST_METHOD( AmfDateValue_GetBooleanTest )
	{
		const auto& val = CreateDefaultDate();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetBoolean();
		} );
	}

	TEST_METHOD( AmfDateValue_GetNumberTest )
	{
		const auto& val = CreateDefaultDate();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetNumber();
		} );
	}

	TEST_METHOD( AmfDateValue_GetStringTest )
	{
		const auto& val = CreateDefaultDate();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetString();
		} );
	}

	TEST_METHOD( AmfDateValue_GetDateTest )
	{
		const auto& val = CreateDefaultDate();
		Assert::IsTrue( generalTestValue_.UniversalTime == val->GetDate().UniversalTime );
	}

	TEST_METHOD( AmfDateValue_GetByteArrayTest )
	{
		const auto& val = CreateDefaultDate();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetByteArray();
		} );
	}

	TEST_METHOD( AmfDateValue_GetVectorIntTest )
	{
		const auto& val = CreateDefaultDate();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfDateValue_GetVectorUintTest )
	{
		const auto& val = CreateDefaultDate();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfDateValue_GetVectorDoubleTest )
	{
		const auto& val = CreateDefaultDate();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfDateValue_GetVectorObjectTest )
	{
		const auto& val = CreateDefaultDate();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfDateValue_GetObjectTest )
	{
		const auto& val = CreateDefaultDate();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetObject();
		} );
	}

	TEST_METHOD( AmfDateValue_GetArrayTest )
	{
		const auto& val = CreateDefaultDate();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetArray();
		} );
	}

	TEST_METHOD( AmfDateValue_GetDictionaryTest )
	{
		const auto& val = CreateDefaultDate();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDictionary();
		} );
	}

	TEST_METHOD( AmfDateValue_ToStringTest )
	{
		const auto& val = CreateDefaultDate();
		Assert::AreEqual( generalTestValue_.ToString(), val->ToString() );
	}

private:
	AmfValue^ CreateDefaultDate()
	{
		return AmfValue::CreateDateValue( generalTestValue_ );
	}

	Windows::Foundation::DateTime generalTestValue_ = AssertHelper::GetDate( 2013, 10, 30 );
};