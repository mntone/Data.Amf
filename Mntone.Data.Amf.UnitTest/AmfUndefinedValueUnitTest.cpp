#include "pch.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;


TEST_CLASS(AmfUndefinedValueUnitTest)
{

	TEST_METHOD(AmfUndefinedValue_CreateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::IsTrue(AmfValueType::Undefined == amfValue->ValueType);
	}


	TEST_METHOD(AmfUndefinedValue_GetBooleanTest){

		auto amfValue = GeneralCareteAmfValue();


		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetBoolean();
		});
	}

	TEST_METHOD(AmfUndefinedValue_GetVectorObjectTest)
	{
		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorObject();
		});
	}


	
	TEST_METHOD(AmfUndefinedValue_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDouble();
		});

	
	}

	TEST_METHOD(AmfUndefinedValue_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();


		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetInteger();
		});



	}

	TEST_METHOD(AmfUndefinedValue_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetString();
		});


	}


	TEST_METHOD(AmfUndefinedValue_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();


		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDate();
		});


	}


	TEST_METHOD(AmfUndefinedValue_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetByteArray();
		});


	}


	TEST_METHOD(AmfUndefinedValue_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorInt();
		});


	}


	TEST_METHOD(AmfUndefinedValue_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorUint();
		});


	}

	TEST_METHOD(AmfUndefinedValue_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorDouble();
		});


	}

	TEST_METHOD(AmfUndefinedValue_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();
		
		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetObject();
		});


	}


	TEST_METHOD(AmfUndefinedValue_GetArrayTest){

		IAmfValue^ amfValue = GeneralCareteAmfValue();
		
		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetArray();
		});


	}

	TEST_METHOD(AmfUndefinedValue_ToStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(L"undefined", amfValue->ToString());
		
	}

private:
	static AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateUndefinedValue();
	}

};
