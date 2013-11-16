#include "pch.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;


TEST_CLASS(AmfObjectUnitTest)
{

	TEST_METHOD(AmfObject_CreateTest){

		auto obj = GeneralCreateAmfObject();

		Assert::IsTrue(AmfValueType::Object == obj->ValueType);
	}

	TEST_METHOD(AmfObject_GetBooleanTest){

		auto obj = GeneralCreateAmfObject();

		AssertHelper::ExpectInvalidOperatonException([=]()
		{
			obj->GetBoolean();
		});
	}

	TEST_METHOD(AmfObject_GetNumberTest){

		auto obj = GeneralCreateAmfObject();

		AssertHelper::ExpectInvalidOperatonException([=]()
		{
			obj->GetNumber();
		});
	}



	TEST_METHOD(AmfObject_GetStringTest){

		auto obj = GeneralCreateAmfObject();

		AssertHelper::ExpectInvalidOperatonException([=]()
		{
			obj->GetString();
		});
	}


	TEST_METHOD(AmfObject_GetDateTest){

		auto obj = GeneralCreateAmfObject();

		AssertHelper::ExpectInvalidOperatonException([=]()
		{
			obj->GetDate();
		});
	}


	TEST_METHOD(AmfObject_GetByteArrayTest){

		auto obj = GeneralCreateAmfObject();

		AssertHelper::ExpectInvalidOperatonException([=]()
		{
			obj->GetByteArray();
		});
	}


	TEST_METHOD(AmfObject_GetVectorIntTest){

		auto obj = GeneralCreateAmfObject();

		AssertHelper::ExpectInvalidOperatonException([=]()
		{
			obj->GetVectorInt();
		});
	}


	TEST_METHOD(AmfObject_GetVectorUintTest){

		auto obj = GeneralCreateAmfObject();

		AssertHelper::ExpectInvalidOperatonException([=]()
		{
			obj->GetVectorUint();
		});
	}

	TEST_METHOD(AmfObject_GetVectorDoubleTest){

		auto obj = GeneralCreateAmfObject();

		AssertHelper::ExpectInvalidOperatonException([=]()
		{
			obj->GetVectorDouble();
		});
	}

	TEST_METHOD(AmfObject_GetVectorObjectTest){

		auto obj = GeneralCreateAmfObject();

		AssertHelper::ExpectInvalidOperatonException([=]()
		{
			obj->GetVectorObject();
		});
	}

	TEST_METHOD(AmfObject_GetObjectTest){

		auto obj = GeneralCreateAmfObject();

		Assert::AreEqual(obj, obj->GetObject());


	}


	TEST_METHOD(AmfObject_GetArrayTest){

		auto obj = GeneralCreateAmfObject();

		AssertHelper::ExpectInvalidOperatonException([=]()
		{
			obj->GetArray();
		});
	}

	TEST_METHOD(AmfObject_ToStringTest){

		auto obj = GeneralCreateAmfObject();
		Assert::AreEqual(L"{}", obj->ToString());
	}

	TEST_METHOD(AmfObject_GetNamedValueTest)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = AmfValue::CreateBooleanValue(false);
		auto key = ref new Platform::String( L"testKey");
		obj->SetNamedValue(key, val);

		Assert::AreEqual(val, obj->GetNamedValue(key));
	}

	TEST_METHOD(AmfObject_GetNamedValueTest_OutOfRange)
	{
		auto obj = GeneralCreateAmfObject();
		auto key = ref new Platform::String(L"testKey");

		Assert::ExpectException<Platform::OutOfBoundsException^>([=]{
			obj->GetNamedValue(key);
		});
		
	}


	TEST_METHOD(AmfObject_GetNamedStringTest)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::String(L"testValue");
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateStringValue(val) );

		Assert::AreEqual(val, obj->GetNamedString(key));
	}

	TEST_METHOD(AmfObject_GetNamedStringTest_OutOfRange)
	{
		auto obj = GeneralCreateAmfObject();
		auto key = ref new Platform::String(L"testKey");

		Assert::ExpectException<Platform::OutOfBoundsException^>([=]{
			obj->GetNamedString(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedStringTest_InvalidType)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = false;
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateBooleanValue(val));

		AssertHelper::ExpectInvalidOperatonException([=]{
			obj->GetNamedString(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedNumberTest)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = 2.5;
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateNumberValue(val));

		Assert::AreEqual(val, obj->GetNamedNumber(key));
	}

	TEST_METHOD(AmfObject_GetNamedNumberTest_OutOfRange)
	{
		auto obj = GeneralCreateAmfObject();
		auto key = ref new Platform::String(L"testKey");

		Assert::ExpectException<Platform::OutOfBoundsException^>([=]{
			obj->GetNamedNumber(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedNumberTest_InvalidType)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::String(L"testValue");
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateStringValue(val));

		AssertHelper::ExpectInvalidOperatonException([=]{
			obj->GetNamedNumber(key);
		});
	}


	TEST_METHOD(AmfObject_GetNamedDateTest)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = AssertHelper::GetDate(2000,10,4);
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateDateValue(val));

		Assert::IsTrue(val.UniversalTime == obj->GetNamedDate(key).UniversalTime);
	}

	TEST_METHOD(AmfObject_GetNamedDateTest_OutOfRange)
	{
		auto obj = GeneralCreateAmfObject();
		auto key = ref new Platform::String(L"testKey");

		Assert::ExpectException<Platform::OutOfBoundsException^>([=]{
			obj->GetNamedDate(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedDateTest_InvalidType)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::String(L"testValue");
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateStringValue(val));

		AssertHelper::ExpectInvalidOperatonException([=]{
			obj->GetNamedDate(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedBooleanTest)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = false;
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateBooleanValue(val));

		Assert::AreEqual(val, obj->GetNamedBoolean(key));
	}

	TEST_METHOD(AmfObject_GetNamedBooleanTest_OutOfRange)
	{
		auto obj = GeneralCreateAmfObject();
		auto key = ref new Platform::String(L"testKey");

		Assert::ExpectException<Platform::OutOfBoundsException^>([=]{
			obj->GetNamedBoolean(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedBooleanTest_InvalidType)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::String(L"testValue");
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateStringValue(val));

		AssertHelper::ExpectInvalidOperatonException([=]{
			obj->GetNamedBoolean(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedByteArrayTest)
	{
		auto obj = GeneralCreateAmfObject();
		Platform::Array<uint8>^ val = { 3, 56 };
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateByteArrayValue(val));

		AssertHelper::AreArrayEqual(val, obj->GetNamedByteArray(key));
	}

	TEST_METHOD(AmfObject_GetNamedByteArrayTest_OutOfRange)
	{
		auto obj = GeneralCreateAmfObject();
		auto key = ref new Platform::String(L"testKey");

		Assert::ExpectException<Platform::OutOfBoundsException^>([=]{
			obj->GetNamedByteArray(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedByteArrayTest_InvalidType)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::String(L"testValue");
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateStringValue(val));

		AssertHelper::ExpectInvalidOperatonException([=]{
			obj->GetNamedByteArray(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedVectorIntTest)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::Collections::Vector<int32>{ 3, -2, 5, 63, 2 };
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateVectorIntValue(val));

		AssertHelper::AreVectorEqual(val, obj->GetNamedVectorInt(key));
	}


	TEST_METHOD(AmfObject_GetNamedVectorIntTest_OutOfRange)
	{
		auto obj = GeneralCreateAmfObject();
		auto key = ref new Platform::String(L"testKey");

		Assert::ExpectException<Platform::OutOfBoundsException^>([=]{
			obj->GetNamedVectorInt(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedVectorIntTest_InvalidType)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::String(L"testValue");
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateStringValue(val));

		AssertHelper::ExpectInvalidOperatonException([=]{
			obj->GetNamedVectorInt(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedVectorUintTest)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::Collections::Vector<uint32>{ 3, 55, 32 };
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateVectorUintValue(val));

		AssertHelper::AreVectorEqual(val, obj->GetNamedVectorUint(key));
	}

	TEST_METHOD(AmfObject_GetNamedVectorUintTest_OutOfRange)
	{
		auto obj = GeneralCreateAmfObject();
		auto key = ref new Platform::String(L"testKey");

		Assert::ExpectException<Platform::OutOfBoundsException^>([=]{
			obj->GetNamedVectorUint(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedVectorUintTest_InvalidType)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::String(L"testValue");
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateStringValue(val));

		AssertHelper::ExpectInvalidOperatonException([=]{
			obj->GetNamedVectorUint(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedVectorDoubleTest)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::Collections::Vector<double>{ 2.5, 3, 2, 44 };
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateVectorDoubleValue(val));

		AssertHelper::AreVectorEqual(val, obj->GetNamedVectorDouble(key));
	}

	TEST_METHOD(AmfObject_GetNamedVectorDoubleTest_OutOfRange)
	{
		auto obj = GeneralCreateAmfObject();
		auto key = ref new Platform::String(L"testKey");

		Assert::ExpectException<Platform::OutOfBoundsException^>([=]{
			obj->GetNamedVectorDouble(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedVectorDoubleTest_InvalidType)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::String(L"testValue");
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateStringValue(val));

		AssertHelper::ExpectInvalidOperatonException([=]{
			obj->GetNamedVectorDouble(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedVectorObjectTest)
	{
		auto obj = GeneralCreateAmfObject();
		Windows::Foundation::Collections::IVector<IAmfValue^>^ val = ref new Platform::Collections::Vector<IAmfValue^>{AmfValue::CreateNumberValue(5.3),AmfValue::CreateStringValue(L"testVal")};
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateVectorObjectValue(val));

		Assert::AreEqual(val, obj->GetNamedVectorObject(key));
	}

	TEST_METHOD(AmfObject_GetNamedVectorObjectTest_OutOfRange)
	{
		auto obj = GeneralCreateAmfObject();
		auto key = ref new Platform::String(L"testKey");

		Assert::ExpectException<Platform::OutOfBoundsException^>([=]{
			obj->GetNamedVectorObject(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedVectorObjectTest_InvalidType)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::String(L"testValue");
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateStringValue(val));

		AssertHelper::ExpectInvalidOperatonException([=]{
			obj->GetNamedVectorObject(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedObjectTest)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new AmfObject();
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, val);

		Assert::AreEqual(val, obj->GetNamedObject(key));
	}

	TEST_METHOD(AmfObject_GetNamedObjectTest_OutOfRange)
	{
		auto obj = GeneralCreateAmfObject();
		auto key = ref new Platform::String(L"testKey");

		Assert::ExpectException<Platform::OutOfBoundsException^>([=]{
			obj->GetNamedObject(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedObjectTest_InvalidType)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::String(L"testValue");
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateStringValue(val));

		AssertHelper::ExpectInvalidOperatonException([=]{
			obj->GetNamedObject(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedArrayTest)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new AmfArray();
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, val);

		Assert::AreEqual(val, obj->GetNamedArray(key));
	}

	TEST_METHOD(AmfObject_GetNamedArrayTest_OutOfRange)
	{
		auto obj = GeneralCreateAmfObject();
		auto key = ref new Platform::String(L"testKey");

		Assert::ExpectException<Platform::OutOfBoundsException^>([=]{
			obj->GetNamedArray(key);
		});
	}

	TEST_METHOD(AmfObject_GetNamedArrayTest_InvalidType)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::String(L"testValue");
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateStringValue(val));

		AssertHelper::ExpectInvalidOperatonException([=]{
			obj->GetNamedArray(key);
		});
	}

	TEST_METHOD(AmfObject_LookupTest)
	{
		auto obj = GeneralCreateAmfObject();
		IAmfValue^ val = AmfValue::CreateNumberValue(5.5);
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, val);

		Assert::AreEqual(val, obj->Lookup(key));
	}

	TEST_METHOD(AmfObject_LookupTest_OutOfRange)
	{
		auto obj = GeneralCreateAmfObject();
		auto key = ref new Platform::String(L"testKey");

		Assert::ExpectException<Platform::OutOfBoundsException^>([=]{
			obj->Lookup(key);
		});
	}


	TEST_METHOD(AmfObject_HaskeyTest_True)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::String(L"testValue");
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateStringValue(val));

		Assert::IsTrue( obj->HasKey(key));
	}

	TEST_METHOD(AmfObject_HaskeyTest_False)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = ref new Platform::String(L"testValue");
		auto key = ref new Platform::String(L"testKey");
		obj->SetNamedValue(key, AmfValue::CreateStringValue(val));

		Assert::IsFalse( obj->HasKey(L"Invalid Key"));
	}

	TEST_METHOD(AmfObject_GetView)
	{
		auto obj = GeneralCreateAmfObject();

		Assert::IsNotNull(obj->GetView());
	}


	TEST_METHOD(AmfObject_First)
	{
		auto obj = GeneralCreateAmfObject();
		auto result = obj->First();
		Assert::IsNotNull(result);
		Assert::AreEqual(false, result->HasCurrent);
	}

	TEST_METHOD(AmfObject_Insert)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = AmfValue::CreateStringValue(L"testValue");
		auto key = ref new Platform::String(L"testKey");
		
		obj->Insert(key, val);
		
		Assert::AreEqual(val, obj->GetNamedValue(key));

	}

	TEST_METHOD(AmfObject_Remove)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = AmfValue::CreateStringValue(L"testValue");
		auto key = ref new Platform::String(L"testKey");

		obj->Insert(key, val);

		obj->Remove(key);

		Assert::IsFalse(obj->HasKey(key));
	}


	TEST_METHOD(AmfObject_Clear)
	{
		auto obj = GeneralCreateAmfObject();
		auto val = AmfValue::CreateStringValue(L"testValue");
		auto key = ref new Platform::String(L"testKey");

		for (size_t i = 0; i < 25; i++)
		{
			obj->Insert(key + i, val);
		}

		obj->Clear();

		Assert::IsFalse(obj->HasKey(key));
	}

private:
	AmfObject^ GeneralCreateAmfObject(){

		return ref new AmfObject();
	}

};