#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfObjectUnitTest )
{
public:
	TEST_METHOD( AmfObject_CreateTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		Assert::IsTrue( AmfValueType::Object == obj->ValueType );
	}

	TEST_METHOD( AmfObject_GetBooleanTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			obj->GetBoolean();
		} );
	}

	TEST_METHOD( AmfObject_GetNumberTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			obj->GetNumber();
		} );
	}

	TEST_METHOD( AmfObject_GetStringTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			obj->GetString();
		} );
	}

	TEST_METHOD( AmfObject_GetDateTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			obj->GetDate();
		} );
	}

	TEST_METHOD( AmfObject_GetByteArrayTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			obj->GetByteArray();
		} );
	}

	TEST_METHOD( AmfObject_GetVectorIntTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			obj->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfObject_GetVectorUintTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			obj->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfObject_GetVectorDoubleTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			obj->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfObject_GetVectorObjectTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			obj->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfObject_GetObjectTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		Assert::AreEqual( obj, obj->GetObject() );
	}

	TEST_METHOD( AmfObject_GetArrayTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		AssertHelper::ExpectInvalidOperatonException( [=]()
		{
			obj->GetArray();
		} );
	}

	TEST_METHOD( AmfObject_ToStringTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		Assert::AreEqual( L"{}", obj->ToString() );
	}

	TEST_METHOD( AmfObject_GetNamedValueTest )
	{
		auto obj = GeneralCreateAmfObject();
		const auto& val = AmfValue::CreateBooleanValue( false );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, val );
		Assert::AreEqual( val, obj->GetNamedValue( key ) );
	}

	TEST_METHOD( AmfObject_GetNamedValueTest_OutOfRange )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedValue( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedStringTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		Assert::AreEqual( val, obj->GetNamedString( key ) );
	}

	TEST_METHOD( AmfObject_GetNamedStringTest_OutOfRange )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedString( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedStringTest_InvalidType )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = false;
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateBooleanValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedString( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedNumberTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = 2.5;
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateNumberValue( val ) );

		Assert::AreEqual( val, obj->GetNamedNumber( key ) );
	}

	TEST_METHOD( AmfObject_GetNamedNumberTest_OutOfRange )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedNumber( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedNumberTest_InvalidType )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedNumber( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedDateTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = AssertHelper::GetDate( 2000, 10, 4 );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateDateValue( val ) );
		Assert::IsTrue( val.UniversalTime == obj->GetNamedDate( key ).UniversalTime );
	}

	TEST_METHOD( AmfObject_GetNamedDateTest_OutOfRange )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedDate( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedDateTest_InvalidType )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedDate( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedBooleanTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = false;
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateBooleanValue( val ) );
		Assert::AreEqual( val, obj->GetNamedBoolean( key ) );
	}

	TEST_METHOD( AmfObject_GetNamedBooleanTest_OutOfRange )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedBoolean( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedBooleanTest_InvalidType )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedBoolean( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedByteArrayTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		U8Array^ val = { 3, 56 };
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateByteArrayValue( val ) );
		AssertHelper::AreArrayEqual( val, obj->GetNamedByteArray( key ) );
	}

	TEST_METHOD( AmfObject_GetNamedByteArrayTest_OutOfRange )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedByteArray( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedByteArrayTest_InvalidType )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedByteArray( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedVectorIntTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::Collections::Vector<int32>{ 3, -2, 5, 63, 2 };
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateVectorIntValue( val ) );
		AssertHelper::AreVectorEqual( val, obj->GetNamedVectorInt( key ) );
	}

	TEST_METHOD( AmfObject_GetNamedVectorIntTest_OutOfRange )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedVectorInt( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedVectorIntTest_InvalidType )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedVectorInt( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedVectorUintTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::Collections::Vector<uint32>{ 3, 55, 32 };
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateVectorUintValue( val ) );
		AssertHelper::AreVectorEqual( val, obj->GetNamedVectorUint( key ) );
	}

	TEST_METHOD( AmfObject_GetNamedVectorUintTest_OutOfRange )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedVectorUint( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedVectorUintTest_InvalidType )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedVectorUint( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedVectorDoubleTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::Collections::Vector<double>{ 2.5, 3, 2, 44 };
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateVectorDoubleValue( val ) );
		AssertHelper::AreVectorEqual( val, obj->GetNamedVectorDouble( key ) );
	}

	TEST_METHOD( AmfObject_GetNamedVectorDoubleTest_OutOfRange )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedVectorDouble( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedVectorDoubleTest_InvalidType )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedVectorDouble( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedVectorObjectTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		Windows::Foundation::Collections::IVector<IAmfValue^>^ val = ref new Platform::Collections::Vector<IAmfValue^>{ AmfValue::CreateNumberValue( 5.3 ), AmfValue::CreateStringValue( L"testVal" ) };
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateVectorObjectValue( val ) );
		Assert::AreEqual( val, obj->GetNamedVectorObject( key ) );
	}

	TEST_METHOD( AmfObject_GetNamedVectorObjectTest_OutOfRange )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedVectorObject( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedVectorObjectTest_InvalidType )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedVectorObject( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedObjectTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, val );
		Assert::AreEqual( val, obj->GetNamedObject( key ) );
	}

	TEST_METHOD( AmfObject_GetNamedObjectTest_OutOfRange )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedObject( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedObjectTest_InvalidType )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedObject( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedArrayTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new AmfArray();
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, val );
		Assert::AreEqual( val, obj->GetNamedArray( key ) );
	}

	TEST_METHOD( AmfObject_GetNamedArrayTest_OutOfRange )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedArray( key );
		} );
	}

	TEST_METHOD( AmfObject_GetNamedArrayTest_InvalidType )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedArray( key );
		} );
	}

	TEST_METHOD( AmfObject_LookupTest )
	{
		const auto& obj = GeneralCreateAmfObject();
		IAmfValue^ val = AmfValue::CreateNumberValue( 5.5 );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, val );
		Assert::AreEqual( val, obj->Lookup( key ) );
	}

	TEST_METHOD( AmfObject_LookupTest_OutOfRange )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->Lookup( key );
		} );
	}

	TEST_METHOD( AmfObject_HaskeyTest_True )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		Assert::IsTrue( obj->HasKey( key ) );
	}

	TEST_METHOD( AmfObject_HaskeyTest_False )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		Assert::IsFalse( obj->HasKey( L"Invalid Key" ) );
	}

	TEST_METHOD( AmfObject_GetView )
	{
		const auto& obj = GeneralCreateAmfObject();
		Assert::IsNotNull( obj->GetView() );
	}

	TEST_METHOD( AmfObject_First )
	{
		const auto& obj = GeneralCreateAmfObject();
		auto result = obj->First();
		Assert::IsNotNull( result );
		Assert::AreEqual( false, result->HasCurrent );
	}

	TEST_METHOD( AmfObject_Insert )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = AmfValue::CreateStringValue( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->Insert( key, val );
		Assert::AreEqual( val, obj->GetNamedValue( key ) );

	}

	TEST_METHOD( AmfObject_Remove )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = AmfValue::CreateStringValue( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->Insert( key, val );
		obj->Remove( key );
		Assert::IsFalse( obj->HasKey( key ) );
	}

	TEST_METHOD( AmfObject_Clear )
	{
		const auto& obj = GeneralCreateAmfObject();
		const auto& val = AmfValue::CreateStringValue( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		for( size_t i = 0; i < 25; i++ )
		{
			obj->Insert( key + i, val );
		}
		obj->Clear();
		Assert::IsFalse( obj->HasKey( key ) );
	}

private:
	AmfObject^ GeneralCreateAmfObject()
	{
		return ref new AmfObject();
	}
};