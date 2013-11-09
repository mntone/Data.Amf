

#include "pch.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;


TEST_CLASS(AmfByteArrayValueUnitTest)
{
	


	TEST_METHOD(AmfByteArrayValue_CreateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::IsTrue(AmfValueType::ByteArray == amfValue->ValueType);
	}

	TEST_METHOD(AmfByteArrayValue_GetBooleanTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetBoolean();
		});
	}

	TEST_METHOD(AmfByteArrayValue_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDouble();
		});


	}

	TEST_METHOD(AmfByteArrayValue_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetInteger();
		});
	}

	TEST_METHOD(AmfByteArrayValue_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetString();
		});

	}


	TEST_METHOD(AmfByteArrayValue_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDate();
		});

	}


	TEST_METHOD(AmfByteArrayValue_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::AreArrayEqual(testByteArray_, amfValue->GetByteArray());
	}


	TEST_METHOD(AmfByteArrayValue_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorInt();
		});

	}


	TEST_METHOD(AmfByteArrayValue_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorUint();
		});

	}

	TEST_METHOD(AmfByteArrayValue_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorDouble();
		});

	}

	TEST_METHOD(AmfByteArrayValue_GetVectorObjectTest)
	{
		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorObject();
		});
	}

	TEST_METHOD(AmfByteArrayValue_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetObject();
		});

	}


	TEST_METHOD(AmfByteArrayValue_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetArray();
		});

	}

	TEST_METHOD(AmfByteArrayValue_ToStringTest){


		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(testByteArray_->ToString(), amfValue->ToString());
	}

private:
	AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateByteArrayValue(testByteArray_);
	}

	
	Platform::Array<uint8>^ CreateTestArray(){

		return ref new Platform::Array<uint8>{5,4,32,22};
	}


	Platform::Array<uint8>^ testByteArray_ = CreateTestArray();

};
