#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfVectorIntValueUnitTest )
{
public:
	TEST_METHOD( AmfVectorIntValue_CreateTest )
	{
		const auto& val = CreateDefaultVectorInt();
		Assert::IsTrue( val->ValueType == AmfValueType::VectorInt );
	}

	TEST_METHOD( AmfVectorIntValue_GetBooleanTest )
	{
		const auto& val = CreateDefaultVectorInt();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetBoolean();
		} );
	}

	TEST_METHOD( AmfVectorIntValue_GetVectorObjectTest )
	{
		const auto& val = CreateDefaultVectorInt();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfVectorIntValue_GetNumberTest )
	{
		const auto& val = CreateDefaultVectorInt();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetNumber();
		} );
	}

	TEST_METHOD( AmfVectorIntValue_GetStringTest )
	{
		const auto& val = CreateDefaultVectorInt();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetString();
		} );
	}

	TEST_METHOD( AmfVectorIntValue_GetDateTest )
	{
		const auto& val = CreateDefaultVectorInt();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDate();
		} );
	}

	TEST_METHOD( AmfVectorIntValue_GetByteArrayTest )
	{
		const auto& val = CreateDefaultVectorInt();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetByteArray();
		} );
	}

	TEST_METHOD( AmfVectorIntValue_GetVectorIntTest )
	{
		const auto& val = CreateDefaultVectorInt();
		auto vectorIntValue = val->GetVectorInt();
		AssertHelper::AreVectorEqual( generalTestVector_, vectorIntValue );
	}

	TEST_METHOD( AmfVectorIntValue_GetVectorUintTest )
	{
		const auto& val = CreateDefaultVectorInt();
		AssertHelper::AreVectorEqual( generalTestVector_, val->GetVectorInt() );
	}

	TEST_METHOD( AmfVectorIntValue_GetVectorDoubleTest )
	{
		const auto& val = CreateDefaultVectorInt();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfVectorIntValue_GetObjectTest )
	{
		const auto& val = CreateDefaultVectorInt();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetObject();
		} );
	}

	TEST_METHOD( AmfVectorIntValue_GetArrayTest )
	{
		const auto& val = CreateDefaultVectorInt();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetArray();
		} );
	}

	TEST_METHOD( AmfVectorIntValue_GetDictionaryTest )
	{
		const auto& val = CreateDefaultVectorInt();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDictionary();
		} );
	}

	TEST_METHOD( AmfVectorIntValue_ToStringTest )
	{
		const auto& val = CreateDefaultVectorInt();
		Assert::AreEqual( L"[3, -2, 5, 63, 2]", val->ToString() );
	}

private:
	AmfValue^ CreateDefaultVectorInt()
	{
		return AmfValue::CreateVectorIntValue( generalTestVector_ );
	}

	Windows::Foundation::Collections::IVector<int32>^ CreateTestVector()
	{
		return ref new Platform::Collections::Vector<int32>{ 3, -2, 5, 63, 2 };
	}

	Windows::Foundation::Collections::IVector<int32>^ generalTestVector_ = CreateTestVector();
};