#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfUndefinedValueUnitTest )
{
	TEST_METHOD( AmfNullValue_CreateTest )
	{
		const auto& val = CreateDefaultNull();
		Assert::IsTrue( val->ValueType == AmfValueType::Null );
	}

	TEST_METHOD( AmfNullValue_GetBooleanTest )
	{
		const auto& val = CreateDefaultNull();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetBoolean();
		} );
	}

	TEST_METHOD( AmfNullValue_GetVectorObjectTest )
	{
		const auto& val = CreateDefaultNull();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfNullValue_GetIntegerTest )
	{
		const auto& val = CreateDefaultNull();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetNumber();
		} );
	}

	TEST_METHOD( AmfNullValue_GetStringTest )
	{
		const auto& val = CreateDefaultNull();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetString();
		} );
	}

	TEST_METHOD( AmfNullValue_GetDateTest )
	{
		const auto& val = CreateDefaultNull();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDate();
		} );
	}

	TEST_METHOD( AmfNullValue_GetByteArrayTest )
	{
		const auto& val = CreateDefaultNull();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetByteArray();
		} );
	}

	TEST_METHOD( AmfNullValue_GetVectorIntTest )
	{
		const auto& val = CreateDefaultNull();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfNullValue_GetVectorUintTest )
	{
		const auto& val = CreateDefaultNull();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfNullValue_GetVectorDoubleTest )
	{
		const auto& val = CreateDefaultNull();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfNullValue_GetObjectTest )
	{
		const auto& val = CreateDefaultNull();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetObject();
		} );
	}

	TEST_METHOD( AmfNullValue_GetArrayTest )
	{
		const auto& val = CreateDefaultNull();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetArray();
		} );
	}

	TEST_METHOD( AmfNullValue_GetDictionaryTest )
	{
		const auto& val = CreateDefaultNull();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDictionary();
		} );
	}

	TEST_METHOD( AmfNullValue_ToStringTest )
	{
		const auto& val = CreateDefaultNull();
		Assert::AreEqual( L"null", val->ToString() );
	}

private:
	AmfValue^ CreateDefaultNull()
	{
		return ref new AmfValue();
	}
};
