#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;



TEST_CLASS(AmfBooleanValueUnitTest)
{


	TEST_METHOD(AmfBooleanValueUnitTest_CreateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::IsTrue(AmfValueType::Boolean == amfValue->ValueType);
	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetBooleanTest){

		auto amfValue = GeneralCareteAmfValue();

		auto booleanValue = amfValue->GetBoolean();

		Assert::AreEqual(generalTestValue_, booleanValue);

	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();


		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDouble();
		});

	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetInteger();
		});
	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetString();
		});
	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDate();
		});


	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetByteArray();
		});
	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorInt();
		});


	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorUint();
		});


	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorDouble();
		});


	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetVectorObjectTest)
	{
		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorObject();
		});
	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();


		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetObject();
		});
	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetArray();
		});
	}

	TEST_METHOD(AmfBooleanValueUnitTest_ToStringTest){

		auto amfValue = GeneralCareteAmfValue();

		auto toStringValue = amfValue->ToString();

		Assert::AreEqual(generalTestValue_.ToString(), toStringValue);
	}

private:
	AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateBooleanValue(generalTestValue_);
	}


	const bool generalTestValue_ = false;

};

