#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfUndefinedValueUnitTest )
{
	TEST_METHOD( AmfUndefinedValue_CreateTest )
	{
		const auto& val = CreateDefaultUndefined();
		Assert::IsTrue( val->ValueType == AmfValueType::Undefined );
	}

	TEST_METHOD( AmfUndefinedValue_GetBooleanTest )
	{
		const auto& val = CreateDefaultUndefined();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetBoolean();
		} );
	}

	TEST_METHOD( AmfUndefinedValue_GetVectorObjectTest )
	{
		const auto& val = CreateDefaultUndefined();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfUndefinedValue_GetIntegerTest )
	{
		const auto& val = CreateDefaultUndefined();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetNumber();
		} );
	}

	TEST_METHOD( AmfUndefinedValue_GetStringTest )
	{
		const auto& val = CreateDefaultUndefined();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetString();
		} );
	}

	TEST_METHOD( AmfUndefinedValue_GetDateTest )
	{
		const auto& val = CreateDefaultUndefined();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDate();
		} );
	}

	TEST_METHOD( AmfUndefinedValue_GetByteArrayTest )
	{
		const auto& val = CreateDefaultUndefined();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetByteArray();
		} );
	}

	TEST_METHOD( AmfUndefinedValue_GetVectorIntTest )
	{
		const auto& val = CreateDefaultUndefined();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfUndefinedValue_GetVectorUintTest )
	{
		const auto& val = CreateDefaultUndefined();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfUndefinedValue_GetVectorDoubleTest )
	{
		const auto& val = CreateDefaultUndefined();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfUndefinedValue_GetObjectTest )
	{
		const auto& val = CreateDefaultUndefined();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetObject();
		} );
	}

	TEST_METHOD( AmfUndefinedValue_GetArrayTest )
	{
		const auto& val = CreateDefaultUndefined();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetArray();
		} );
	}

	TEST_METHOD( AmfUndefinedValue_GetDictionaryTest )
	{
		const auto& val = CreateDefaultUndefined();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDictionary();
		} );
	}

	TEST_METHOD( AmfUndefinedValue_ToStringTest )
	{
		const auto& val = CreateDefaultUndefined();
		Assert::AreEqual( L"undefined", val->ToString() );
	}

private:
	AmfValue^ CreateDefaultUndefined()
	{
		return AmfValue::CreateUndefinedValue();
	}
};
