#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfVectorDoubleValueUnitTest )
{
public:
	TEST_METHOD( AmfVectorDoubleValue_CreateTest )
	{
		const auto& val = GeneralCareteAmfValue();
		Assert::IsTrue( AmfValueType::VectorDouble == val->ValueType );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetBooleanTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetBoolean();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetVectorObjectTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetNumberTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetNumber();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetStringTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetString();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetDateTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetDate();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetByteArrayTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetByteArray();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetVectorIntTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetVectorUintTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetVectorDoubleTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::AreVectorEqual( generalTestVector_, val->GetVectorDouble() );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetObjectTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetObject();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_GetArrayTest )
	{
		const auto& val = GeneralCareteAmfValue();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			val->GetArray();
		} );
	}

	TEST_METHOD( AmfVectorDoubleValue_ToStringTest )
	{
		const auto& val = GeneralCareteAmfValue();
		Assert::AreEqual( L"[5.6, 44, 22.2]", val->ToString() );
	}

private:
	AmfValue^ GeneralCareteAmfValue()
	{
		return AmfValue::CreateVectorDoubleValue( generalTestVector_ );
	}

	Windows::Foundation::Collections::IVector<float64>^ CreateGeneralTestVector( void )
	{
		return ref new Platform::Collections::Vector<float64>{ 5.6, 44.0, 22.2 };
	}

	Windows::Foundation::Collections::IVector<float64>^ generalTestVector_ = CreateGeneralTestVector();
};