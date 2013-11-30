#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfByteArrayValueUnitTest )
{
public:
	TEST_METHOD( AmfByteArrayValue_CreateTest )
	{
		const auto& val = CreateDefaultByteArray();
		Assert::IsTrue( val->ValueType == AmfValueType::ByteArray );
	}

	TEST_METHOD( AmfByteArrayValue_GetBooleanTest )
	{
		const auto& val = CreateDefaultByteArray();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetBoolean();
		} );
	}

	TEST_METHOD( AmfByteArrayValue_GetNumberTest )
	{
		const auto& val = CreateDefaultByteArray();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetNumber();
		} );
	}

	TEST_METHOD( AmfByteArrayValue_GetStringTest )
	{
		const auto& val = CreateDefaultByteArray();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetString();
		} );
	}

	TEST_METHOD( AmfByteArrayValue_GetDateTest )
	{
		const auto& val = CreateDefaultByteArray();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDate();
		} );
	}

	TEST_METHOD( AmfByteArrayValue_GetByteArrayTest )
	{
		const auto& val = CreateDefaultByteArray();
		AssertHelper::AreArrayEqual( testByteArray_, val->GetByteArray() );
	}

	TEST_METHOD( AmfByteArrayValue_GetVectorIntTest )
	{
		const auto& val = CreateDefaultByteArray();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfByteArrayValue_GetVectorUintTest )
	{
		const auto& val = CreateDefaultByteArray();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfByteArrayValue_GetVectorDoubleTest )
	{
		const auto& val = CreateDefaultByteArray();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfByteArrayValue_GetVectorObjectTest )
	{
		const auto& val = CreateDefaultByteArray();

		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfByteArrayValue_GetObjectTest )
	{
		const auto& val = CreateDefaultByteArray();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetObject();
		} );
	}

	TEST_METHOD( AmfByteArrayValue_GetArrayTest )
	{
		const auto& val = CreateDefaultByteArray();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetArray();
		} );
	}

	TEST_METHOD( AmfByteArrayValue_GetDictionaryTest )
	{
		const auto& val = CreateDefaultByteArray();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDictionary();
		} );
	}

	TEST_METHOD( AmfByteArrayValue_ToStringTest )
	{
		const auto& val = CreateDefaultByteArray();
		Assert::AreEqual( L"[0x5, 0x4, 0x20, 0x16]", val->ToString() );
	}

private:
	AmfValue^ CreateDefaultByteArray()
	{
		return AmfValue::CreateByteArrayValue( testByteArray_ );
	}

	U8Array^ CreateTestArray()
	{
		return ref new U8Array{ 5, 4, 32, 22 };
	}

	U8Array^ testByteArray_ = CreateTestArray();
};