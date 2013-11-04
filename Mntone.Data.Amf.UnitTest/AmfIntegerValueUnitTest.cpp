#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;





TEST_CLASS(AmfIntegerValueUnitTest)
{

	TEST_METHOD(AmfIntegerValueUnitTest_CreateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::IsTrue(AmfValueType::Integer == amfValue->ValueType);
	}

	TEST_METHOD(AmfIntegerValueUnitTest_GetBooleanTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfIntegerValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfIntegerValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(generalTestValue, amfValue->GetInteger());

	}

	TEST_METHOD(AmfIntegerValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfIntegerValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfIntegerValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfIntegerValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfIntegerValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfIntegerValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfIntegerValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfIntegerValueUnitTest_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfIntegerValueUnitTest_ToStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(generalTestValue.ToString(), amfValue->ToString());
	}

private:
	static AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateIntegerValue(generalTestValue);
	}

	const static int generalTestValue = 8250;
};

