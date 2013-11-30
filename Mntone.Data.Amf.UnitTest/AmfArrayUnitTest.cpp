#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfArrayUnitTest )
{
public:
#pragma region IAmfArrayFactory methods

	TEST_METHOD( AmfArray_IAmfArrayFactory_ConstractorTest )
	{
		const auto& ary = ref new AmfArray();
		Assert::IsTrue( ary->ValueType == AmfValueType::Array );
		Assert::AreEqual( 0u, ary->Size );
	}

#pragma endregion

#pragma region IAmfArrayStatics methods

	TEST_METHOD( AmfArray_IAmfArrayStatics_ParseTest_Default )
	{
		const auto& ary = AmfArray::Parse( ref new U8Array{ 6 } );
		Assert::IsTrue( ary->ValueType == AmfValueType::Undefined );
	}

	TEST_METHOD( AmfArray_IAmfArrayStatics_ParseTest_Amf0 )
	{
		const auto& ary = AmfArray::Parse( ref new U8Array{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, AmfEncodingType::Amf0 );
		Assert::IsTrue( ary->ValueType == AmfValueType::Number );
		Assert::AreEqual( 0.0, ary->GetNumber() );
	}

	TEST_METHOD( AmfArray_IAmfArrayStatics_ParseTest_Amf3 )
	{
		const auto& ary = AmfArray::Parse( ref new U8Array{ 0 }, AmfEncodingType::Amf3 );
		Assert::IsTrue( ary->ValueType == AmfValueType::Undefined );
	}

	TEST_METHOD( AmfArray_IAmfArrayStatics_TryParseTest_Default )
	{
		AmfArray^ ary;
		Assert::IsTrue( AmfArray::TryParse( ref new U8Array{ 6 }, &ary ) );
		Assert::IsTrue( ary->ValueType == AmfValueType::Undefined );
	}

	TEST_METHOD( AmfArray_IAmfArrayStatics_TryParseTest_Amf0 )
	{
		AmfArray^ ary;
		Assert::IsTrue( AmfArray::TryParse( ref new U8Array{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, AmfEncodingType::Amf0, &ary ) );
		Assert::IsTrue( ary->ValueType == AmfValueType::Number );
		Assert::AreEqual( 0.0, ary->GetNumber() );
	}

	TEST_METHOD( AmfArray_IAmfArrayStatics_TryParseTest_Amf3 )
	{
		AmfArray^ ary;
		Assert::IsTrue( AmfArray::TryParse( ref new U8Array{ 0 }, AmfEncodingType::Amf3, &ary ) );
		Assert::IsTrue( ary->ValueType == AmfValueType::Undefined );
	}

#pragma endregion

#pragma region IAmfValue methods

	TEST_METHOD( AmfArray_IAmfValue_GetBooleanTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetBoolean();
		} );
	}

	TEST_METHOD( AmfArray_IAmfValue_GetNumberTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetNumber();
		} );
	}

	TEST_METHOD( AmfArray_IAmfValue_GetStringTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetString();
		} );
	}

	TEST_METHOD( AmfArray_IAmfValue_GetDateTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetDate();
		} );
	}

	TEST_METHOD( AmfArray_IAmfValue_GetByteArrayTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetByteArray();
		} );
	}

	TEST_METHOD( AmfArray_IAmfValue_GetVectorIntTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfArray_IAmfValue_GetVectorUintTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfArray_IAmfValue_GetVectorDouble )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfArray_IAmfValue_GetVectorObjectTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetObject();
		} );
	}

	TEST_METHOD( AmfArray_IAmfValue_GetObjectTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfArray_IAmfValue_GetArrayTest )
	{
		const auto& ary = ref new AmfArray();
		Assert::AreEqual( ary, ary->GetArray() );
	}

	TEST_METHOD( AmfArray_IAmfValue_GetDictionaryTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetDictionary();
		} );
	}

#pragma endregion

