

#include "pch.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;


TEST_CLASS(AmfVectorObjectValueUnitTest)
{

	TEST_METHOD(AmfVectorObjectValue_CreateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::IsTrue(AmfValueType::VectorObject == amfValue->ValueType);
	}

	TEST_METHOD(AmfVectorObjectValue_GetBooleanTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetBoolean();
		});

	}

	TEST_METHOD(AmfVectorObjectValue_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDouble();
		});

	}

	TEST_METHOD(AmfVectorObjectValue_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetInteger();
		});


	}

	TEST_METHOD(AmfVectorObjectValue_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetString();
		});

	}


	TEST_METHOD(AmfVectorObjectValue_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDate();
		});

	}


	TEST_METHOD(AmfVectorObjectValue_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetByteArray();
		});

	}


	TEST_METHOD(AmfVectorObjectValue_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorInt();
		});

	}


	TEST_METHOD(AmfVectorObjectValue_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorUint();
		});

	}

	TEST_METHOD(AmfVectorObjectValue_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorDouble();
		});

	}

	TEST_METHOD(AmfVectorObjectValue_GetVectorObjectTest){

		auto amfValue = GeneralCareteAmfValue();


		Assert::AreEqual(generalTestVector_, amfValue->GetVectorObject());


	}

	TEST_METHOD(AmfVectorObjectValue_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetObject();
		});

	}


	TEST_METHOD(AmfVectorObjectValue_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetArray();
		});

	}

	TEST_METHOD(AmfVectorObjectValue_ToStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(generalTestVector_->ToString(), amfValue->ToString());

	}

private:
	AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateVectorObjectValue(generalTestVector_);
	}

	Windows::Foundation::Collections::IVector<IAmfValue^>^ CreateTestVector(){

		return ref new Platform::Collections::Vector<IAmfValue^>{ref new AmfObject(L"testClass1"),ref new AmfObject(L"testClass2")};
	}

	Windows::Foundation::Collections::IVector<IAmfValue^>^ generalTestVector_ = CreateTestVector();

};