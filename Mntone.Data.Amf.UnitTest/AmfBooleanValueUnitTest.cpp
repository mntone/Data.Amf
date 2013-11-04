#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;



TEST_CLASS(AmfBooleanValueUnitTest)
{



	TEST_METHOD(AmfBooleanValueUnitTest_GetBooleanTest){

		auto amfValue = GeneralCareteAmfValue();

		
		auto booleanValue = amfValue->GetBoolean();

		Assert::AreEqual(false, booleanValue);

	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();


		Assert::Fail(L"must write test");


		
	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();
		
		Assert::Fail(L"must write test");


	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");


	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		
		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfBooleanValueUnitTest_ToStringTest){




		auto amfValue = GeneralCareteAmfValue();


		auto toStringValue = amfValue->ToString();

		Assert::AreEqual(L"false", toStringValue);
	}

private:
	static AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateBooleanValue(false);
	}

};