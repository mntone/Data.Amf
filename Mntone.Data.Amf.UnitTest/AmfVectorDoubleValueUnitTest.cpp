

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

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetBoolean();
		});


	}

	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetVectorObjectTest)
	{
		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorObject();
		});
	}

	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDouble();
		});


	}

	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetInteger();
		});



	}

	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetString();
		});


	}


	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDate();
		});


	}


	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetByteArray();
		});


	}


	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorInt();
		});


	}


	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		
		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorUint();
		});
	}

	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::AreVectorEqual(generalTestVector_, amfValue->GetVectorDouble());

		


	}

	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetObject();
		});


	}


	TEST_METHOD(AmfVectorDoubleValueUnitTest_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetArray();
		});


	}

	TEST_METHOD(AmfVectorDoubleValueUnitTest_ToStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(generalTestVector_->ToString(), amfValue->ToString());
	}

private:
	AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateVectorDoubleValue(generalTestVector_);
	}

	Windows::Foundation::Collections::IVector<float64>^ CreateGeneralTestVector(){

		return ref new Platform::Collections::Vector<float64>{ 5.6, 44.0, 22.2 };
	}

	Windows::Foundation::Collections::IVector<float64>^ generalTestVector_ = CreateGeneralTestVector();

};