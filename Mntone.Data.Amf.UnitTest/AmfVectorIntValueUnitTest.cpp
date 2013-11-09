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

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetBoolean();
		});


	}

	TEST_METHOD(AmfVectorIntValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDouble();
		});


	}

	TEST_METHOD(AmfVectorIntValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetInteger();
		});



	}

	TEST_METHOD(AmfVectorIntValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetString();
		});


	}


	TEST_METHOD(AmfVectorIntValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDate();
		});


	}


	TEST_METHOD(AmfVectorIntValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetByteArray();
		});


	}


	TEST_METHOD(AmfVectorIntValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		auto vectorIntValue = amfValue->GetVectorInt();

		AssertHelper::AreVectorEqual(generalTestVector_, vectorIntValue);

	}


	TEST_METHOD(AmfVectorIntValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::AreVectorEqual(generalTestVector_, amfValue->GetVectorInt());
	}

	TEST_METHOD(AmfVectorIntValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorDouble();
		});


	}

	TEST_METHOD(AmfVectorIntValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetObject();
		});


	}


	TEST_METHOD(AmfVectorIntValueUnitTest_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetArray();
		});


	}

	TEST_METHOD(AmfVectorIntValueUnitTest_ToStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(generalTestVector_->ToString(), amfValue->ToString());
	}

private:
	AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateVectorIntValue(generalTestVector_);
	}

	Windows::Foundation::Collections::IVector<int32>^ CreateTestVector(){

		return ref new Platform::Collections::Vector<int32>{ 3, 2 ,5,63,2};
	}

	Windows::Foundation::Collections::IVector<int32>^ generalTestVector_ = CreateTestVector();
};