#pragma region IAmfArray methods

	TEST_METHOD( AmfArray_IAmfArray_GetBooleanAtTest )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateBooleanValue( false ) );
		Assert::AreEqual( false, ary->GetBooleanAt( 0 ) );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetBooleanAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateBooleanValue( false ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetBooleanAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetBooeanAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type value" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetBooleanAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetStringAtTest )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"get string test" ) );
		Assert::AreEqual( L"get string test", ary->GetStringAt( 0 ) );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetStringAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"get string test" ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetStringAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetStringAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateBooleanValue( false ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetStringAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetNumberAtTest )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateNumberValue( 2.5 ) );
		Assert::AreEqual( 2.5, ary->GetNumberAt( 0 ) );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetNumberAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateNumberValue( 2.5 ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetNumberAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetNumberAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetNumberAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetDateAtTest )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateDateValue( AssertHelper::GetDate( 2000, 12, 4 ) ) );
		Assert::IsTrue( AssertHelper::GetDate( 2000, 12, 4 ).UniversalTime == ary->GetDateAt( 0 ).UniversalTime );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetDateAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateDateValue( AssertHelper::GetDate( 2000, 12, 4 ) ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetDateAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetDateAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetDateAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetByteArrayAtTest )
	{
		auto ary = ref new AmfArray();
		Platform::Array<uint8>^ byteArray = { 255, 222, 21 };
		ary->Append( AmfValue::CreateByteArrayValue( byteArray ) );
		AssertHelper::AreArrayEqual( byteArray, ary->GetByteArrayAt( 0 ) );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetByteArrayAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		Platform::Array<uint8>^ byteArray = { 255, 222, 21 };
		ary->Append( AmfValue::CreateByteArrayValue( byteArray ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetByteArrayAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetByteArrayAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetByteArrayAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetVectorDoubleAtTest )
	{
		auto ary = ref new AmfArray();
		auto doubleVector = ref new Platform::Collections::Vector<float64>{ 2.4, 2.1 };
		ary->Append( AmfValue::CreateVectorDoubleValue( doubleVector ) );
		AssertHelper::AreVectorEqual( doubleVector, ary->GetVectorDoubleAt( 0 ) );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetVectorDoubleAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		auto doubleVector = ref new Platform::Collections::Vector<float64>{ 2.4, 2.1 };
		ary->Append( AmfValue::CreateVectorDoubleValue( doubleVector ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetVectorDoubleAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetVectorDoubleAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetVectorDoubleAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetVectorIntAtTest )
	{
		auto ary = ref new AmfArray();
		auto intVector = ref new Platform::Collections::Vector<int>{ 5, 2 };
		ary->Append( AmfValue::CreateVectorIntValue( intVector ) );
		AssertHelper::AreVectorEqual( intVector, ary->GetVectorIntAt( 0 ) );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetVectorIntAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		auto intVector = ref new Platform::Collections::Vector<int>{ 5, 2 };
		ary->Append( AmfValue::CreateVectorIntValue( intVector ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetVectorIntAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetVectorIntAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetVectorIntAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetVectorUintAtTest )
	{
		auto ary = ref new AmfArray();
		auto uintVector = ref new Platform::Collections::Vector<uint32>{ 5, 2 };
		ary->Append( AmfValue::CreateVectorUintValue( uintVector ) );
		AssertHelper::AreVectorEqual( uintVector, ary->GetVectorUintAt( 0 ) );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetVectorUintAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		auto uintVector = ref new Platform::Collections::Vector<uint32>{ 5, 2 };
		ary->Append( AmfValue::CreateVectorUintValue( uintVector ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetVectorUintAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetVectorUintAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetVectorUintAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetVectorObjectAtTest )
	{
		auto ary = ref new AmfArray();
		Windows::Foundation::Collections::IVector<IAmfValue^>^ vec = ref new Platform::Collections::Vector<IAmfValue^>{ ref new AmfObject(), ref new AmfObject() };
		ary->Append( AmfValue::CreateVectorObjectValue( vec ) );
		Assert::AreEqual( vec, ary->GetVectorObjectAt( 0 ) );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetVectorObjectAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		auto vec = ref new Platform::Collections::Vector<IAmfValue^>{ ref new AmfObject(), ref new AmfObject() };
		ary->Append( AmfValue::CreateVectorObjectValue( vec ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetVectorObjectAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetVectorObjectAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetVectorObjectAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetObjectAtTest )
	{
		auto ary = ref new AmfArray();
		auto amfObject = ref new AmfObject();
		ary->Append( amfObject );
		Assert::AreEqual( amfObject, ary->GetObjectAt( 0 ) );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetObjectAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		auto amfObject = ref new AmfObject();
		ary->Append( amfObject );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetObjectAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetObjectAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetObjectAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetArrayAtTest )
	{
		auto ary = ref new AmfArray();
		auto valAry = ref new AmfArray();
		ary->Append( valAry );
		Assert::AreEqual( valAry, ary->GetArrayAt( 0 ) );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetArrayAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		auto valAry = ref new AmfArray();
		ary->Append( valAry );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetArrayAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetArrayAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetArrayAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetDictionaryAtTest )
	{
		auto ary = ref new AmfArray();
		auto amfDictionary = ref new AmfDictionary();
		ary->Append( amfDictionary );
		Assert::AreEqual( amfDictionary, ary->GetDictionaryAt( 0 ) );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetDictionaryAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		auto amfDictionary = ref new AmfObject();
		ary->Append( amfDictionary );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetDictionaryAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_IAmfArray_GetDictionaryAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetDictionaryAt( 0 );
		} );
	}

#pragma endregion

#pragma region IIterator methods

	TEST_METHOD( AmfArray_IIterator_FirstTest_NoneItem )
	{
		const auto& ary = ref new AmfArray();
		auto result = ary->First();
		Assert::AreEqual( false, result->HasCurrent );
	}

	TEST_METHOD( AmfArray_IIterator_FirstTest_SomeItems )
	{
		const auto& ary = CreateDefaultArray();

		auto result = ary->First();
		Assert::AreEqual( true, result->HasCurrent );
		result->MoveNext();
		Assert::AreEqual( true, result->HasCurrent );
		result->MoveNext();
		Assert::AreEqual( false, result->HasCurrent );
	}

#pragma endregion

#pragma region IVector: read methods

	TEST_METHOD( AmfArray_IVectorÅ]read_GetAtTest )
	{
		const auto& ary = ref new AmfArray();
		ary->Append( xValue );
		CheckX( ary->GetAt( 0 ) );
	}

	TEST_METHOD( AmfArray_IVectorÅ]read_GetAtTest_OutOfRange )
	{
		const auto& ary = CreateDefaultArray();
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetAt( 2 );
		} );
	}

	TEST_METHOD( AmfArray_IVectorÅ]read_GetAtTest_NoneItem_OutOfRange )
	{
		const auto& ary = ref new AmfArray();
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_IMapÅ]read_GetViewTest )
	{
		const auto& ary = CreateDefaultArray();
		const auto& view = ary->GetView();
		Assert::IsNotNull( view );
		Assert::AreEqual( 2u, view->Size );
		CheckW( view->GetAt( 0 ) );
		CheckX( view->GetAt( 1 ) );
	}

	TEST_METHOD( AmfArray_IMapÅ]read_IndexOfTest )
	{
		const auto& ary = CreateDefaultArray();
		uint32 index;
		Assert::IsTrue( ary->IndexOf( xValue, &index ) );
		Assert::AreEqual( 1u, index );
	}

	TEST_METHOD( AmfArray_IMapÅ]read_IndexOfTest_NotFound )
	{
		const auto& ary = ref new AmfArray();
		uint32 index;
		Assert::IsFalse( ary->IndexOf( xValue, &index ) );
	}

