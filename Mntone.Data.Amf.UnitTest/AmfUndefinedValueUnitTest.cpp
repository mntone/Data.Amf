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


		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetBoolean();
		});
	}

	TEST_METHOD(AmfUndefinedValueUnitTest_GetVectorObjectTest)
	{
		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorObject();
		});
	}


	
	TEST_METHOD(AmfUndefinedValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDouble();
		});

	
	}

	TEST_METHOD(AmfUndefinedValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();


		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetInteger();
		});



	}

	TEST_METHOD(AmfUndefinedValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetString();
		});


	}


	TEST_METHOD(AmfUndefinedValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();


		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDate();
		});


	}


	TEST_METHOD(AmfUndefinedValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetByteArray();
		});


	}


	TEST_METHOD(AmfUndefinedValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorInt();
		});


	}


	TEST_METHOD(AmfUndefinedValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorUint();
		});


	}

	TEST_METHOD(AmfUndefinedValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorDouble();
		});


	}

	TEST_METHOD(AmfUndefinedValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();
		
		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetObject();
		});


	}


	TEST_METHOD(AmfUndefinedValueUnitTest_GetArrayTest){

		IAmfValue^ amfValue = GeneralCareteAmfValue();
		
		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetArray();
		});


	}

	TEST_METHOD(AmfUndefinedValueUnitTest_ToStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(L"undefined", amfValue->ToString());
		
	}

private:
	static AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateUndefinedValue();
	}

};
