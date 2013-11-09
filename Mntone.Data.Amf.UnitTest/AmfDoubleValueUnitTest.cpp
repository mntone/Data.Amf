#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;




TEST_CLASS(AmfDoubleValueUnitTest)
{

	TEST_METHOD(AmfDoubleValue_CreateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::IsTrue(AmfValueType::Double ==  amfValue->ValueType);

	}

	TEST_METHOD(AmfDoubleValue_GetBooleanTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetBoolean();
		});

	}

	TEST_METHOD(AmfDoubleValue_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(generalTestValue_, amfValue->GetDouble());
	}

	TEST_METHOD(AmfDoubleValue_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetInteger();
		});


	}

	TEST_METHOD(AmfDoubleValue_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetString();
		});

	}


	TEST_METHOD(AmfDoubleValue_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDate();
		});

	}


	TEST_METHOD(AmfDoubleValue_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetByteArray();
		});

	}


	TEST_METHOD(AmfDoubleValue_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorInt();
		});

	}


	TEST_METHOD(AmfDoubleValue_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorUint();
		});

	}

	TEST_METHOD(AmfDoubleValue_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorDouble();
		});

	}

	TEST_METHOD(AmfDoubleValue_GetVectorObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorObject();
		});

	}

	TEST_METHOD(AmfDoubleValue_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetObject();
		});

	}


	TEST_METHOD(AmfDoubleValue_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetArray();
		});

	}

	TEST_METHOD(AmfDoubleValue_ToStringTest){

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

