

#include "pch.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;


TEST_CLASS(AmfVectorUintValueUnitTest)
{

	TEST_METHOD(AmfVectorUintValueUnitTest_CreateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::IsTrue(AmfValueType::VectorUint == amfValue->ValueType);
	}

	TEST_METHOD(AmfVectorUintValueUnitTest_GetBooleanTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetBoolean();
		});


	}

	TEST_METHOD(AmfVectorUintValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDouble();
		});


	}

	TEST_METHOD(AmfVectorUintValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetInteger();
		});



	}

	TEST_METHOD(AmfVectorUintValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetString();
		});


	}


	TEST_METHOD(AmfVectorUintValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetDate();
		});


	}


	TEST_METHOD(AmfVectorUintValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetByteArray();
		});


	}


	TEST_METHOD(AmfVectorUintValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorInt();
		});


	}


	TEST_METHOD(AmfVectorUintValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::AreVectorEqual(generalTestVector_, amfValue->GetVectorUint());
	}

	TEST_METHOD(AmfVectorUintValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorDouble();
		});
	}

	TEST_METHOD(AmfVectorUintValueUnitTest_GetVectorObjectTest)
	{
		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetVectorObject();
		});


	}

	TEST_METHOD(AmfVectorUintValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetObject();
		});


	}


	TEST_METHOD(AmfVectorUintValueUnitTest_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		AssertHelper::ExpectInvalidOperatonException([=](){
			amfValue->GetArray();
		});


	}

	TEST_METHOD(AmfVectorUintValueUnitTest_ToStringTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::AreEqual(generalTestVector_->ToString(), amfValue->ToString());
	}

private:
	AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateVectorUintValue(generalTestVector_);
	}

	Windows::Foundation::Collections::IVector<uint32>^ CreategeneralTestVector(){

		return ref new Platform::Collections::Vector<uint32>{ 47, 44, 22 };
	}

	Windows::Foundation::Collections::IVector<uint32>^ generalTestVector_ = CreategeneralTestVector();

};