#pragma endregion

#pragma region IVector: write methods

	TEST_METHOD( AmfArray_IVectorÅ]write_SetAtTest )
	{
		const auto& ary = CreateDefaultArray();
		ary->SetAt( 1u, zValue );
		Assert::AreEqual( 2u, ary->Size );

		CheckW( ary->GetAt( 0 ) );
		CheckZ( ary->GetAt( 1 ) );
	}

	TEST_METHOD( AmfArray_IVectorÅ]write_InsertTest )
	{
		const auto& ary = CreateDefaultArray();
		ary->InsertAt( 1u, zValue );
		Assert::AreEqual( 3u, ary->Size );

		CheckW( ary->GetAt( 0 ) );
		CheckZ( ary->GetAt( 1 ) );
		CheckX( ary->GetAt( 2 ) );
	}

	TEST_METHOD( AmfArray_IVectorÅ]write_RemoveAtTest )
	{
		const auto& ary = CreateDefaultArray();
		ary->RemoveAt( 0u );
		Assert::AreEqual( 1u, ary->Size );

		CheckX( ary->GetAt( 0 ) );
	}

	TEST_METHOD( AmfArray_IVectorÅ]write_AppendTest )
	{
		const auto& ary = CreateDefaultArray();
		CheckW( ary->GetAt( 0 ) );
		CheckX( ary->GetAt( 1 ) );
	}

	TEST_METHOD( AmfArray_IVectorÅ]write_RemoveAtEndTest )
	{
		const auto& ary = CreateDefaultArray();
		ary->RemoveAtEnd();
		Assert::AreEqual( 1u, ary->Size );

		CheckW( ary->GetAt( 0 ) );
	}

	TEST_METHOD( AmfArray_IVectorÅ]write_ClearTest )
	{
		const auto& ary = CreateDefaultArray();
		ary->Clear();
		Assert::AreEqual( 0u, ary->Size );
	}

