

#include "pch.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;


TEST_CLASS(AmfByteArrayValueUnitTest)
{
	


	TEST_METHOD(AmfByteArrayValueUnitTest_CreateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::IsTrue(AmfValueType::ByteArray == amfValue->ValueType);
	}

	TEST_METHOD(AmfByteArrayValueUnitTest_GetBooleanTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfByteArrayValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfByteArrayValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");

	}

	TEST_METHOD(AmfByteArrayValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfByteArrayValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfByteArrayValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::AreArrayEqual(testByteArray, amfValue->GetByteArray());
	}


	TEST_METHOD(AmfByteArrayValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfByteArrayValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfByteArrayValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfByteArrayValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfByteArrayValueUnitTest_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfByteArrayValueUnitTest_ToStringTest){


		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(testByteArray->ToString(), amfValue->ToString());
	}

private:
	AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateByteArrayValue(testByteArray);
	}

	
	Platform::Array<uint8>^ CreateTestArray(){

		return ref new Platform::Array<uint8>{5,4,32,22};
	}


	Platform::Array<uint8>^ testByteArray = CreateTestArray();

};
