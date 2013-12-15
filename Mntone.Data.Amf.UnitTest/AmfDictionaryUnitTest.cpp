#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfDictionaryUnitTest )
{
public:
#pragma region IAmfDictionaryFactory methods

	TEST_METHOD( AmfDictionary_IAmfDictionaryFactory_ConstractorTest )
	{
		const auto& dic = ref new AmfDictionary();
		Assert::IsTrue( dic->ValueType == AmfValueType::Dictionary );
		Assert::AreEqual( 0u, dic->Size );
	}

#pragma endregion

#pragma region IAmfDictionaryStatics methods

	TEST_METHOD( AmfDictionary_IAmfDictionaryStatics_ParseTest_Default )
	{
		const auto& dic = AmfDictionary::Parse( ref new U8Array{ 6 } );
		Assert::IsTrue( dic->ValueType == AmfValueType::Undefined );
	}

	TEST_METHOD( AmfDictionary_IAmfDictionaryStatics_ParseTest_Amf0 )
	{
		const auto& dic = AmfDictionary::Parse( ref new U8Array{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, AmfEncodingType::Amf0 );
		Assert::IsTrue( dic->ValueType == AmfValueType::Number );
		Assert::AreEqual( 0.0, dic->GetNumber() );
	}

	TEST_METHOD( AmfDictionary_IAmfDictionaryStatics_ParseTest_Amf3 )
	{
		const auto& dic = AmfDictionary::Parse( ref new U8Array{ 0 }, AmfEncodingType::Amf3 );
		Assert::IsTrue( dic->ValueType == AmfValueType::Undefined );
	}

	TEST_METHOD( AmfDictionary_IAmfDictionaryStatics_TryParseTest_Default )
	{
		AmfDictionary^ dic;
		Assert::IsTrue( AmfDictionary::TryParse( ref new U8Array{ 6 }, &dic ) );
		Assert::IsTrue( dic->ValueType == AmfValueType::Undefined );
	}

	TEST_METHOD( AmfDictionary_IAmfDictionaryStatics_TryParseTest_Amf0 )
	{
		AmfDictionary^ dic;
		Assert::IsTrue( AmfDictionary::TryParse( ref new U8Array{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, AmfEncodingType::Amf0, &dic ) );
		Assert::IsTrue( dic->ValueType == AmfValueType::Number );
		Assert::AreEqual( 0.0, dic->GetNumber() );
	}

	TEST_METHOD( AmfDictionary_IAmfDictionaryStatics_TryParseTest_Amf3 )
	{
		AmfDictionary^ dic;
		Assert::IsTrue( AmfDictionary::TryParse( ref new U8Array{ 0 }, AmfEncodingType::Amf3, &dic ) );
		Assert::IsTrue( dic->ValueType == AmfValueType::Undefined );
	}

#pragma endregion

#pragma region IAmfValue methods

	TEST_METHOD( AmfDictionary_IAmfValue_GetBooleanTest )
	{
		InvalidOperationTest( []( AmfDictionary^ dic )
		{
			dic->GetBoolean();
		} );
	}

	TEST_METHOD( AmfDictionary_IAmfValue_GetNumberTest )
	{
		InvalidOperationTest( []( AmfDictionary^ dic )
		{
			dic->GetNumber();
		} );
	}

	TEST_METHOD( AmfDictionary_IAmfValue_GetStringTest )
	{
		InvalidOperationTest( []( AmfDictionary^ dic )
		{
			dic->GetString();
		} );
	}

	TEST_METHOD( AmfDictionary_IAmfValue_GetDateTest )
	{
		InvalidOperationTest( []( AmfDictionary^ dic )
		{
			dic->GetDate();
		} );
	}

	TEST_METHOD( AmfDictionary_IAmfValue_GetByteArrayTest )
	{
		InvalidOperationTest( []( AmfDictionary^ dic )
		{
			dic->GetByteArray();
		} );
	}

	TEST_METHOD( AmfDictionary_IAmfValue_GetVectorIntTest )
	{
		InvalidOperationTest( []( AmfDictionary^ dic )
		{
			dic->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfDictionary_IAmfValue_GetVectorUintTest )
	{
		InvalidOperationTest( []( AmfDictionary^ dic )
		{
			dic->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfDictionary_IAmfValue_GetVectorDouble )
	{
		InvalidOperationTest( []( AmfDictionary^ dic )
		{
			dic->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfDictionary_IAmfValue_GetVectorObjectTest )
	{
		InvalidOperationTest( []( AmfDictionary^ dic )
		{
			dic->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfDictionary_IAmfValue_GetObjectTest )
	{
		InvalidOperationTest( []( AmfDictionary^ dic )
		{
			dic->GetObject();
		} );
	}

	TEST_METHOD( AmfDictionary_IAmfValue_GetArrayTest )
	{
		InvalidOperationTest( []( AmfDictionary^ dic )
		{
			dic->GetArray();
		} );
	}

	TEST_METHOD( AmfDictionary_IAmfValue_GetDictionaryTest )
	{
		const auto& dic = ref new AmfDictionary();
		Assert::AreEqual( dic, dic->GetDictionary() );
	}

#pragma endregion

#pragma region IAmfDictionary: write methods

	TEST_METHOD( AmfDictionary_IAmfDictionaryÅ]write_AppendPairTest )
	{
		const auto& dic = ref new AmfDictionary();
		dic->AppendPair( wKey, wValue );
		dic->AppendPair( xKey, xValue );
		Assert::AreEqual( 2u, dic->Size );

		CheckW( dic->GetAt( 0 ) );
		CheckX( dic->GetAt( 1 ) );
	}

#pragma endregion

#pragma region IIterator methods

	TEST_METHOD( AmfDictionary_IIterator_FirstTest_NoneItem )
	{
		const auto& dic = ref new AmfDictionary();
		auto result = dic->First();
		Assert::AreEqual( false, result->HasCurrent );
	}

	TEST_METHOD( AmfDictionary_IIterator_FirstTest_SomeItems )
	{
		const auto& dic = CreateDefaultDictionary();

		auto result = dic->First();
		Assert::AreEqual( true, result->HasCurrent );
		result->MoveNext();
		Assert::AreEqual( true, result->HasCurrent );
		result->MoveNext();
		Assert::AreEqual( false, result->HasCurrent );
	}

#pragma endregion

#pragma region IVector: read methods

	TEST_METHOD( AmfDictionary_IVectorÅ]read_GetAtTest )
	{
		const auto& dic = ref new AmfDictionary();
		dic->Append( xPair );
		CheckX( dic->GetAt( 0 ) );
	}

	TEST_METHOD( AmfDictionary_IVectorÅ]read_GetAtTest_OutOfRange )
	{
		const auto& dic = CreateDefaultDictionary();
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			dic->GetAt( 2 );
		} );
	}

	TEST_METHOD( AmfDictionary_IVectorÅ]read_GetAtTest_NoneItem_OutOfRange )
	{
		const auto& dic = ref new AmfDictionary();
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			dic->GetAt( 0 );
		} );
	}

	TEST_METHOD( AmfDictionary_IMapÅ]read_GetViewTest )
	{
		const auto& dic = CreateDefaultDictionary();
		const auto& view = dic->GetView();
		Assert::IsNotNull( view );
		Assert::AreEqual( 2u, view->Size );
		CheckW( view->GetAt( 0 ) );
		CheckX( view->GetAt( 1 ) );
	}

	TEST_METHOD( AmfDictionary_IMapÅ]read_IndexOfTest )
	{
		const auto& dic = CreateDefaultDictionary();
		uint32 index;
		Assert::IsTrue( dic->IndexOf( xPair, &index ) );
		Assert::AreEqual( 1u, index );
	}

	TEST_METHOD( AmfDictionary_IMapÅ]read_IndexOfTest_NotFound )
	{
		const auto& dic = ref new AmfDictionary();
		uint32 index;
		Assert::IsFalse( dic->IndexOf( xPair, &index ) );
	}