#pragma endregion

#pragma region IVector: bulk transfer methods

	TEST_METHOD( AmfArray_IVectorÅ]bulkTransfer_GetManyTest )
	{
		const auto& ary = CreateDefaultArray();
		ary->Append( zValue );
		Assert::AreEqual( 3u, ary->Size );

		auto pcAry = ref new Platform::Array<IAmfValue^>( 2 );
		ary->GetMany( 1u, pcAry );

		CheckX( pcAry[0] );
		CheckZ( pcAry[1] );
	}

	TEST_METHOD( AmfArray_IVectorÅ]bulkTransfer_ReplaceAllTest )
	{
		const auto& ary = CreateDefaultArray();
		Assert::AreEqual( 2u, ary->Size );

		auto pcAry = ref new Platform::Array<IAmfValue^>( 2 );
		pcAry[0] = yValue;
		pcAry[1] = zValue;
		ary->ReplaceAll( pcAry );
		Assert::AreEqual( 2u, ary->Size );

		CheckY( ary->GetAt( 0 ) );
		CheckZ( ary->GetAt( 1 ) );
	}

#pragma endregion

#pragma region IStringable methods

	TEST_METHOD( AmfArray_IStringable_ToStringTest_NoneItem )
	{
		const auto& ary = ref new AmfArray();
		Assert::AreEqual( L"[]", ary->ToString() );
	}

	TEST_METHOD( AmfArray_IStringable_ToStringTest_SomeItems )
	{
		const auto& ary = ref new AmfArray();
		ary->Append( AmfValue::CreateBooleanValue( true ) );
		ary->Append( AmfValue::CreateNumberValue( 50.0 ) );
		Assert::AreEqual( L"[true, 50]", ary->ToString() );
	}

#pragma endregion

private:
	void InvalidOperationTest( std::function<void( AmfArray^ )> testHandler )
	{
		const auto& ary = ref new AmfArray();
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			testHandler( ary );
		} );
	}

	AmfValue^ wValue = AmfValue::CreateStringValue( "abc" );
	AmfValue^ xValue = AmfValue::CreateBooleanValue( true );
	AmfValue^ yValue = AmfValue::CreateNumberValue( 50.0 );
	AmfValue^ zValue = AmfValue::CreateUndefinedValue();

	void CheckW( IAmfValue^ value )
	{
		Assert::IsTrue( value->ValueType == AmfValueType::String );
		Assert::AreEqual( L"abc", value->GetString() );
	}

	void CheckX( IAmfValue^ value )
	{
		Assert::IsTrue( value->ValueType == AmfValueType::Boolean );
		Assert::AreEqual( true, value->GetBoolean()  );
	}

	void CheckY( IAmfValue^ value )
	{
		Assert::IsTrue( value->ValueType == AmfValueType::Number );
		Assert::AreEqual( 50.0, value->GetNumber() );
	}

	void CheckZ( IAmfValue^ value )
	{
		Assert::IsTrue( value->ValueType == AmfValueType::Undefined );
	}

	AmfArray^ CreateDefaultArray()
	{
		const auto& ary = ref new AmfArray();
		ary->Append( wValue );
		ary->Append( xValue );
		return ary;
	}
};