#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( AmfArrayUnitTest )
{
public:
	TEST_METHOD( AmfArray_ConstractorTest )
	{
		const auto& ary = ref new AmfArray();
		Assert::IsTrue( ary->ValueType == AmfValueType::Array );
		Assert::AreEqual<uint32>( 0, ary->Size );
	}

	TEST_METHOD( AmfArray_CreateStrictArrayTest_Member )
	{
		const auto& ary = ref new AmfArray();
		Assert::IsTrue( ary->ValueType == AmfValueType::Array );
		Assert::AreEqual<uint32>( 0, ary->Size );
	}

	TEST_METHOD( AmfArray_AppendAndGetFirstTest )
	{
		const auto& ary = ref new AmfArray();
		ary->Append( AmfValue::CreateBooleanValue( false ) );
		Assert::AreEqual<uint32>( 1, ary->Size );

		const auto& firstValue = ary->GetAt( 0 );
		Assert::IsTrue( firstValue->ValueType == AmfValueType::Boolean );
		Assert::IsFalse( firstValue->GetBoolean() );
	}

	TEST_METHOD( AmfArray_NoneItemTest_OutOfRangeException )
	{
		const auto& ary = ref new AmfArray();

		Assert::ExpectException<Platform::OutOfBoundsException^>( [ary]
		{
			ary->GetAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_GetBooleanTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetBoolean();
		} );
	}

	TEST_METHOD( AmfArray_GetNumberTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetNumber();
		} );
	}

	TEST_METHOD( AmfArray_GetStringTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetString();
		} );
	}

	TEST_METHOD( AmfArray_GetDateTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetDate();
		} );
	}

	TEST_METHOD( AmfArray_GetByteArrayTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetByteArray();
		} );
	}

	TEST_METHOD( AmfArray_GetVectorIntTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetVectorInt();
		} );
	}

	TEST_METHOD( AmfArray_GetVectorUintTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetVectorUint();
		} );
	}

	TEST_METHOD( AmfArray_GetVectorDouble )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetVectorDouble();
		} );
	}

	TEST_METHOD( AmfArray_GetVectorObjectTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetObject();
		} );
	}

	TEST_METHOD( AmfArray_GetObjectTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetVectorObject();
		} );
	}

	TEST_METHOD( AmfArray_GetDictionaryTest )
	{
		InvalidOperationTest( []( AmfArray^ ary )
		{
			ary->GetDictionary();
		} );
	}

	TEST_METHOD( AmfArray_GetArrayTest )
	{
		const auto& ary = ref new AmfArray();
		Assert::AreEqual( ary, ary->GetArray() );
	}

	TEST_METHOD( AmfArray_ToStringTest_NoneItem )
	{
		const auto& ary = ref new AmfArray();
		Assert::AreEqual( L"[]", ary->ToString() );
	}

	TEST_METHOD( AmfArray_ToStringTest_SomeItems )
	{
		const auto& ary = ref new AmfArray();
		ary->Append( AmfValue::CreateBooleanValue( true ) );
		ary->Append( AmfValue::CreateNumberValue( 50.0 ) );
		Assert::AreEqual( L"[true, 50]", ary->ToString() );
	}

	TEST_METHOD( AmfArray_ParseTest_Default )
	{
		const auto& ary = AmfArray::Parse( ref new U8Array{ 6 } );
		Assert::IsTrue( ary->ValueType == AmfValueType::Undefined );
	}

	TEST_METHOD( AmfArray_ParseTest_Amf0 )
	{
		const auto& ary = AmfArray::Parse( ref new U8Array{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, AmfEncodingType::Amf0 );
		Assert::IsTrue( ary->ValueType == AmfValueType::Number );
		Assert::AreEqual( 0.0, ary->GetNumber() );
	}

	TEST_METHOD( AmfArray_ParseTest_Amf3 )
	{
		const auto& ary = AmfArray::Parse( ref new U8Array{ 0 }, AmfEncodingType::Amf3 );
		Assert::IsTrue( ary->ValueType == AmfValueType::Undefined );
	}

	TEST_METHOD( AmfArray_TryParseTest_Default )
	{
		AmfArray^ ary;
		Assert::IsTrue( AmfArray::TryParse( ref new U8Array{ 6 }, &ary ) );
		Assert::IsTrue( ary->ValueType == AmfValueType::Undefined );
	}

	TEST_METHOD( AmfArray_TryParseTest_Amf0 )
	{
		AmfArray^ ary;
		Assert::IsTrue( AmfArray::TryParse( ref new U8Array{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, AmfEncodingType::Amf0, &ary ) );
		Assert::IsTrue( ary->ValueType == AmfValueType::Number );
		Assert::AreEqual( 0.0, ary->GetNumber() );
	}

	TEST_METHOD( AmfArray_TryParseTest_Amf3 )
	{
		AmfArray^ ary;
		Assert::IsTrue( AmfArray::TryParse( ref new U8Array{ 0 }, AmfEncodingType::Amf3, &ary ) );
		Assert::IsTrue( ary->ValueType == AmfValueType::Undefined );
	}

	TEST_METHOD( AmfArray_GetBooleanAtTest )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateBooleanValue( false ) );
		Assert::AreEqual( false, ary->GetBooleanAt( 0 ) );
	}

	TEST_METHOD( AmfArray_GetBooleanAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateBooleanValue( false ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetBooleanAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_GetBooeanAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type value" ) );

		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetBooleanAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_GetStringAtTest )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"get string test" ) );
		Assert::AreEqual( L"get string test", ary->GetStringAt( 0 ) );
	}

	TEST_METHOD( AmfArray_GetStringAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"get string test" ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetStringAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_GetStringAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateBooleanValue( false ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetStringAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_GetNumberAtTest )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateNumberValue( 2.5 ) );
		Assert::AreEqual( 2.5, ary->GetNumberAt( 0 ) );
	}

	TEST_METHOD( AmfArray_GetNumberAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateNumberValue( 2.5 ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetNumberAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_GetNumberAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetNumberAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_GetDateAtTest )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateDateValue( AssertHelper::GetDate( 2000, 12, 4 ) ) );
		Assert::IsTrue( AssertHelper::GetDate( 2000, 12, 4 ).UniversalTime == ary->GetDateAt( 0 ).UniversalTime );
	}

	TEST_METHOD( AmfArray_GetDateAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateDateValue( AssertHelper::GetDate( 2000, 12, 4 ) ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetDateAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_GetDateAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetDateAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_GetByteArrayAtTest )
	{
		auto ary = ref new AmfArray();
		Platform::Array<uint8>^ byteArray = { 255, 222, 21 };
		ary->Append( AmfValue::CreateByteArrayValue( byteArray ) );
		AssertHelper::AreArrayEqual( byteArray, ary->GetByteArrayAt( 0 ) );
	}

	TEST_METHOD( AmfArray_GetByteArrayAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		Platform::Array<uint8>^ byteArray = { 255, 222, 21 };
		ary->Append( AmfValue::CreateByteArrayValue( byteArray ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetByteArrayAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_GetByteArrayAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetByteArrayAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_GetVectorDoubleAtTest )
	{
		auto ary = ref new AmfArray();
		auto doubleVector = ref new Platform::Collections::Vector<float64>{ 2.4, 2.1 };
		ary->Append( AmfValue::CreateVectorDoubleValue( doubleVector ) );
		AssertHelper::AreVectorEqual( doubleVector, ary->GetVectorDoubleAt( 0 ) );
	}

	TEST_METHOD( AmfArray_GetVectorDoubleAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		auto doubleVector = ref new Platform::Collections::Vector<float64>{ 2.4, 2.1 };
		ary->Append( AmfValue::CreateVectorDoubleValue( doubleVector ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetVectorDoubleAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_GetVectorDoubleAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetVectorDoubleAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_GetVectorIntAtTest )
	{
		auto ary = ref new AmfArray();
		auto intVector = ref new Platform::Collections::Vector<int>{ 5, 2 };
		ary->Append( AmfValue::CreateVectorIntValue( intVector ) );
		AssertHelper::AreVectorEqual( intVector, ary->GetVectorIntAt( 0 ) );
	}

	TEST_METHOD( AmfArray_GetVectorIntAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		auto intVector = ref new Platform::Collections::Vector<int>{ 5, 2 };
		ary->Append( AmfValue::CreateVectorIntValue( intVector ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetVectorIntAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_GetVectorIntAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetVectorIntAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_GetVectorUintAtTest )
	{
		auto ary = ref new AmfArray();
		auto uintVector = ref new Platform::Collections::Vector<uint32>{ 5, 2 };
		ary->Append( AmfValue::CreateVectorUintValue( uintVector ) );
		AssertHelper::AreVectorEqual( uintVector, ary->GetVectorUintAt( 0 ) );
	}

	TEST_METHOD( AmfArray_GetVectorUintAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		auto uintVector = ref new Platform::Collections::Vector<uint32>{ 5, 2 };
		ary->Append( AmfValue::CreateVectorUintValue( uintVector ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetVectorUintAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_GetVectorUintAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetVectorUintAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_GetVectorObjectAtTest )
	{
		auto ary = ref new AmfArray();
		Windows::Foundation::Collections::IVector<IAmfValue^>^ vec = ref new Platform::Collections::Vector<IAmfValue^>{ ref new AmfObject(), ref new AmfObject() };
		ary->Append( AmfValue::CreateVectorObjectValue( vec ) );
		Assert::AreEqual( vec, ary->GetVectorObjectAt( 0 ) );
	}

	TEST_METHOD( AmfArray_GetVectorObjectAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		auto vec = ref new Platform::Collections::Vector<IAmfValue^>{ ref new AmfObject(), ref new AmfObject() };
		ary->Append( AmfValue::CreateVectorObjectValue( vec ) );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetVectorObjectAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_GetVectorObjectAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetVectorObjectAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_GetObjectAtTest )
	{
		auto ary = ref new AmfArray();
		auto amfObject = ref new AmfObject();
		ary->Append( amfObject );
		Assert::AreEqual( amfObject, ary->GetObjectAt( 0 ) );
	}

	TEST_METHOD( AmfArray_GetObjectAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		auto amfObject = ref new AmfObject();
		ary->Append( amfObject );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetObjectAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_GetObjectAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetObjectAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_GetArrayAtTest )
	{
		auto ary = ref new AmfArray();
		auto valAry = ref new AmfArray();
		ary->Append( valAry );
		Assert::AreEqual( valAry, ary->GetArrayAt( 0 ) );
	}

	TEST_METHOD( AmfArray_GetArrayAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		auto valAry = ref new AmfArray();
		ary->Append( valAry );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetArrayAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_GetArrayAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetArrayAt( 0 );
		} );
	}

	TEST_METHOD( AmfArray_GetDictionaryAtTest )
	{
		auto ary = ref new AmfArray();
		auto amfDictionary = ref new AmfDictionary();
		ary->Append( amfDictionary );
		Assert::AreEqual( amfDictionary, ary->GetDictionaryAt( 0 ) );
	}

	TEST_METHOD( AmfArray_GetDictionaryAtTest_OutOfRange )
	{
		auto ary = ref new AmfArray();
		auto amfDictionary = ref new AmfObject();
		ary->Append( amfDictionary );
		Assert::ExpectException<Platform::OutOfBoundsException^>( [=]
		{
			ary->GetDictionaryAt( 1 );
		} );
	}

	TEST_METHOD( AmfArray_GetDictionaryAtTest_InvalidType )
	{
		auto ary = ref new AmfArray();
		ary->Append( AmfValue::CreateStringValue( L"invalid type" ) );
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			ary->GetDictionaryAt( 0 );
		} );
	}

private:
	void InvalidOperationTest( std::function<void( AmfArray^ )> testHandler )
	{
		const auto& ary = ref new AmfArray();
		AssertHelper::ExpectInvalidOperatonException( [=]
		{
			testHandler( ary );
		} );
	}
};