#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;
namespace WG = Windows::Globalization;

using TestByteArray = Platform::Array<uint8>;

TEST_CLASS( Amf3UnitTest )
{
public:
	TEST_METHOD( Amf3_⓪UndefinedTest )
	{
		TestAmf3( ref new TestByteArray{ 0 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Undefined );
		} );
	}

	TEST_METHOD( Amf3_①NullTest )
	{
		TestAmf3( ref new TestByteArray{ 1 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Null );
		} );
	}

	TEST_METHOD( Amf3_②BooleanFalseTest )
	{
		TestAmf3( ref new TestByteArray{ 2 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Boolean );
			Assert::IsFalse( amfValue->GetBoolean() );
		} );
	}

	TEST_METHOD( Amf3_③BooleanTrueTest )
	{
		TestAmf3( ref new TestByteArray{ 3 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Boolean );
			Assert::IsTrue( amfValue->GetBoolean() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐0_0 )
	{
		TestAmf3( ref new TestByteArray{ 4, 0 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 0, amfValue->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐1_1 )
	{
		TestAmf3( ref new TestByteArray{ 4, 1 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 1, amfValue->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐2_127 )
	{
		TestAmf3( ref new TestByteArray{ 4, 0x7f }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 127, amfValue->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐3_128 )
	{
		TestAmf3( ref new TestByteArray{ 4, 0x81, 0x00 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 128, amfValue->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐4_16383 )
	{
		TestAmf3( ref new TestByteArray{ 4, 0xff, 0x7f }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 16383, amfValue->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐5_16384 )
	{
		TestAmf3( ref new TestByteArray{ 4, 0x81, 0x80, 0x00 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 16384, amfValue->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐6_2097151 )
	{
		TestAmf3( ref new TestByteArray{ 4, 0xff, 0xff, 0x7f }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 2097151, amfValue->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐7_2097152 )
	{
		TestAmf3( ref new TestByteArray{ 4, 0x80, 0xc0, 0x80, 0x00 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 2097152, amfValue->GetInteger() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐8_536870911 )
	{
		TestAmf3( ref new TestByteArray{ 4, 0xff, 0xff, 0xff, 0xff }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Integer );
			Assert::AreEqual<uint32>( 536870911, amfValue->GetInteger() );
		} );
	}


	TEST_METHOD( FromValueParseTest_Double0 )
	{
		ParseTestDouble0( ValueParse );
	}

	TEST_METHOD( FromValueParseTest_ObjectNull )
	{
		ParseTestObjectNull( ValueParse );
	}

	TEST_METHOD( FromValueParseTest_ArrayNull )
	{
		ParseTestArrayNull( ValueParse );
	}

	TEST_METHOD( FromObjectParseTest_Double0 )
	{
		ParseTestDouble0( ObjectParse );
	}

	TEST_METHOD( FromObjectParseTest_ObjectNull )
	{
		ParseTestObjectNull( ObjectParse );
	}

	TEST_METHOD( FromObjectParseTest_ArrayNull )
	{
		ParseTestArrayNull( ObjectParse );
	}

	TEST_METHOD( FromArrayParseTest_Double0 )
	{
		ParseTestDouble0( ArrayParse );
	}

	TEST_METHOD( FromArrayParseTest_ObjectNull )
	{
		ParseTestObjectNull( ArrayParse );
	}

	TEST_METHOD( FromArrayParseTest_ArrayNull )
	{
		ParseTestArrayNull( ArrayParse );
	}

	TEST_METHOD( FromValueTryParseTest_Double0 )
	{
		ParseTestDouble0( ValueTryParse );
	}

	TEST_METHOD( FromValueTryParseTest_ObjectNull )
	{
		ParseTestObjectNull( ValueTryParse );
	}

	TEST_METHOD( FromValueTryParseTest_ArrayNull )
	{
		ParseTestArrayNull( ValueTryParse );
	}

	TEST_METHOD( FromObjectTryParseTest_Double0 )
	{
		ParseTestDouble0( ObjectTryParse );
	}

	TEST_METHOD( FromObjectTryParseTest_ObjectNull )
	{
		ParseTestObjectNull( ObjectTryParse );
	}

	TEST_METHOD( FromObjectTryParseTest_ArrayNull )
	{
		ParseTestArrayNull( ObjectTryParse );
	}

	TEST_METHOD( FromArrayTryParseTest_Double0 )
	{
		ParseTestDouble0( ArrayTryParse );
	}

	TEST_METHOD( FromArrayTryParseTest_ObjectNull )
	{
		ParseTestObjectNull( ArrayTryParse );
	}

	TEST_METHOD( FromArrayTryParseTest_ArrayNull )
	{
		ParseTestArrayNull( ArrayTryParse );
	}


	TEST_METHOD( Amf3_MasterTest_RtmpCommandData )
	{
		TestAmf3( ref new TestByteArray{ 10, 0, 0, 0, 4, 0x02, 0x00, 0x07, 0x5f, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x06, 0x66, 0x6d, 0x73, 0x56, 0x65, 0x72, 0x02, 0x00, 0x0d, 0x46, 0x4d, 0x53, 0x2f, 0x33, 0x2c, 0x30, 0x2c, 0x31, 0x2c, 0x31, 0x32, 0x33, 0x00, 0x0c, 0x63, 0x61, 0x70, 0x61, 0x62, 0x69, 0x6c, 0x69, 0x74, 0x69, 0x65, 0x73, 0x00, 0x40, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x03, 0x00, 0x05, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x02, 0x00, 0x06, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x00, 0x04, 0x63, 0x6f, 0x64, 0x65, 0x02, 0x00, 0x1d, 0x4e, 0x65, 0x74, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x2e, 0x53, 0x75, 0x63, 0x63, 0x65, 0x73, 0x73, 0x00, 0x0b, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x02, 0x00, 0x14, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x73, 0x75, 0x63, 0x63, 0x65, 0x65, 0x64, 0x65, 0x64, 0x00, 0x0e, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x45, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Array );

			const auto& ary = amfValue->GetArray();
			Assert::AreEqual<uint32>( 4, ary->Size );
			Assert::AreEqual( L"_result", ary->GetStringAt( 0 )->Data() );
			Assert::AreEqual( 1.0, ary->GetDoubleAt( 1 ) );

			const auto& objLapped = ary->GetAt( 2 );
			Assert::IsTrue( objLapped->ValueType == AmfValueType::Object );

			const auto& obj = objLapped->GetObject();
			Assert::AreEqual( L"FMS/3,0,1,123", obj->GetNamedString( "fmsVer" )->Data() );
			Assert::AreEqual( 31.0, obj->GetNamedDouble( "capabilities" ) );

			const auto& objLapped2 = ary->GetAt( 3 );
			Assert::IsTrue( objLapped2->ValueType == AmfValueType::Object );

			const auto& obj2 = objLapped2->GetObject();
			Assert::AreEqual( L"status", obj2->GetNamedString( "level" )->Data() );

			Assert::AreEqual( L"NetConnection.Connect.Success", obj2->GetNamedString( "code" )->Data() );
			Assert::AreEqual( L"Connection succeeded", obj2->GetNamedString( "description" )->Data() );
			Assert::AreEqual( 0.0, obj2->GetNamedDouble( "objectEncoding" ) );
		} );
	}

private:
	static void ParseTestDouble0( std::function<IAmfValue^ ( TestByteArray^ )> parseFunc )
	{
		Assert::AreEqual( 0.0, parseFunc( ref new TestByteArray{ 0, 0, 0, 0, 0, 0, 0, 0, 0 } )->GetDouble() );
	}

	static void ParseTestObjectNull( std::function<IAmfValue^ ( TestByteArray^ )> parseFunc )
	{
		Assert::AreEqual<uint32>( 0, parseFunc( ref new TestByteArray{ 3, 0, 0, 9 } )->GetObject()->Size );
	}

	static void ParseTestArrayNull( std::function<IAmfValue^ ( TestByteArray^ )> parseFunc )
	{
		Assert::AreEqual<uint32>( 0, parseFunc( ref new TestByteArray{ 10, 0, 0, 0, 0 } )->GetArray()->Size );
	}

	static AmfValue^ ValueParse( TestByteArray^ byteArray )
	{
		return AmfValue::Parse( byteArray, AmfEncodingType::Amf0 );
	}

	static AmfValue^ ValueTryParse( TestByteArray^ byteArray )
	{
		AmfValue^ outValue;
		AmfValue::TryParse( byteArray, AmfEncodingType::Amf0, &outValue );
		return outValue;
	}

	static AmfObject^ ObjectParse( TestByteArray^ byteArray )
	{
		return AmfObject::Parse( byteArray, AmfEncodingType::Amf0 );
	}

	static AmfObject^ ObjectTryParse( TestByteArray^ byteArray )
	{
		AmfObject^ outObject;
		AmfObject::TryParse( byteArray, AmfEncodingType::Amf0, &outObject );
		return outObject;
	}

	static AmfArray^ ArrayParse( TestByteArray^ byteArray )
	{
		return AmfArray::Parse( byteArray, AmfEncodingType::Amf0 );
	}

	static AmfArray^ ArrayTryParse( TestByteArray^ byteArray )
	{
		AmfArray^ outArray;
		AmfArray::TryParse( byteArray, AmfEncodingType::Amf0, &outArray );
		return outArray;
	}


	static void TestAmf3( TestByteArray^ rawData, std::function<void( IAmfValue^ )> checkHandler )
	{
		auto r = Amf3Parser::Parse( rawData );
		auto st = r->ToString();
		checkHandler( r );
		//const auto& create_data = Amf0Sequencer::Sequenceify( r );

		//Assert::IsTrue( ArrayEquals( rawData, create_data ) );
	}

	static bool ArrayEquals( const Platform::Array<uint8>^ firstArray, const Platform::Array<uint8>^ secondArray )
	{
		if( firstArray->Length != secondArray->Length )
			return false;
		for( auto i = 0u; i < firstArray->Length; ++i )
		{
			if( !secondArray[i].Equals( secondArray[i] ) )
			{
				return false;
			}
		}
		return true;
	}
};