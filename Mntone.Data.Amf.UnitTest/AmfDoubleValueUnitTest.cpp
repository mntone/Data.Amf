#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;




TEST_CLASS(AmfDoubleValueUnitTest)
{

	TEST_METHOD(AmfDoubleValueUnitTest_CreateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::IsTrue(AmfValueType::Double ==  amfValue->ValueType);

	}

	TEST_METHOD(AmfDoubleValueUnitTest_GetBooleanTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfDoubleValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(generalTestValue, amfValue->GetDouble());
	}

	TEST_METHOD(AmfDoubleValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");

	}

	TEST_METHOD(AmfDoubleValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfDoubleValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfDoubleValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfDoubleValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfDoubleValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfDoubleValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfDoubleValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfDoubleValueUnitTest_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfDoubleValueUnitTest_ToStringTest){

		auto amfValue = GeneralCareteAmfValue();

		auto toStringValue = amfValue->ToString();

		Assert::AreEqual(generalTestValue.ToString(), toStringValue);
	}

private:
	static AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateDoubleValue(generalTestValue);
	}

	const static float64 generalTestValue;

};

const float64 AmfDoubleValueUnitTest::generalTestValue = 4.5;