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

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetBoolean();
		});

	}

	TEST_METHOD(AmfDoubleValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(generalTestValue_, amfValue->GetDouble());
	}

	TEST_METHOD(AmfDoubleValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetInteger();
		});


	}

	TEST_METHOD(AmfDoubleValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetString();
		});

	}


	TEST_METHOD(AmfDoubleValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDate();
		});

	}


	TEST_METHOD(AmfDoubleValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetByteArray();
		});

	}


	TEST_METHOD(AmfDoubleValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorInt();
		});

	}


	TEST_METHOD(AmfDoubleValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorUint();
		});

	}

	TEST_METHOD(AmfDoubleValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorDouble();
		});

	}

	TEST_METHOD(AmfDoubleValueUnitTest_GetVectorObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorObject();
		});

	}

	TEST_METHOD(AmfDoubleValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetObject();
		});

	}


	TEST_METHOD(AmfDoubleValueUnitTest_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetArray();
		});

	}

	TEST_METHOD(AmfDoubleValueUnitTest_ToStringTest){

		auto amfValue = GeneralCareteAmfValue();

		auto toStringValue = amfValue->ToString();

		Assert::AreEqual(generalTestValue_.ToString(), toStringValue);
	}

private:
	AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateDoubleValue(generalTestValue_);
	}

	const float64 generalTestValue_ = 4.5;

};

