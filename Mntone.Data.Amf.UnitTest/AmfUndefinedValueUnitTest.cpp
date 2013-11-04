#include "pch.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;


TEST_CLASS(AmfUndefinedValueUnitTest)
{

	TEST_METHOD(AmfUndefinedValueUnitTest_CreateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::IsTrue(AmfValueType::Undefined == amfValue->ValueType);
	}


	TEST_METHOD(AmfUndefinedValueUnitTest_GetBooleanTest){

		auto amfValue = GeneralCareteAmfValue();


		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfUndefinedValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();


		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfUndefinedValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();


		Assert::Fail(L"must write test");

	}

	TEST_METHOD(AmfUndefinedValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfUndefinedValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();


		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfUndefinedValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfUndefinedValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfUndefinedValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfUndefinedValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfUndefinedValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfUndefinedValueUnitTest_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfUndefinedValueUnitTest_ToStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

private:
	static AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateUndefinedValue();
	}

};
