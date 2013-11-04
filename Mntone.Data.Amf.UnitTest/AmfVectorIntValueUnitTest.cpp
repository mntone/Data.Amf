#include "pch.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;


TEST_CLASS(AmfVectorIntValueUnitTest)
{

	TEST_METHOD(AmfVectorIntValueUnitTest_CreateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::IsTrue(AmfValueType::VectorInt == amfValue->ValueType);
	}

	TEST_METHOD(AmfVectorIntValueUnitTest_GetBooleanTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfVectorIntValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfVectorIntValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");

	}

	TEST_METHOD(AmfVectorIntValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfVectorIntValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfVectorIntValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfVectorIntValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfVectorIntValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::AreVectorEqual(generalTestVector, amfValue->GetVectorInt());
	}

	TEST_METHOD(AmfVectorIntValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfVectorIntValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfVectorIntValueUnitTest_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfVectorIntValueUnitTest_ToStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(generalTestVector->ToString(), amfValue->ToString());
	}

private:
	AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateVectorIntValue(generalTestVector);
	}

	Windows::Foundation::Collections::IVector<int32>^ CreateTestVector(){

		return ref new Platform::Collections::Vector<int32>{ 3, 2 ,5,63,2};
	}

	Windows::Foundation::Collections::IVector<int32>^ generalTestVector = CreateTestVector();
};