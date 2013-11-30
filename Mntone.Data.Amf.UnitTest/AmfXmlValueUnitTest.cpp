#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfXmlValueUnitTest )
{
public:
	TEST_METHOD( AmfXmlValue_CreateTest )
	{
		const auto& val = GeneralCareteAmfValue();
		Assert::IsTrue( AmfValueType::Xml == val->ValueType );
	}

	TEST_METHOD( AmfXmlValue_GetBooleanTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetBoolean();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetNumberTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetNumber();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetStringTest )
	{
		const auto& val = GeneralCareteAmfValue();
		auto getStringValue = val->GetString();
		Assert::AreEqual( generalTestValue_, getStringValue );
	}

	TEST_METHOD( AmfXmlValue_GetDateTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDate();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetByteArrayTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetByteArray();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetVectorIntTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetVectorUintTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetVectorDoubleTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetObjectTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetObject();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetVectorObjectTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetArrayTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetArray();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetDictionaryTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDictionary();
		} );
	}

	TEST_METHOD( AmfXmlValue_ToStringTest )
	{
		const auto& val = GeneralCareteAmfValue();
		Assert::AreEqual( L"\"<test></test>\"", val->ToString() );
	}

private:
	AmfValue^ GeneralCareteAmfValue()
	{
		return AmfValue::CreateXmlValue( generalTestValue_ );
	}

	Platform::String^ generalTestValue_ = L"<test></test>";
};