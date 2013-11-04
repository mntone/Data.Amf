#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;



TEST_CLASS(AmfBooleanValueUnitTest)
{



	TEST_METHOD(AmfBooleanValueUnitTest_GetBooleanTest){

		auto amfValue = GeneralCareteAmfValue();

		
		auto booleanValue = amfValue->GetBoolean();

		Assert::AreEqual(false, booleanValue);

	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::ExpectException<Platform::InvalidCastException^>([amfValue]{
			auto doubleValue = amfValue->GetDouble();
		});

		
	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetIntegerTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::ExpectException<Platform::InvalidCastException^>([amfValue]{
			auto integerValue = amfValue->GetInteger();
		});

	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetStringTest){

		auto amfValue = GeneralCareteAmfValue();

	
		Assert::ExpectException<Platform::InvalidCastException^>([amfValue]{
			auto stringValue = amfValue->GetString();

		});
	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetDateTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::ExpectException<Platform::InvalidCastException^>([amfValue]{
			auto dateValue = amfValue->GetDate();
		});
	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetByteArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::ExpectException<Platform::InvalidCastException^>([amfValue]{
			auto byteArrayValue = amfValue->GetByteArray();
		});
	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetVectorIntTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::ExpectException<Platform::InvalidCastException^>([amfValue]{

			auto vectorIntValue = amfValue->GetVectorInt();

		});
	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetVectorUintTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::ExpectException<Platform::InvalidCastException^>([amfValue]{

			auto vectorUintValue = amfValue->GetVectorUint();
		});
	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetVectorDoubleTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::ExpectException<Platform::InvalidCastException^>([amfValue]{
			auto vectorDoubleValue = amfValue->GetVectorDouble();
		});
	}

	TEST_METHOD(AmfBooleanValueUnitTest_GetObjectTest){

		auto amfValue = GeneralCareteAmfValue();

		
		Assert::ExpectException<Platform::FailureException^>([amfValue]{
			auto objectValue = amfValue->GetObject();
		});
	}


	TEST_METHOD(AmfBooleanValueUnitTest_GetArrayTest){

		auto amfValue = GeneralCareteAmfValue();

		Assert::ExpectException<Platform::FailureException^>([amfValue]{
			auto arrayValue = amfValue->GetArray();
		});
	}

	TEST_METHOD(AmfBooleanValueUnitTest_ToStringTest){




		auto amfValue = GeneralCareteAmfValue();


		auto toStringValue = amfValue->ToString();

		Assert::AreEqual(L"false", toStringValue);
	}

private:
	static AmfValue^ GeneralCareteAmfValue(){

		return AmfValue::CreateBooleanValue(false);
	}

};