#pragma endregion

#pragma region IVector: write methods

	TEST_METHOD( AmfDictionary_IVectorÅ]write_SetAtTest )
	{
		const auto& dic = CreateDefaultDictionary();
		dic->SetAt( 1u, zPair );
		Assert::AreEqual( 2u, dic->Size );

		CheckW( dic->GetAt( 0 ) );
		CheckZ( dic->GetAt( 1 ) );
	}

	TEST_METHOD( AmfDictionary_IVectorÅ]write_InsertTest )
	{
		const auto& dic = CreateDefaultDictionary();
		dic->InsertAt( 1u, zPair );
		Assert::AreEqual( 3u, dic->Size );

		CheckW( dic->GetAt( 0 ) );
		CheckZ( dic->GetAt( 1 ) );
		CheckX( dic->GetAt( 2 ) );
	}

	TEST_METHOD( AmfDictionary_IVectorÅ]write_RemoveAtTest )
	{
		const auto& dic = CreateDefaultDictionary();
		dic->RemoveAt( 0u );
		Assert::AreEqual( 1u, dic->Size );

		CheckX( dic->GetAt( 0 ) );
	}

	TEST_METHOD( AmfDictionary_IVectorÅ]write_AppendTest )
	{
		const auto& dic = CreateDefaultDictionary();
		CheckW( dic->GetAt( 0 ) );
		CheckX( dic->GetAt( 1 ) );
	}

	TEST_METHOD( AmfDictionary_IVectorÅ]write_RemoveAtEndTest )
	{
		const auto& dic = CreateDefaultDictionary();
		dic->RemoveAtEnd();
		Assert::AreEqual( 1u, dic->Size );

		CheckW( dic->GetAt( 0 ) );
	}

	TEST_METHOD( AmfDictionary_IVectorÅ]write_ClearTest )
	{
		const auto& dic = CreateDefaultDictionary();
		dic->Clear();
		Assert::AreEqual( 0u, dic->Size );
	}

