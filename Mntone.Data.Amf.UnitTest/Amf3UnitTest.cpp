#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

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

	TEST_METHOD( Amf3_⑤DoubleTest‐0_0．0 )
	{
		TestAmf3( ref new TestByteArray{ 5, 0, 0, 0, 0, 0, 0, 0, 0 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Double );
			Assert::AreEqual( 0.0, amfValue->GetDouble() );
		} );
	}

	TEST_METHOD( Amf3_⑤DoubleTest‐1_0．5 )
	{
		TestAmf3( ref new TestByteArray{ 5, 0x3f, 0xe0, 0, 0, 0, 0, 0, 0 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Double );
			Assert::AreEqual( 0.5, amfValue->GetDouble() );
		} );
	}

	TEST_METHOD( Amf3_⑥StringTest‐0_Null )
	{
		TestAmf3( ref new TestByteArray{ 6, 1 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::String );
			Assert::AreEqual( amfValue->GetString()->Data(), L"" );
		} );
	}

	TEST_METHOD( Amf3_⑥StringTest‐1_Ascii )
	{
		TestAmf3( ref new TestByteArray{ 6, 11, 0x41, 0x53, 0x43, 0x49, 0x49 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::String );
			Assert::AreEqual( amfValue->GetString()->Data(), L"ASCII" );
		} );
	}

	TEST_METHOD( Amf3_⑥StringTest‐2_RandomCharactors1 )
	{
		TestAmf3( ref new TestByteArray{ 6, 13, 0xc2, 0xbd, 0x3a, 0x20, 0x32, 0x42 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::String );
			Assert::AreEqual( L"½: 2B", amfValue->GetString()->Data() );
		} );
	}

	TEST_METHOD( Amf3_⑥StringTest‐3_RandomCharactors2 )
	{
		TestAmf3( ref new TestByteArray{ 6, 15, 0xe2, 0x91, 0xb4, 0x3a, 0x20, 0x33, 0x42 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::String );
			Assert::AreEqual( L"⑴: 3B", amfValue->GetString()->Data() );
		} );
	}

	TEST_METHOD( Amf3_⑦XmlDocumentTest‐0_RootNode )
	{
		TestAmf3( ref new TestByteArray{ 7, 13, 0x3c, 0x72, 0x6f, 0x6f, 0x74, 0x3e }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Xml );
			Assert::AreEqual( L"<root>", amfValue->GetString()->Data() );
		} );
	}

	TEST_METHOD( Amf3_⑧DateTest‐0_2013／10／13 )
	{
		TestAmf3( ref new TestByteArray{ 8, 1, 0x42, 0x74, 0x1a, 0xd2, 0xe6, 0x18, 0x00, 0x00 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Date );

			const auto& exp = AssertHelper::GetDate( 2013, 10, 13 );
			Assert::IsTrue( exp.UniversalTime == amfValue->GetDate().UniversalTime );
		} );
	}

	TEST_METHOD( Amf3_⑧DateTest‐1_2013／11／02_20：28：52．0100 )
	{
		TestAmf3( ref new TestByteArray{ 8, 1, 0x42, 0x74, 0x21, 0x89, 0x2a, 0x18, 0x40, 0 }, []( IAmfValue^ amfValue )
		{
			Assert::IsTrue( amfValue->ValueType == AmfValueType::Date );

			const auto& exp = AssertHelper::GetDate( 2013, 11, 2, 20, 28, 52, 100 * 1000000 );
			Assert::IsTrue( exp.UniversalTime == amfValue->GetDate().UniversalTime );
		} );
	}

	TEST_METHOD( Amf3_ⓍMasterTest_RtmpCommandData )
	{
		TestAmf3( ref new TestByteArray{ 0x9, 0x9, 0x1, 0x6, 0xf, 0x5f, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x4, 0x1, 0xa, 0xb, 0x1, 0x19, 0x63, 0x61, 0x70, 0x61, 0x62, 0x69, 0x6c, 0x69, 0x74, 0x69, 0x65, 0x73, 0x4, 0x1f, 0xd, 0x66, 0x6d, 0x73, 0x56, 0x65, 0x72, 0x6, 0x1b, 0x46, 0x4d, 0x53, 0x2f, 0x33, 0x2c, 0x30, 0x2c, 0x31, 0x2c, 0x31, 0x32, 0x33, 0x1, 0xa, 0x1, 0x17, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x6, 0x29, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x73, 0x75, 0x63, 0x63, 0x65, 0x65, 0x64, 0x65, 0x64, 0x1d, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x45, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67, 0x4, 0x0, 0x9, 0x63, 0x6f, 0x64, 0x65, 0x6, 0x3b, 0x4e, 0x65, 0x74, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x2e, 0x53, 0x75, 0x63, 0x63, 0x65, 0x73, 0x73, 0xb, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x6, 0xd, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x1 }, []( IAmfValue^ amfValue )
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
	void TestAmf3( TestByteArray^ rawData, std::function<void( IAmfValue^ )> checkHandler )
	{
		const auto& amf = Amf3Parser::Parse( rawData );
		const auto& str = amf->ToString();
		Logger::WriteMessage( str->Data() );
		checkHandler( amf );

		//const auto& createData = Amf0Sequencer::Sequenceify( r );
		//Assert::AreEqual( rawData->Length, createData->Length );
		//AssertHelper::AreArrayEqual( rawData, createData );
	}
};