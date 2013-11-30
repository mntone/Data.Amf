#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfObjectUnitTest )
{
public:
#pragma region IAmfObjectFactory methods

	TEST_METHOD( AmfObject_IAmfObjectFactory_CreateTest )
	{
		const auto& obj = ref new AmfObject();
		Assert::IsTrue( obj->ValueType == AmfValueType::Object );
		Assert::AreEqual( 0u, obj->Size );
	}

#pragma endregion

#pragma region IAmfObjectStatics methods

	TEST_METHOD( AmfObject_IAmfObjectStatics_CreateEcmaArrayTest )
	{
		const auto& obj = AmfObject::CreateEcmaArray();
		Assert::IsTrue( obj->ValueType == AmfValueType::EcmaArray );
		Assert::AreEqual( 0u, obj->Size );
	}

	TEST_METHOD( AmfObject_IAmfObjectStatics_ParseTest_Default )
	{
		const auto& obj = AmfObject::Parse( ref new U8Array{ 6 } );
		Assert::IsTrue( obj->ValueType == AmfValueType::Undefined );
	}

	TEST_METHOD( AmfObject_IAmfObjectStatics_ParseTest_Amf0 )
	{
		const auto& obj = AmfObject::Parse( ref new U8Array{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, AmfEncodingType::Amf0 );
		Assert::IsTrue( obj->ValueType == AmfValueType::Number );
		Assert::AreEqual( 0.0, obj->GetNumber() );
	}

	TEST_METHOD( AmfObject_IAmfObjectStatics_ParseTest_Amf3 )
	{
		const auto& obj = AmfObject::Parse( ref new U8Array{ 0 }, AmfEncodingType::Amf3 );
		Assert::IsTrue( obj->ValueType == AmfValueType::Undefined );
	}

	TEST_METHOD( AmfObject_IAmfObjectStatics_TryParseTest_Default )
	{
		AmfObject^ obj;
		Assert::IsTrue( AmfObject::TryParse( ref new U8Array{ 6 }, &obj ) );
		Assert::IsTrue( obj->ValueType == AmfValueType::Undefined );
	}

	TEST_METHOD( AmfObject_IAmfObjectStatics_TryParseTest_Amf0 )
	{
		AmfObject^ obj;
		Assert::IsTrue( AmfObject::TryParse( ref new U8Array{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, AmfEncodingType::Amf0, &obj ) );
		Assert::IsTrue( obj->ValueType == AmfValueType::Number );
		Assert::AreEqual( 0.0, obj->GetNumber() );
	}

	TEST_METHOD( AmfObject_IAmfObjectStatics_TryParseTest_Amf3 )
	{
		AmfObject^ obj;
		Assert::IsTrue( AmfObject::TryParse( ref new U8Array{ 0 }, AmfEncodingType::Amf3, &obj ) );
		Assert::IsTrue( obj->ValueType == AmfValueType::Undefined );
	}

#pragma endregion

#pragma region IAmfValue methods

	TEST_METHOD( AmfObject_IAmfValue_GetBooleanTest )
	{
		InvalidOperationTest( []( AmfObject^ obj )
		{
			obj->GetBoolean();
		} );
	}

	TEST_METHOD( AmfObject_IAmfValue_GetNumberTest )
	{
		InvalidOperationTest( []( AmfObject^ obj )
		{
			obj->GetNumber();
		} );
	}

	TEST_METHOD( AmfObject_IAmfValue_GetStringTest )
	{
		InvalidOperationTest( []( AmfObject^ obj )
		{
			obj->GetString();
		} );
	}

	TEST_METHOD( AmfObject_IAmfValue_GetDateTest )
	{
		InvalidOperationTest( []( AmfObject^ obj )
		{
			obj->GetDate();
		} );
	}

	TEST_METHOD( AmfObject_IAmfValue_GetByteArrayTest )
	{
		InvalidOperationTest( []( AmfObject^ obj )
		{
			obj->GetByteArray();
		} );
	}

	TEST_METHOD( AmfObject_IAmfValue_GetVectorIntTest )
	{
		InvalidOperationTest( []( AmfObject^ obj )
		{
			obj->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfObject_IAmfValue_GetVectorUintTest )
	{
		InvalidOperationTest( []( AmfObject^ obj )
		{
			obj->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfObject_IAmfValue_GetVectorDouble )
	{
		InvalidOperationTest( []( AmfObject^ obj )
		{
			obj->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfObject_IAmfValue_GetVectorObjectTest )
	{
		InvalidOperationTest( []( AmfObject^ obj )
		{
			obj->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfObject_IAmfValue_GetObjectTest )
	{
		const auto& obj = ref new AmfObject();
		Assert::AreEqual( obj, obj->GetObject() );
	}

	TEST_METHOD( AmfObject_IAmfValue_GetArrayTest )
	{
		InvalidOperationTest( []( AmfObject^ obj )
		{
			obj->GetArray();
		} );
	}

	TEST_METHOD( AmfObject_IAmfValue_GetDictionaryTest )
	{
		InvalidOperationTest( []( AmfObject^ obj )
		{
			obj->GetDictionary();
		} );
	}

#pragma endregion

#pragma region IAmfObject methods

	TEST_METHOD( AmfObject_IAmfObject_GetNamedValueTest )
	{
		auto obj = ref new AmfObject();
		const auto& val = AmfValue::CreateBooleanValue( false );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, val );

		const auto& testValue = obj->GetNamedValue( key );
		Assert::IsTrue( testValue->ValueType == AmfValueType::Boolean );
		Assert::IsFalse( testValue->GetBoolean() );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedValueTest_OutOfRange )
	{
		const auto& obj = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedValue( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedStringTest )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		Assert::AreEqual( val, obj->GetNamedString( key ) );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedStringTest_OutOfRange )
	{
		const auto& obj = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedString( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedStringTest_InvalidType )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = false;
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateBooleanValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedString( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedNumberTest )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = 2.5;
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateNumberValue( val ) );

		Assert::AreEqual( val, obj->GetNamedNumber( key ) );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedNumberTest_OutOfRange )
	{
		const auto& obj = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedNumber( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedNumberTest_InvalidType )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedNumber( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedDateTest )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = AssertHelper::GetDate( 2000, 10, 4 );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateDateValue( val ) );
		Assert::IsTrue( val.UniversalTime == obj->GetNamedDate( key ).UniversalTime );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedDateTest_OutOfRange )
	{
		const auto& obj = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedDate( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedDateTest_InvalidType )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedDate( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedBooleanTest )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = false;
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateBooleanValue( val ) );
		Assert::AreEqual( val, obj->GetNamedBoolean( key ) );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedBooleanTest_OutOfRange )
	{
		const auto& obj = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedBoolean( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedBooleanTest_InvalidType )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedBoolean( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedByteArrayTest )
	{
		const auto& obj = ref new AmfObject();
		U8Array^ val = { 3, 56 };
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateByteArrayValue( val ) );
		AssertHelper::AreArrayEqual( val, obj->GetNamedByteArray( key ) );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedByteArrayTest_OutOfRange )
	{
		const auto& obj = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedByteArray( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedByteArrayTest_InvalidType )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedByteArray( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedVectorIntTest )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::Collections::Vector<int32>{ 3, -2, 5, 63, 2 };
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateVectorIntValue( val ) );
		AssertHelper::AreVectorEqual( val, obj->GetNamedVectorInt( key ) );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedVectorIntTest_OutOfRange )
	{
		const auto& obj = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedVectorInt( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedVectorIntTest_InvalidType )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedVectorInt( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedVectorUintTest )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::Collections::Vector<uint32>{ 3, 55, 32 };
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateVectorUintValue( val ) );
		AssertHelper::AreVectorEqual( val, obj->GetNamedVectorUint( key ) );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedVectorUintTest_OutOfRange )
	{
		const auto& obj = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedVectorUint( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedVectorUintTest_InvalidType )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedVectorUint( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedVectorDoubleTest )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::Collections::Vector<double>{ 2.5, 3, 2, 44 };
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateVectorDoubleValue( val ) );
		AssertHelper::AreVectorEqual( val, obj->GetNamedVectorDouble( key ) );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedVectorDoubleTest_OutOfRange )
	{
		const auto& obj = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedVectorDouble( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedVectorDoubleTest_InvalidType )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedVectorDouble( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedVectorObjectTest )
	{
		const auto& obj = ref new AmfObject();
		Windows::Foundation::Collections::IVector<IAmfValue^>^ val = ref new Platform::Collections::Vector<IAmfValue^>{ AmfValue::CreateNumberValue( 5.3 ), AmfValue::CreateStringValue( L"testVal" ) };
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateVectorObjectValue( val ) );
		Assert::AreEqual( val, obj->GetNamedVectorObject( key ) );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedVectorObjectTest_OutOfRange )
	{
		const auto& obj = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedVectorObject( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedVectorObjectTest_InvalidType )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedVectorObject( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedObjectTest )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, val );
		Assert::AreEqual( val, obj->GetNamedObject( key ) );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedObjectTest_OutOfRange )
	{
		const auto& obj = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedObject( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedObjectTest_InvalidType )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedObject( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedArrayTest )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new AmfArray();
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, val );
		Assert::AreEqual( val, obj->GetNamedArray( key ) );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedArrayTest_OutOfRange )
	{
		const auto& obj = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedArray( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedArrayTest_InvalidType )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedArray( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedDictionaryTest )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new AmfDictionary();
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, val );
		Assert::AreEqual( val, obj->GetNamedDictionary( key ) );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedDictionaryTest_OutOfRange )
	{
		const auto& obj = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->GetNamedDictionary( key );
		} );
	}

	TEST_METHOD( AmfObject_IAmfObject_GetNamedDictionaryTest_InvalidType )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			obj->GetNamedDictionary( key );
		} );
	}

