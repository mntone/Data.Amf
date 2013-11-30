#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfXmlValueUnitTest )
{
public:
	TEST_METHOD( AmfXmlValue_CreateTest )
	{
		const auto& val = CreateDefaultXml();
		Assert::IsTrue( val->ValueType == AmfValueType::Xml );
	}

	TEST_METHOD( AmfXmlValue_GetBooleanTest )
	{
		const auto& val = CreateDefaultXml();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetBoolean();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetNumberTest )
	{
		const auto& val = CreateDefaultXml();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetNumber();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetStringTest )
	{
		const auto& val = CreateDefaultXml();
		auto getStringValue = val->GetString();
		Assert::AreEqual( generalTestValue_, getStringValue );
	}

	TEST_METHOD( AmfXmlValue_GetDateTest )
	{
		const auto& val = CreateDefaultXml();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDate();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetByteArrayTest )
	{
		const auto& val = CreateDefaultXml();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetByteArray();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetVectorIntTest )
	{
		const auto& val = CreateDefaultXml();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetVectorUintTest )
	{
		const auto& val = CreateDefaultXml();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetVectorDoubleTest )
	{
		const auto& val = CreateDefaultXml();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetObjectTest )
	{
		const auto& val = CreateDefaultXml();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetObject();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetVectorObjectTest )
	{
		const auto& val = CreateDefaultXml();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetArrayTest )
	{
		const auto& val = CreateDefaultXml();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetArray();
		} );
	}

	TEST_METHOD( AmfXmlValue_GetDictionaryTest )
	{
		const auto& val = CreateDefaultXml();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDictionary();
		} );
	}

	TEST_METHOD( AmfXmlValue_ToStringTest )
	{
		const auto& val = CreateDefaultXml();
		Assert::AreEqual( L"\"<test></test>\"", val->ToString() );
	}

private:
	AmfValue^ CreateDefaultXml()
	{
		return AmfValue::CreateXmlValue( generalTestValue_ );
	}

	Platform::String^ generalTestValue_ = L"<test></test>";
};