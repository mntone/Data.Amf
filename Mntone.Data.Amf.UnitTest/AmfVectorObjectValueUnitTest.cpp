#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfVectorObjectValueUnitTest )
{
public:
	TEST_METHOD( AmfVectorObjectValue_CreateTest )
	{
		const auto& val = CreateDefaultVectorObject();
		Assert::IsTrue( val->ValueType == AmfValueType::VectorObject );
	}

	TEST_METHOD( AmfVectorObjectValue_GetBooleanTest )
	{
		const auto& val = CreateDefaultVectorObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetBoolean();
		} );
	}

	TEST_METHOD( AmfVectorObjectValue_GetNumberTest )
	{
		const auto& val = CreateDefaultVectorObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetNumber();
		} );
	}

	TEST_METHOD( AmfVectorObjectValue_GetStringTest )
	{
		const auto& val = CreateDefaultVectorObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetString();
		} );
	}

	TEST_METHOD( AmfVectorObjectValue_GetDateTest )
	{
		const auto& val = CreateDefaultVectorObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDate();
		} );
	}

	TEST_METHOD( AmfVectorObjectValue_GetByteArrayTest )
	{
		const auto& val = CreateDefaultVectorObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetByteArray();
		} );
	}

	TEST_METHOD( AmfVectorObjectValue_GetVectorIntTest )
	{
		const auto& val = CreateDefaultVectorObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfVectorObjectValue_GetVectorUintTest )
	{
		const auto& val = CreateDefaultVectorObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfVectorObjectValue_GetVectorDoubleTest )
	{
		const auto& val = CreateDefaultVectorObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfVectorObjectValue_GetVectorObjectTest )
	{
		const auto& val = CreateDefaultVectorObject();
		Assert::AreEqual( generalTestVector_, val->GetVectorObject() );
	}

	TEST_METHOD( AmfVectorObjectValue_GetObjectTest )
	{
		const auto& val = CreateDefaultVectorObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetObject();
		} );
	}

	TEST_METHOD( AmfVectorObjectValue_GetArrayTest )
	{
		const auto& val = CreateDefaultVectorObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetArray();
		} );
	}

	TEST_METHOD( AmfVectorObjectValue_GetDictionaryTest )
	{
		const auto& val = CreateDefaultVectorObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDictionary();
		} );
	}

	TEST_METHOD( AmfVectorObjectValue_ToStringTest )
	{
		const auto& val = CreateDefaultVectorObject();
		Assert::AreEqual( L"[{}, {}]", val->ToString() );
	}

private:
	AmfValue^ CreateDefaultVectorObject()
	{
		return AmfValue::CreateVectorObjectValue( generalTestVector_ );
	}

	Windows::Foundation::Collections::IVector<IAmfValue^>^ CreateTestVector()
	{
		auto testClass1 = ref new AmfObject();
		testClass1->ClassName = "testClass1";
		auto testClass2 = ref new AmfObject();
		testClass2->ClassName = "testClass2";
		return ref new Platform::Collections::Vector<IAmfValue^>{ testClass1, testClass2 };
	}

	Windows::Foundation::Collections::IVector<IAmfValue^>^ generalTestVector_ = CreateTestVector();
};