#pragma endregion

#pragma region IIterator methods

	TEST_METHOD( AmfObject_IIterator_FirstTest_NoneItem )
	{
		const auto& obj = ref new AmfObject();
		auto result = obj->First();
		Assert::AreEqual( false, result->HasCurrent );
	}

	TEST_METHOD( AmfObject_IIterator_FirstTest_SomeItems )
	{
		const auto& obj = ref new AmfObject( );
		obj->Insert( "x", AmfValue::CreateBooleanValue( true ) );
		obj->Insert( "y", AmfValue::CreateNumberValue( 50.0 ) );

		auto result = obj->First();
		Assert::AreEqual( true, result->HasCurrent );
		result->MoveNext();
		Assert::AreEqual( true, result->HasCurrent );
		result->MoveNext();
		Assert::AreEqual( false, result->HasCurrent );
	}

#pragma endregion

#pragma region IMap: read methods

	TEST_METHOD( AmfObject_IMapÅ]read_LookupTest )
	{
		const auto& obj = ref new AmfObject();
		IAmfValue^ val = AmfValue::CreateNumberValue( 5.5 );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, val );
		Assert::AreEqual( val, obj->Lookup( key ) );
	}

	TEST_METHOD( AmfObject_IMapÅ]read_LookupTest_OutOfRange )
	{
		const auto& obj = ref new AmfObject();
		const auto& key = ref new Platform::String( L"testKey" );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			obj->Lookup( key );
		} );
	}

	TEST_METHOD( AmfObject_IMapÅ]read_HasKeyTest_True )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		Assert::IsTrue( obj->HasKey( key ) );
	}

	TEST_METHOD( AmfObject_IMapÅ]read_HasKeyTest_False )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = ref new Platform::String( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->SetNamedValue( key, AmfValue::CreateStringValue( val ) );
		Assert::IsFalse( obj->HasKey( L"Invalid Key" ) );
	}

	TEST_METHOD( AmfObject_IMapÅ]read_GetViewTest )
	{
		const auto& obj = ref new AmfObject();
		Assert::IsNotNull( obj->GetView() );
	}

