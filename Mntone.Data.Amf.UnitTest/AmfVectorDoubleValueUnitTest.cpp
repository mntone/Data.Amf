#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfVectorDoubleValueUnitTest )
{
public:
	TEST_METHOD( AmfVectorDoubleValue_CreateTest )
	{
		const auto& val = CreateDefaultVectorDouble();
		Assert::IsTrue( val->ValueType == AmfValueType::VectorDouble );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetBooleanTest )
	{
		const auto& val = CreateDefaultVectorDouble();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetBoolean();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetVectorObjectTest )
	{
		const auto& val = CreateDefaultVectorDouble();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetNumberTest )
	{
		const auto& val = CreateDefaultVectorDouble();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetNumber();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetStringTest )
	{
		const auto& val = CreateDefaultVectorDouble();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetString();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetDateTest )
	{
		const auto& val = CreateDefaultVectorDouble();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDate();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetByteArrayTest )
	{
		const auto& val = CreateDefaultVectorDouble();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetByteArray();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetVectorIntTest )
	{
		const auto& val = CreateDefaultVectorDouble();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetVectorUintTest )
	{
		const auto& val = CreateDefaultVectorDouble();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetVectorDoubleTest )
	{
		const auto& val = CreateDefaultVectorDouble();
		AssertHelper::AreVectorEqual( generalTestVector_, val->GetVectorDouble() );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetObjectTest )
	{
		const auto& val = CreateDefaultVectorDouble();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetObject();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetArrayTest )
	{
		const auto& val = CreateDefaultVectorDouble();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetArray();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetDictionaryTest )
	{
		const auto& val = CreateDefaultVectorDouble();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDictionary();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_ToStringTest )
	{
		const auto& val = CreateDefaultVectorDouble();
		Assert::AreEqual( L"[5.6, 44, 22.2]", val->ToString() );
	}

private:
	AmfValue^ CreateDefaultVectorDouble()
	{
		return AmfValue::CreateVectorDoubleValue( generalTestVector_ );
	}

	Windows::Foundation::Collections::IVector<float64>^ CreateGeneralTestVector()
	{
		return ref new Platform::Collections::Vector<float64>{ 5.6, 44.0, 22.2 };
	}

	Windows::Foundation::Collections::IVector<float64>^ generalTestVector_ = CreateGeneralTestVector();
};