

#include "pch.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;


TEST_CLASS(AmfVectorDoubleValueUnitTest)
{

	TEST_METHOD(AmfVectorDoubleValueUnitTest_CreateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::IsTrue(AmfValueType::VectorDouble == amfValue->ValueType);
	}

	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetBooleanTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");

	}

	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::AreVectorEqual(generalTestVector, amfValue->GetVectorDouble());
	}

	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}


	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::Fail(L"must write test");
	}

	TEST_METHOD(AmfVectorDoubleValueUnitTest_ToStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(generalTestVector->ToString(), amfValue->ToString());
	}

private:
	AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateVectorDoubleValue(generalTestVector);
	}

	Windows::Foundation::Collections::IVector<float64>^ CreateGeneralTestVector(){

		return ref new Platform::Collections::Vector<float64>{ 5.6, 44.0, 22.2 };
	}

	Windows::Foundation::Collections::IVector<float64>^ generalTestVector = CreateGeneralTestVector();

};