#pragma endregion

#pragma region IMap: write methods

	TEST_METHOD( AmfObject_IMapÅ]write_InsertTest )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = AmfValue::CreateStringValue( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->Insert( key, val );

		const auto& testValue = obj->GetNamedValue( key );
		Assert::IsTrue( testValue->ValueType == AmfValueType::String );
		Assert::AreEqual( L"testValue", testValue->GetString() );
	}

	TEST_METHOD( AmfObject_IMapÅ]write_RemoveTest )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = AmfValue::CreateStringValue( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		obj->Insert( key, val );
		obj->Remove( key );
		Assert::IsFalse( obj->HasKey( key ) );
	}

	TEST_METHOD( AmfObject_IMapÅ]write_ClearTest )
	{
		const auto& obj = ref new AmfObject();
		const auto& val = AmfValue::CreateStringValue( L"testValue" );
		const auto& key = ref new Platform::String( L"testKey" );
		for( size_t i = 0; i < 25; i++ )
		{
			obj->Insert( key + i, val );
		}
		obj->Clear();
		Assert::IsFalse( obj->HasKey( key ) );
	}

#pragma endregion

#pragma region IStringable methods

	TEST_METHOD( AmfObject_IStringable_ToStringTest_NoneItem )
	{
		const auto& obj = ref new AmfObject();
		Assert::AreEqual( L"{}", obj->ToString() );
	}
	
	TEST_METHOD( AmfObject_IStringable_ToStringTest_SomeItems )
	{
		const auto& obj = ref new AmfObject();
		obj->Insert( "x", AmfValue::CreateBooleanValue( true ) );
		obj->Insert( "y", AmfValue::CreateNumberValue( 50.0 ) );
		Assert::AreEqual( L"{\"x\": true, \"y\": 50}", obj->ToString() );
	}

#pragma endregion

private:
	void InvalidOperationTest( std::function<void( AmfObject^ )> testHandler )
	{
		const auto& obj = ref new AmfObject();
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			testHandler( obj );
		} );
	}
};