#pragma endregion

#pragma region IVector: bulk transfer methods

	TEST_METHOD( AmfDictionary_IVectorÅ]bulkTransfer_GetManyTest )
	{
		const auto& dic = CreateDefaultDictionary();
		dic->Append( zPair );
		Assert::AreEqual( 3u, dic->Size );

		auto ary = ref new Platform::Array<AmfPair^>( 2 );
		dic->GetMany( 1u, ary );

		CheckX( ary[0] );
		CheckZ( ary[1] );
	}

	TEST_METHOD( AmfDictionary_IVectorÅ]bulkTransfer_ReplaceAllTest )
	{
		const auto& dic = CreateDefaultDictionary();
		Assert::AreEqual( 2u, dic->Size );

		auto ary = ref new Platform::Array<AmfPair^>( 2 );
		ary[0] = yPair;
		ary[1] = zPair;
		dic->ReplaceAll( ary );
		Assert::AreEqual( 2u, dic->Size );

		CheckY( dic->GetAt( 0 ) );
		CheckZ( dic->GetAt( 1 ) );
	}

#pragma endregion

#pragma region IStringable methods

	TEST_METHOD( AmfDictionary_IStringable_ToStringTest_NoneItem )
	{
		const auto& dic = ref new AmfDictionary();
		Assert::AreEqual( L"{}", dic->ToString() );
	}

	TEST_METHOD( AmfDictionary_IStringable_ToStringTest_SomeItems )
	{
		const auto& dic = ref new AmfDictionary();
		dic->AppendPair( AmfValue::CreateStringValue( "x" ), AmfValue::CreateBooleanValue( true ) );
		dic->AppendPair( AmfValue::CreateStringValue( "y" ), AmfValue::CreateNumberValue( 50.0 ) );
		Assert::AreEqual( L"{\"x\": true, \"y\": 50}", dic->ToString() );
	}

#pragma endregion

private:
	void InvalidOperationTest( std::function<void( AmfDictionary^ )> testHandler )
	{
		const auto& dic = ref new AmfDictionary();
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			testHandler( dic );
		} );
	}

	AmfValue^ wKey = AmfValue::CreateNumberValue( 3.0 );
	AmfValue^ wValue = AmfValue::CreateStringValue( "abc" );
	AmfPair^ wPair = ref new AmfPair( wKey, wValue );
	AmfValue^ xKey = AmfValue::CreateStringValue( "x" );
	AmfValue^ xValue = AmfValue::CreateBooleanValue( true );
	AmfPair^ xPair = ref new AmfPair( xKey, xValue );
	AmfValue^ yKey = AmfValue::CreateStringValue( "y" );
	AmfValue^ yValue = AmfValue::CreateNumberValue( 50.0 );
	AmfPair^ yPair = ref new AmfPair( yKey, yValue );
	AmfValue^ zKey = AmfValue::CreateStringValue( "z" );
	AmfValue^ zValue = AmfValue::CreateUndefinedValue();
	AmfPair^ zPair = ref new AmfPair( zKey, zValue );

	void CheckW( AmfPair^ pair )
	{
		const auto& key = pair->Key;
		Assert::IsTrue( key->ValueType == AmfValueType::Number );
		Assert::AreEqual( 3.0, key->GetNumber() );

		const auto& value = pair->Value;
		Assert::IsTrue( value->ValueType == AmfValueType::String );
		Assert::AreEqual( L"abc", value->GetString() );
	}

	void CheckX( AmfPair^ pair )
	{
		const auto& key = pair->Key;
		Assert::IsTrue( key->ValueType == AmfValueType::String );
		Assert::AreEqual( L"x", key->GetString() );

		const auto& value = pair->Value;
		Assert::IsTrue( value->ValueType == AmfValueType::Boolean );
		Assert::IsTrue( value->GetBoolean() );
	}

	void CheckY( AmfPair^ pair )
	{
		const auto& key = pair->Key;
		Assert::IsTrue( key->ValueType == AmfValueType::String );
		Assert::AreEqual( L"y", key->GetString() );

		const auto& value = pair->Value;
		Assert::IsTrue( value->ValueType == AmfValueType::Number );
		Assert::AreEqual( 50.0, value->GetNumber() );
	}

	void CheckZ( AmfPair^ pair )
	{
		const auto& key = pair->Key;
		Assert::IsTrue( key->ValueType == AmfValueType::String );
		Assert::AreEqual( L"z", key->GetString() );

		const auto& value = pair->Value;
		Assert::IsTrue( value->ValueType == AmfValueType::Undefined );
	}

	AmfDictionary^ CreateDefaultDictionary()
	{
		const auto& dic = ref new AmfDictionary();
		dic->Append( wPair );
		dic->Append( xPair );
		return dic;
	}
};