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

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetBoolean();
		});

	}

	TEST_METHOD(AmfIntegerValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDouble();
		});


	}

	TEST_METHOD(AmfIntegerValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(generalTestValue, amfValue->GetInteger());

	}

	TEST_METHOD(AmfIntegerValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetString();
		});


	}


	TEST_METHOD(AmfIntegerValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDate();
		});


	}


	TEST_METHOD(AmfIntegerValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetByteArray();
		});


	}


	TEST_METHOD(AmfIntegerValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorInt();
		});


	}


	TEST_METHOD(AmfIntegerValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorUint();
		});


	}

	TEST_METHOD(AmfIntegerValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorDouble();
		});


	}

	TEST_METHOD(AmfIntegerValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetObject();
		});


	}


	TEST_METHOD(AmfIntegerValueUnitTest_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetArray();
		});


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

