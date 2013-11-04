#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;



TEST_CLASS(AmfStringValueUnitTest)
{

	TEST_METHOD(AmfStringValueUnitTest_CreateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::IsTrue(AmfValueType::String == amfValue->ValueType);
	}

	TEST_METHOD(AmfStringValueUnitTest_GetBooleanTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfStringValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfStringValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");

	}

	TEST_METHOD(AmfStringValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(ref new Platform::String(generalTestValue), amfValue->GetString());
	}


	TEST_METHOD(AmfStringValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfStringValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfStringValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfStringValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfStringValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfStringValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfStringValueUnitTest_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfStringValueUnitTest_ToStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(ref new Platform::String(generalTestValue), amfValue->ToString());
	}

private:
	AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateStringValue(ref new Platform::String(generalTestValue));
	}


	const wchar_t* generalTestValue = L"testValue";
};
