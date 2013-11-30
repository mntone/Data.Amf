#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfVectorUintValueUnitTest )
{
public:
	TEST_METHOD( AmfVectorUintValue_CreateTest )
	{
		const auto& val = CreateDefaultVectorUint();
		Assert::IsTrue( val->ValueType == AmfValueType::VectorUint );
	}

	TEST_METHOD( AmfVectorUintValue_GetBooleanTest )
	{
		const auto& val = CreateDefaultVectorUint();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetBoolean();
		} );
	}

	TEST_METHOD( AmfVectorUintValue_GetNumberTest )
	{
		const auto& val = CreateDefaultVectorUint();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetNumber();
		} );
	}

	TEST_METHOD( AmfVectorUintValue_GetStringTest )
	{
		const auto& val = CreateDefaultVectorUint();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetString();
		} );
	}

	TEST_METHOD( AmfVectorUintValue_GetDateTest )
	{
		const auto& val = CreateDefaultVectorUint();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDate();
		} );
	}

	TEST_METHOD( AmfVectorUintValue_GetByteArrayTest )
	{
		const auto& val = CreateDefaultVectorUint();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetByteArray();
		} );
	}

	TEST_METHOD( AmfVectorUintValue_GetVectorIntTest )
	{
		const auto& val = CreateDefaultVectorUint();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfVectorUintValue_GetVectorUintTest )
	{
		const auto& val = CreateDefaultVectorUint();
		AssertHelper::AreVectorEqual( generalTestVector_, val->GetVectorUint() );
	}

	TEST_METHOD( AmfVectorUintValue_GetVectorDoubleTest )
	{
		const auto& val = CreateDefaultVectorUint();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfVectorUintValue_GetVectorObjectTest )
	{
		const auto& val = CreateDefaultVectorUint();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfVectorUintValue_GetObjectTest )
	{
		const auto& val = CreateDefaultVectorUint();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetObject();
		} );
	}

	TEST_METHOD( AmfVectorUintValue_GetArrayTest )
	{
		const auto& val = CreateDefaultVectorUint();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetArray();
		} );
	}

	TEST_METHOD( AmfVectorUintValue_GetDictionaryTest )
	{
		const auto& val = CreateDefaultVectorUint();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDictionary();
		} );
	}

	TEST_METHOD( AmfVectorUintValue_ToStringTest )
	{
		const auto& val = CreateDefaultVectorUint();
		Assert::AreEqual( L"[47, 44, 22]", val->ToString() );
	}

private:
	AmfValue^ CreateDefaultVectorUint()
	{
		return AmfValue::CreateVectorUintValue( generalTestVector_ );
	}

	Windows::Foundation::Collections::IVector<uint32>^ CreateTestVector()
	{
		return ref new Platform::Collections::Vector<uint32>{ 47, 44, 22 };
	}

	Windows::Foundation::Collections::IVector<uint32>^ generalTestVector_ = CreateTestVector();
};