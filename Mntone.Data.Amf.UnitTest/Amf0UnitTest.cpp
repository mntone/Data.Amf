#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( Amf0UnitTest )
{
public:
	TEST_METHOD( Amf0_⓪NumberTest‐0_0．0 )
	{
		Test( ref new U8Array{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Double );
			Assert::AreEqual( 0.0, val->GetDouble() );
		} );
	}

	TEST_METHOD( Amf0_⓪NumbetTest‐1_0．5 )
	{
		Test( ref new U8Array{ 0, 0x3f, 0xe0, 0, 0, 0, 0, 0, 0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Double );
			Assert::AreEqual( 0.5, val->GetDouble() );
		} );
	}

	TEST_METHOD( Amf0_①BooleanTest‐0_true )
	{
		Test( ref new U8Array{ 1, 1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Boolean );
			Assert::AreEqual( true, val->GetBoolean() );
		} );
	}

	TEST_METHOD( Amf0_①BooleanTest‐1_false )
	{
		Test( ref new U8Array{ 1, 0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Boolean );
			Assert::AreEqual( false, val->GetBoolean() );
		} );
	}

	TEST_METHOD( Amf0_②StringTest‐0_Null )
	{
		Test( ref new U8Array{ 2, 0, 0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::String );
			Assert::AreEqual( L"", val->GetString()->Data() );
		} );
	}

	TEST_METHOD( Amf0_②StringTest‐1_Ascii )
	{
		Test( ref new U8Array{ 2, 0, 5, 0x41, 0x53, 0x43, 0x49, 0x49 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::String );
			Assert::AreEqual( L"ASCII", val->GetString() );
		} );
	}

	TEST_METHOD( Amf0_②StringTest‐2_RandomCharactors1 )
	{
		Test( ref new U8Array{ 2, 0, 6, 0xc2, 0xbd, 0x3a, 0x20, 0x32, 0x42 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::String );
			Assert::AreEqual( L"½: 2B", val->GetString() );
		} );
	}

	TEST_METHOD( Amf0_②StringTest‐3_RandomCharactors2 )
	{
		Test( ref new U8Array{ 2, 0, 7, 0xe2, 0x91, 0xb4, 0x3a, 0x20, 0x33, 0x42 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::String );
			Assert::AreEqual( L"⑴: 3B", val->GetString() );
		} );
	}

	TEST_METHOD( Amf0_③ObjectTest‐0_Null )
	{
		Test( ref new U8Array{ 3, 0, 0, 9 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Object );
			Assert::AreEqual<uint32>( 0, val->GetObject()->Size );
		} );
	}

	TEST_METHOD( Amf0_③ObjectTest‐1_BStringNull )
	{
		Test( ref new U8Array{ 3, 0, 1, 0x42, 2, 0, 0, 0, 0, 9 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Object );

			const auto& obj = val->GetObject();
			Assert::AreEqual<uint32>( 1, obj->Size );
			Assert::AreEqual( L"", obj->GetNamedString( "B" )->Data() );
		} );
	}

	TEST_METHOD( Amf0_③ObjectTest‐2_More )
	{
		Test( ref new U8Array{ 3, 0, 1, 0x44, 2, 0, 0, 0, 1, 0x43, 2, 0, 0, 0, 0, 9 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Object );

			const auto& obj = val->GetObject();
			Assert::AreEqual<uint32>( 2, obj->Size );
			Assert::IsNull( obj->GetNamedString( "D" ) );
			Assert::IsNull( obj->GetNamedString( "C" ) );
		} );
	}

	TEST_METHOD( Amf0_⑤ValueTypeTest‐0_Null )
	{
		Test( ref new U8Array{ 5 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Null );
		} );
	}

	TEST_METHOD( Amf0_⑥ValueTypeTest‐0_Undefined )
	{
		Test( ref new U8Array{ 6 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Undefined );
		} );
	}

	TEST_METHOD( Amf0_⑧EcmaArrayTest‐0_Null )
	{
		Test( ref new U8Array{ 8, 0, 0, 0, 0, 0, 0, 9 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::EcmaArray );
			Assert::AreEqual<uint32>( 0, val->GetObject()->Size );
		} );
	}

	TEST_METHOD( Amf0_⑧EcmaArrayTest‐1_StringNull )
	{
		Test( ref new U8Array{ 8, 0, 0, 0, 1, 0, 1, 0x30, 2, 0, 0, 0, 0, 9 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::EcmaArray );

			const auto& obj = val->GetObject();
			Assert::AreEqual<uint32>( 1, obj->Size );
			Assert::AreEqual( L"", obj->GetNamedString( "0" )->Data() );
		} );
	}

	TEST_METHOD( Amf0_⑩StrictArrayTest‐0_Null )
	{
		Test( ref new U8Array{ 10, 0, 0, 0, 0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );
			Assert::AreEqual<uint32>( 0, val->GetArray()->Size );
		} );
	}

	TEST_METHOD( Amf0_⑩StrinctArray‐1_0．0，True )
	{
		Test( ref new U8Array{ 10, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			Assert::AreEqual<uint32>( 2, ary->Size );
			Assert::AreEqual( 0.0, ary->GetDoubleAt( 0 ) );
			Assert::IsTrue( ary->GetBooleanAt( 1 ) );
		} );
	}

	TEST_METHOD( Amf0_⑪DateTest‐0_2013／10／13WithJST )
	{
		Test( ref new U8Array{ 11, 0x42, 0x74, 0x1a, 0xd2, 0xe6, 0x18, 0x00, 0x00, 0xfd, 0xe4 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Date );

			const auto& exp = AssertHelper::GetDate( 2013, 10, 13 );
			Assert::IsTrue( exp.UniversalTime == val->GetDate().UniversalTime );
		} );
	}

	TEST_METHOD( Amf0_⑪DateTest‐1_2013／11／02_20：28：52．0100WithJST )
	{
		Test( ref new U8Array{ 0x0b, 0x42, 0x74, 0x21, 0x89, 0x2a, 0x18, 0x40, 0x00, 0xfd, 0xe4 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Date );

			const auto& exp = AssertHelper::GetDate( 2013, 11, 2, 20, 28, 52, 100 * 1000000 );
			Assert::IsTrue( exp.UniversalTime == val->GetDate().UniversalTime );
		} );
	}

	TEST_METHOD( Amf0_⑫LongStringTest‐0 )
	{
		auto exp = ref new U8Array( 5 + 0x10000 );
		exp[0] = 12;
		exp[1] = 0;
		exp[2] = 1;
		exp[3] = 0;
		exp[4] = 0;

		std::wstring result;
		for( auto i = 0; i < 0x2000; ++i )
		{
			exp[5 + 8 * i] = 0x71;
			exp[5 + 8 * i + 1] = 0x72;
			exp[5 + 8 * i + 2] = 0x73;
			exp[5 + 8 * i + 3] = 0x74;
			exp[5 + 8 * i + 4] = 0x75;
			exp[5 + 8 * i + 5] = 0x76;
			exp[5 + 8 * i + 6] = 0x77;
			exp[5 + 8 * i + 7] = 0x78;
			result += L"qrstuvwx";
		}

		Test( exp, [result]( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::String );
			Assert::AreEqual( result.c_str(), val->GetString()->Data() );
		} );
	}

	TEST_METHOD( Amf0_⑮XmlDocumentTest‐0_RootNode )
	{
		Test( ref new U8Array{ 15, 0, 0, 0, 6, 0x3c, 0x72, 0x6f, 0x6f, 0x74, 0x3e }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Xml );
			Assert::AreEqual( L"<root>", val->GetString() );
		} );
	}

	TEST_METHOD( Amf0_⑯TypedObjectTest‐0_Null )
	{
		Test( ref new U8Array{ 16, 0, 4, 0x54, 0x65, 0x73, 0x74, 0, 0, 9 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Object );
			Assert::AreEqual<uint32>( 0, val->GetObject()->Size );
			Assert::AreEqual( L"Test", val->GetObject()->ClassName );
		} );
	}

	TEST_METHOD( Amf0_⑰UnknownTypeTest‐0 )
	{
		ParserFailureExceptionTest( ref new U8Array{ 17 } );
	}

	TEST_METHOD( Amf0_ⓍMasterTest_RtmpCommandData )
	{
		Test( ref new U8Array{ 10, 0, 0, 0, 4, 0x02, 0x00, 0x07, 0x5f, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x06, 0x66, 0x6d, 0x73, 0x56, 0x65, 0x72, 0x02, 0x00, 0x0d, 0x46, 0x4d, 0x53, 0x2f, 0x33, 0x2c, 0x30, 0x2c, 0x31, 0x2c, 0x31, 0x32, 0x33, 0x00, 0x0c, 0x63, 0x61, 0x70, 0x61, 0x62, 0x69, 0x6c, 0x69, 0x74, 0x69, 0x65, 0x73, 0x00, 0x40, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x03, 0x00, 0x05, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x02, 0x00, 0x06, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x00, 0x04, 0x63, 0x6f, 0x64, 0x65, 0x02, 0x00, 0x1d, 0x4e, 0x65, 0x74, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x2e, 0x53, 0x75, 0x63, 0x63, 0x65, 0x73, 0x73, 0x00, 0x0b, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x02, 0x00, 0x14, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x73, 0x75, 0x63, 0x63, 0x65, 0x65, 0x64, 0x65, 0x64, 0x00, 0x0e, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x45, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			Assert::AreEqual<uint32>( 4, ary->Size );
			Assert::AreEqual( L"_result", ary->GetStringAt( 0 ) );
			Assert::AreEqual( 1.0, ary->GetDoubleAt( 1 ) );

			const auto& objLapped = ary->GetAt( 2 );
			Assert::IsTrue( objLapped->ValueType == AmfValueType::Object );

			const auto& obj = objLapped->GetObject();
			Assert::AreEqual( L"FMS/3,0,1,123", obj->GetNamedString( "fmsVer" ) );
			Assert::AreEqual( 31.0, obj->GetNamedDouble( "capabilities" ) );

			const auto& objLapped2 = ary->GetAt( 3 );
			Assert::IsTrue( objLapped2->ValueType == AmfValueType::Object );

			const auto& obj2 = objLapped2->GetObject();
			Assert::AreEqual( L"status", obj2->GetNamedString( "level" ) );

			Assert::AreEqual( L"NetConnection.Connect.Success", obj2->GetNamedString( "code" ) );
			Assert::AreEqual( L"Connection succeeded", obj2->GetNamedString( "description" ) );
			Assert::AreEqual( 0.0, obj2->GetNamedDouble( "objectEncoding" ) );
		} );
	}

private:
	void Test( U8Array^ expected, std::function<void( IAmfValue^ )> checkHandler )
	{
		const auto& amf = ParserTest( expected, checkHandler );
		const auto& createData = SequencerTest( amf );
		AssertHelper::AreArrayEqual( expected, createData );
	}

	IAmfValue^ ParserTest( U8Array^ expected, std::function<void( IAmfValue^ )> checkHandler )
	{
		const auto& amf = Amf0Parser::Parse( expected );
		const auto& str = amf->ToString();
		Logger::WriteMessage( str->Data() );
		Logger::WriteMessage( L"\n" );
		checkHandler( amf );
		return amf;
	}

	U8Array^ SequencerTest( IAmfValue^ val )
	{
		return Amf0Sequencer::Sequencify( val );
	}

	void ParserFailureExceptionTest( U8Array^ ary )
	{
		Assert::ExpectException<Platform::FailureException^>( [=]
		{
			ParserTest( ary, []( IAmfValue^ ) { } );
		} );
	}

	void SequencerFailureExceptionTest( IAmfValue^ val )
	{
		Assert::ExpectException<Platform::FailureException^>( [=]
		{
			SequencerTest( val );
		} );
	}
};