#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;

TEST_CLASS( Amf3UnitTest )
{
public:
	TEST_METHOD( Amf3_⓪UndefinedTest )
	{
		Test( ref new U8Array{ 0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Undefined );
		} );
	}

	TEST_METHOD( Amf3_①NullTest )
	{
		Test( ref new U8Array{ 1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Null );
		} );
	}

	TEST_METHOD( Amf3_②BooleanFalseTest )
	{
		Test( ref new U8Array{ 2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Boolean );
			Assert::IsFalse( val->GetBoolean() );
		} );
	}

	TEST_METHOD( Amf3_③BooleanTrueTest )
	{
		Test( ref new U8Array{ 3 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Boolean );
			Assert::IsTrue( val->GetBoolean() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐0_0 )
	{
		Test( ref new U8Array{ 4, 0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			Assert::AreEqual( 0.0, val->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐1_1 )
	{
		Test( ref new U8Array{ 4, 1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			Assert::AreEqual( 1.0, val->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐2_127 )
	{
		Test( ref new U8Array{ 4, 0x7f }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			Assert::AreEqual( 127.0, val->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐3_128 )
	{
		Test( ref new U8Array{ 4, 0x81, 0x00 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			Assert::AreEqual( 128.0, val->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐4_16383 )
	{
		Test( ref new U8Array{ 4, 0xff, 0x7f }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			Assert::AreEqual( 16383.0, val->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐5_16384 )
	{
		Test( ref new U8Array{ 4, 0x81, 0x80, 0x00 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			Assert::AreEqual( 16384.0, val->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐6_2097151 )
	{
		Test( ref new U8Array{ 4, 0xff, 0xff, 0x7f }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			Assert::AreEqual( 2097151.0, val->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐7_2097152 )
	{
		Test( ref new U8Array{ 4, 0x80, 0xc0, 0x80, 0x00 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			Assert::AreEqual( 2097152.0, val->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐8_268435455 )
	{
		Test( ref new U8Array{ 4, 0xbf, 0xff, 0xff, 0xff }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			Assert::AreEqual( 268435455.0, val->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐9_－1 )
	{
		Test( ref new U8Array{ 4, 0xff, 0xff, 0xff, 0xff }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			auto n = val->GetNumber();
			Assert::AreEqual( -1.0, n );
		} );
	}

	TEST_METHOD( Amf3_④IntegerTest‐a_－268435456 )
	{
		Test( ref new U8Array{ 4, 0xc0, 0x80, 0x80, 0x00 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			Assert::AreEqual( -268435456.0, val->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_⑤DoubleTest‐0_0．5 )
	{
		Test( ref new U8Array{ 5, 0x3f, 0xe0, 0, 0, 0, 0, 0, 0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			Assert::AreEqual( 0.5, val->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_⑤DoubleTest‐1_268435456．0 )
	{
		Test( ref new U8Array{ 5, 0x41, 0xb0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			Assert::AreEqual( 268435456.0, val->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_⑤DoubleTest‐2_2147483647．0 )
	{
		Test( ref new U8Array{ 5, 0x41, 0xdf, 0xff, 0xff, 0xff, 0xc0, 0x0, 0x0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			Assert::AreEqual( 2147483647.0, val->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_⑤DoubleTest‐3_－268435457．0 )
	{
		Test( ref new U8Array{ 5, 0xc1, 0xb0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			Assert::AreEqual( -268435457.0, val->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_⑤DoubleTest‐4_－2147483648．0 )
	{
		Test( ref new U8Array{ 5, 0xc1, 0xe0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Number );
			Assert::AreEqual( -2147483648.0, val->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_⑥StringTest‐0_Null )
	{
		Test( ref new U8Array{ 6, 1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::String );
			Assert::AreEqual( L"", val->GetString()->Data() );
		} );
	}

	TEST_METHOD( Amf3_⑥StringTest‐1_Ascii )
	{
		Test( ref new U8Array{ 6, 11, 0x41, 0x53, 0x43, 0x49, 0x49 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::String );
			Assert::AreEqual( L"ASCII", val->GetString() );
		} );
	}

	TEST_METHOD( Amf3_⑥StringTest‐2_RandomCharactors1 )
	{
		Test( ref new U8Array{ 6, 13, 0xc2, 0xbd, 0x3a, 0x20, 0x32, 0x42 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::String );
			Assert::AreEqual( L"½: 2B", val->GetString() );
		} );
	}

	TEST_METHOD( Amf3_⑥StringTest‐3_RandomCharactors2 )
	{
		Test( ref new U8Array{ 6, 15, 0xe2, 0x91, 0xb4, 0x3a, 0x20, 0x33, 0x42 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::String );
			Assert::AreEqual( L"⑴: 3B", val->GetString() );
		} );
	}

	TEST_METHOD( Amf3_⑥StringTest‐4_StringAndRef )
	{
		Test( ref new U8Array{ 0x9, 0x5, 0x1, 0x6, 0x7, 0x61, 0x62, 0x63, 0x6, 0x0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			Assert::AreEqual( 2u, ary->Size );
			Assert::AreEqual( L"abc", ary->GetStringAt( 0 ) );
			Assert::AreEqual( L"abc", ary->GetStringAt( 1 ) );
		} );
	}

	TEST_METHOD( Amf3_⑥StringTest‐5_String_InvalidReference )
	{
		ParserFailureExceptionTest( ref new U8Array{ 0x9, 0x5, 0x1, 0x6, 0x7, 0x61, 0x62, 0x63, 0x6, 0x2 } );
	}

	TEST_METHOD( Amf3_⑦XmlDocumentTest‐0_RootNode )
	{
		ParserTest( ref new U8Array{ 7, 13, 0x3c, 0x72, 0x6f, 0x6f, 0x74, 0x3e }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Xml );
			Assert::AreEqual( L"<root>", val->GetString() );
		} );
	}

	TEST_METHOD( Amf3_⑦XmlDocumentTest‐1_RootNodeAndRef )
	{
		ParserTest( ref new U8Array{ 9, 0x5, 0x1, 7, 13, 0x3c, 0x72, 0x6f, 0x6f, 0x74, 0x3e, 7, 0x2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			Assert::AreEqual( 2u, ary->Size );
			
			const auto& xml = ary->GetAt( 0 );
			Assert::IsTrue( xml->ValueType == AmfValueType::Xml );
			Assert::AreEqual( L"<root>", xml->GetString() );
			Assert::IsTrue( ary->GetAt( 1 ) == xml );
		} );
	}

	TEST_METHOD( Amf3_⑦XmlDocumentTest‐2_RootNode_InvalidReference )
	{
		ParserFailureExceptionTest( ref new U8Array{ 9, 0x5, 0x1, 7, 13, 0x3c, 0x72, 0x6f, 0x6f, 0x74, 0x3e, 7, 0x4 } );
	}

	TEST_METHOD( Amf3_⑧DateTest‐0_2013／10／13 )
	{
		Test( ref new U8Array{ 8, 1, 0x42, 0x74, 0x1a, 0xd2, 0xe6, 0x18, 0x00, 0x00 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Date );

			const auto& exp = AssertHelper::GetDate( 2013, 10, 13 );
			Assert::IsTrue( exp.UniversalTime == val->GetDate().UniversalTime );
		} );
	}

	TEST_METHOD( Amf3_⑧DateTest‐1_2013／11／02_20：28：52．0100 )
	{
		Test( ref new U8Array{ 8, 1, 0x42, 0x74, 0x21, 0x89, 0x2a, 0x18, 0x40, 0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Date );

			const auto& exp = AssertHelper::GetDate( 2013, 11, 2, 20, 28, 52, 100 * 1000000 );
			Assert::IsTrue( exp.UniversalTime == val->GetDate().UniversalTime );
		} );
	}

	TEST_METHOD( Amf3_⑧DateTest‐2_2013／11／02_20：28：52．0100AndRef )
	{
		Test( ref new U8Array{ 9, 0x5, 0x1, 0x8, 0x1, 0x42, 0x74, 0x21, 0x89, 0x2a, 0x18, 0x40, 0x0, 0x8, 0x2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			Assert::AreEqual( 2u, ary->Size );

			const auto& exp = AssertHelper::GetDate( 2013, 11, 2, 20, 28, 52, 100 * 1000000 );
			Assert::IsTrue( exp.UniversalTime == ary->GetDateAt( 0 ).UniversalTime );
			Assert::IsTrue( exp.UniversalTime == ary->GetDateAt( 1 ).UniversalTime );
		} );
	}

	TEST_METHOD( Amf3_⑧DateTest‐2_2013／11／02_20：28：52．0100_InvalidReference )
	{
		ParserFailureExceptionTest( ref new U8Array{ 9, 0x5, 0x1, 0x8, 0x1, 0x42, 0x74, 0x21, 0x89, 0x2a, 0x18, 0x40, 0x0, 0x8, 0x4 } );
	}

	TEST_METHOD( Amf3_⑨ArrayTest‐0_NumKeyAndStrKey )
	{
		Test( ref new U8Array{ 9, 0x3, 0x7, 0x61, 0x62, 0x63, 0x4, 0x3, 0x1, 0x4, 0x2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::EcmaArray );

			const auto& obj = val->GetObject();
			const auto& num = obj->GetNamedNumber( "0" );
			Assert::AreEqual( 2.0, num );

			const auto& str = obj->GetNamedNumber( "abc" );
			Assert::AreEqual( 3.0, str );
		} );
	}

	TEST_METHOD( Amf3_⑨ArrayTest‐1_NumKeyOnly )
	{
		Test( ref new U8Array{ 9, 0x5, 0x1, 0x4, 0x2, 0x4, 0x3 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			const auto& num0 = ary->GetNumberAt( 0 );
			Assert::AreEqual( 2.0, num0 );

			const auto& num1 = ary->GetNumberAt( 1 );
			Assert::AreEqual( 3.0, num1 );
		} );
	}

	TEST_METHOD( Amf3_⑨ArrayTest‐2_StrKeyOnly )
	{
		Test( ref new U8Array{ 9, 0x1, 0x7, 0x61, 0x62, 0x63, 0x4, 0x2, 0x7, 0x78, 0x79, 0x7a, 0x4, 0x3, 0x1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::EcmaArray );

			const auto& obj = val->GetObject();
			const auto& strAbc = obj->GetNamedNumber( "abc" );
			Assert::AreEqual( 2.0, strAbc );

			const auto& strXyz = obj->GetNamedNumber( "xyz" );
			Assert::AreEqual( 3.0, strXyz );
		} );
	}

	TEST_METHOD( Amf3_⑨ArrayTest‐3_NumKeyAndSkippedNumKey )
	{
		Test( ref new U8Array{ 9, 0x5, 0x3, 0x33, 0x4, 0x4, 0x1, 0x4, 0x2, 0x4, 0x3 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::EcmaArray );

			const auto& obj = val->GetObject();
			const auto& str0 = obj->GetNamedNumber( "0" );
			Assert::AreEqual( 2.0, str0 );

			const auto& str1 = obj->GetNamedNumber( "1" );
			Assert::AreEqual( 3.0, str1 );

			const auto& str3 = obj->GetNamedNumber( "3" );
			Assert::AreEqual( 4.0, str3 );
		} );
	}

	TEST_METHOD( Amf3_⑨ArrayTest‐4_HasOneRefStrValue )
	{
		Test( ref new U8Array{ 9, 0x1, 0x7, 0x61, 0x62, 0x63, 0x6, 0x0, 0x7, 0x78, 0x79, 0x7a, 0x4, 0x3, 0x1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::EcmaArray );

			const auto& obj = val->GetObject();
			const auto& strAbc = obj->GetNamedString( "abc" );
			Assert::AreEqual( L"abc", strAbc );

			const auto& strXyz = obj->GetNamedNumber( "xyz" );
			Assert::AreEqual( 3.0, strXyz );
		} );
	}

	TEST_METHOD( Amf3_⑨ArrayTest‐5_HasSomeRefStrValue )
	{
		Test( ref new U8Array{ 9, 0x7, 0x7, 0x78, 0x79, 0x7a, 0x6, 0x9, 0x70, 0x71, 0x72, 0x73, 0x1, 0x6, 0x7, 0x61, 0x62, 0x63, 0x6, 0x0, 0x6, 0x2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::EcmaArray );

			const auto& obj = val->GetObject();
			const auto& str0 = obj->GetNamedString( "0" );
			Assert::AreEqual( L"abc", str0 );

			const auto& str1 = obj->GetNamedString( "1" );
			Assert::AreEqual( L"xyz", str1 );

			const auto& str2 = obj->GetNamedString( "2" );
			Assert::AreEqual( L"pqrs", str2 );

			const auto& strXyz = obj->GetNamedString( "xyz" );
			Assert::AreEqual( L"pqrs", strXyz );
		} );
	}

	TEST_METHOD( Amf3_⑨ArrayTest‐6_StringNullKeyExceptionTest )
	{
		Assert::ExpectException<Platform::InvalidArgumentException^>( [=]
		{
			const auto& ary = AmfObject::CreateEcmaArray();
			ary->Insert( "", AmfValue::CreateBooleanValue( true ) );
			SequencerTest( ary );
		} );
	}

	TEST_METHOD( Amf3_⑩ObjectTest‐0_Default )
	{
		Test( ref new U8Array{ 10, 0xb, 0x1, 0x3, 0x61, 0x4, 0x2, 0x3, 0x62, 0x4, 0x3, 0x1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Object );

			const auto& obj = val->GetObject();
			const auto& a = obj->GetNamedNumber( "a" );
			Assert::AreEqual( 2.0, a );

			const auto& b = obj->GetNamedNumber( "b" );
			Assert::AreEqual( 3.0, b );
		} );
	}

	TEST_METHOD( Amf3_⑪XmlTest‐0_RootNode )
	{
		Test( ref new U8Array{ 11, 13, 0x3c, 0x72, 0x6f, 0x6f, 0x74, 0x3e }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Xml );
			Assert::AreEqual( L"<root>", val->GetString()->Data() );
		} );
	}

	TEST_METHOD( Amf3_⑪XmlTest‐1_RootNodeAndRef )
	{
		Test( ref new U8Array{ 9, 0x5, 0x1, 11, 13, 0x3c, 0x72, 0x6f, 0x6f, 0x74, 0x3e, 0xb, 0x2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			Assert::AreEqual( 2u, ary->Size );

			const auto& xml = ary->GetAt( 0 );
			Assert::IsTrue( xml->ValueType == AmfValueType::Xml );
			Assert::AreEqual( L"<root>", xml->GetString() );
			Assert::IsTrue( ary->GetAt( 1 ) == xml );
		} );
	}

	TEST_METHOD( Amf3_⑪XmlTest‐2_RootNode_InvalidReference )
	{
		ParserFailureExceptionTest( ref new U8Array{ 9, 0x5, 0x1, 11, 13, 0x3c, 0x72, 0x6f, 0x6f, 0x74, 0x3e, 0xb, 0x4 } );
	}

	TEST_METHOD( Amf3_⑫ByteArrayTest‐0_234 )
	{
		Test( ref new U8Array{ 12, 0x7, 0x2, 0x3, 0x4 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::ByteArray );

			const auto& ba = val->GetByteArray();
			AssertHelper::AreArrayEqual( ref new U8Array{ 2, 3, 4 }, ba );
		} );
	}

	TEST_METHOD( Amf3_⑫ByteArrayTest‐1_234AndRef )
	{
		Test( ref new U8Array{ 9, 0x5, 0x1, 12, 0x7, 0x2, 0x3, 0x4, 0xc, 0x2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			Assert::AreEqual( 2u, ary->Size );

			const auto& ba = ary->GetAt( 0 );
			Assert::IsTrue( ba->ValueType == AmfValueType::ByteArray );
			AssertHelper::AreArrayEqual( ref new U8Array{ 2, 3, 4 }, ba->GetByteArray() );
			Assert::IsTrue( ary->GetAt( 1 ) == ba );
		} );
	}

	TEST_METHOD( Amf3_⑫ByteArrayTest‐2_234_InvalidReference )
	{
		ParserFailureExceptionTest( ref new U8Array{ 9, 0x5, 0x1, 12, 0x7, 0x2, 0x3, 0x4, 0xc, 0x4 } );
	}

	TEST_METHOD( Amf3_⑬VectorIntTest‐0_2／3 )
	{
		Test( ref new U8Array{ 13, 0x5, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x3 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::VectorInt );

			const auto& vi = val->GetVectorInt();
			Assert::AreEqual( 2u, vi->Size );
			Assert::AreEqual( 2, vi->GetAt( 0 ) );
			Assert::AreEqual( 3, vi->GetAt( 1 ) );
		} );
	}

	TEST_METHOD( Amf3_⑬VectorIntTest‐1_2／3AndRef )
	{
		Test( ref new U8Array{ 9, 0x5, 0x1, 13, 0x5, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x3, 0xd, 0x2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			Assert::AreEqual( 2u, ary->Size );

			const auto& ivi = ary->GetAt( 0 );
			Assert::IsTrue( ivi->ValueType == AmfValueType::VectorInt );

			const auto& vi = ivi->GetVectorInt();
			Assert::AreEqual( 2u, vi->Size );
			Assert::AreEqual( 2, vi->GetAt( 0 ) );
			Assert::AreEqual( 3, vi->GetAt( 1 ) );
			Assert::IsTrue( ary->GetAt( 1 ) == ivi );
		} );
	}

	TEST_METHOD( Amf3_⑬VectorIntTest‐2_2／3_InvalidReference )
	{
		ParserFailureExceptionTest( ref new U8Array{ 9, 0x5, 0x1, 13, 0x5, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x3, 0xd, 0x4 } );
	}

	TEST_METHOD( Amf3_⑭VectorUintTest‐0_2／3 )
	{
		Test( ref new U8Array{ 14, 0x5, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x3 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::VectorUint );

			const auto& vu = val->GetVectorUint();
			Assert::AreEqual( 2u, vu->Size );
			Assert::AreEqual( 2u, vu->GetAt( 0 ) );
			Assert::AreEqual( 3u, vu->GetAt( 1 ) );
		} );
	}

	TEST_METHOD( Amf3_⑬VectorUintTest‐1_2／3AndRef )
	{
		Test( ref new U8Array{ 9, 0x5, 0x1, 14, 0x5, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x3, 0xe, 0x2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			Assert::AreEqual( 2u, ary->Size );

			const auto& ivu = ary->GetAt( 0 );
			Assert::IsTrue( ivu->ValueType == AmfValueType::VectorUint );

			const auto& vu = ivu->GetVectorUint();
			Assert::AreEqual( 2u, vu->Size );
			Assert::AreEqual( 2u, vu->GetAt( 0 ) );
			Assert::AreEqual( 3u, vu->GetAt( 1 ) );
			Assert::IsTrue( ary->GetAt( 1 ) == ivu );
		} );
	}

	TEST_METHOD( Amf3_⑬VectorUintTest‐2_2／3_InvalidReference )
	{
		ParserFailureExceptionTest( ref new U8Array{ 9, 0x5, 0x1, 14, 0x5, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x3, 0xe, 0x4 } );
	}

	TEST_METHOD( Amf3_⑮VectorDoubleTest‐0_2．0／3．0 )
	{
		Test( ref new U8Array{ 15, 0x5, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::VectorDouble );

			const auto& vd = val->GetVectorDouble();
			Assert::AreEqual( 2u, vd->Size );
			Assert::AreEqual( 2.0, vd->GetAt( 0 ) );
			Assert::AreEqual( 3.0, vd->GetAt( 1 ) );
		} );
	}

	TEST_METHOD( Amf3_⑬VectorDoubleTest‐1_2．0／3．0AndRef )
	{
		Test( ref new U8Array{ 9, 0x5, 0x1, 15, 0x5, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			Assert::AreEqual( 2u, ary->Size );

			const auto& ivd = ary->GetAt( 0 );
			Assert::IsTrue( ivd->ValueType == AmfValueType::VectorDouble );

			const auto& vd = ivd->GetVectorDouble();
			Assert::AreEqual( 2u, vd->Size );
			Assert::AreEqual( 2.0, vd->GetAt( 0 ) );
			Assert::AreEqual( 3.0, vd->GetAt( 1 ) );
			Assert::IsTrue( ary->GetAt( 1 ) == ivd );
		} );
	}

	TEST_METHOD( Amf3_⑬VectorDoubleTest‐2_2．0／3．0_InvalidReference )
	{
		ParserFailureExceptionTest( ref new U8Array{ 9, 0x5, 0x1, 15, 0x5, 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x4 } );
	}

	TEST_METHOD( Amf3_⑯VectorObjectTest‐0_abcAnd1 )
	{
		Test( ref new U8Array{ 16, 0x5, 0x0, 0x1, 0x6, 0x7, 0x61, 0x62, 0x63, 0x4, 0x1 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::VectorObject );

			const auto& vo = val->GetVectorObject();
			Assert::AreEqual( 2u, vo->Size );

			const auto& string = vo->GetAt( 0 );
			Assert::IsTrue( string->ValueType == AmfValueType::String );
			Assert::AreEqual( L"abc", string->GetString() );

			const auto& integer = vo->GetAt( 1 );
			Assert::IsTrue( integer->ValueType == AmfValueType::Number );
			Assert::AreEqual( 1.0, integer->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_⑯VectorObjectTest‐1_abcAnd1AndRef )
	{
		Test( ref new U8Array{ 9, 0x5, 0x1, 16, 0x5, 0x0, 0x1, 0x6, 0x7, 0x61, 0x62, 0x63, 0x4, 0x1, 0x10, 0x2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			Assert::AreEqual( 2u, ary->Size );

			const auto& ivo = ary->GetAt( 0 );
			Assert::IsTrue( ivo->ValueType == AmfValueType::VectorObject );

			const auto& vo = ivo->GetVectorObject();
			Assert::AreEqual( 2u, vo->Size );

			const auto& string = vo->GetAt( 0 );
			Assert::IsTrue( string->ValueType == AmfValueType::String );
			Assert::AreEqual( L"abc", string->GetString() );

			const auto& integer = vo->GetAt( 1 );
			Assert::IsTrue( integer->ValueType == AmfValueType::Number );
			Assert::AreEqual( 1.0, integer->GetNumber() );
			Assert::IsTrue( ary->GetAt( 1 ) == ivo );
		} );
	}

	TEST_METHOD( Amf3_⑯VectorObjectTest‐2_abcAnd1_InvalidReference )
	{
		ParserFailureExceptionTest( ref new U8Array{ 9, 0x5, 0x1, 16, 0x5, 0x0, 0x1, 0x6, 0x7, 0x61, 0x62, 0x63, 0x4, 0x1, 0x10, 0x4 } );
	}

	TEST_METHOD( Amf3_⑰DictionaryTest‐0_Null )
	{
		Test( ref new U8Array{ 0x11, 0x1, 0x0 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Dictionary );

			const auto& dic = val->GetDictionary();
			Assert::AreEqual( 0u, dic->Size );
		} );
	}

	TEST_METHOD( Amf3_⑰DictionaryTest‐1_test )
	{
		Test( ref new U8Array{ 0x11, 0x7, 0x0, 0xa, 0xb, 0x1, 0x3, 0x62, 0x4, 0x3, 0x3, 0x61, 0x4, 0x2, 0x1, 0x4, 0x3, 0xa, 0x1, 0x3, 0x79, 0x4, 0x5, 0x3, 0x78, 0x4, 0x4, 0x1, 0x4, 0x4, 0x6, 0x2, 0x4, 0x2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Dictionary );

			const auto& dic = val->GetDictionary();
			Assert::AreEqual( 3u, dic->Size );

			const auto& first = dic->GetAt( 0 );
			Assert::IsTrue( first->KeyType == AmfValueType::Object );
			const auto& firstKey = first->Key->GetObject();
			Assert::AreEqual( 2.0, firstKey->GetNamedNumber( "a" ) );
			Assert::AreEqual( 3.0, firstKey->GetNamedNumber( "b" ) );
			Assert::IsTrue( first->ValueType == AmfValueType::Number );
			Assert::AreEqual( 3.0, first->Value->GetNumber() );

			const auto& second = dic->GetAt( 1 );
			Assert::IsTrue( second->KeyType == AmfValueType::Object );
			const auto& secondKey = second->Key->GetObject();
			Assert::AreEqual( 4.0, secondKey->GetNamedNumber( "x" ) );
			Assert::AreEqual( 5.0, secondKey->GetNamedNumber( "y" ) );
			Assert::IsTrue( second->ValueType == AmfValueType::Number );
			Assert::AreEqual( 4.0, second->Value->GetNumber() );

			const auto& third = dic->GetAt( 2 );
			Assert::IsTrue( third->KeyType == AmfValueType::String );
			Assert::AreEqual( L"a", third->Key->GetString() );
			Assert::IsTrue( third->ValueType == AmfValueType::Number );
			Assert::AreEqual( 2.0, third->Value->GetNumber() );
		} );
	}

	TEST_METHOD( Amf3_⑰DictionaryTest‐2_NullAndRef )
	{
		Test( ref new U8Array{ 9, 0x5, 0x1, 0x11, 0x1, 0x0, 0x11, 0x2 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			Assert::AreEqual( 2u, ary->Size );

			const auto& dic = ary->GetDictionaryAt( 0 );
			Assert::AreEqual( 0u, dic->Size );

			Assert::IsTrue( ary->GetAt( 1 ) == dic );
		} );
	}

	TEST_METHOD( Amf3_⑰DictionaryTest‐3_Null_InvalidReference )
	{
		ParserFailureExceptionTest( ref new U8Array{ 9, 0x5, 0x1, 0x11, 0x1, 0x0, 0x11, 0x4 } );
	}

	TEST_METHOD( Amf3_⑱UnknownTypeTest‐0 )
	{
		ParserFailureExceptionTest( ref new U8Array{ 16 } );
	}

	TEST_METHOD( Amf3_ⓍMasterTest_0‐RtmpCommandData )
	{
		ParserTest( ref new U8Array{ 0x9, 0x9, 0x1, 0x6, 0xf, 0x5f, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x4, 0x1, 0xa, 0xb, 0x1, 0x19, 0x63, 0x61, 0x70, 0x61, 0x62, 0x69, 0x6c, 0x69, 0x74, 0x69, 0x65, 0x73, 0x4, 0x1f, 0xd, 0x66, 0x6d, 0x73, 0x56, 0x65, 0x72, 0x6, 0x1b, 0x46, 0x4d, 0x53, 0x2f, 0x33, 0x2c, 0x30, 0x2c, 0x31, 0x2c, 0x31, 0x32, 0x33, 0x1, 0xa, 0x1, 0x17, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x6, 0x29, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x73, 0x75, 0x63, 0x63, 0x65, 0x65, 0x64, 0x65, 0x64, 0x1d, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x45, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67, 0x4, 0x0, 0x9, 0x63, 0x6f, 0x64, 0x65, 0x6, 0x3b, 0x4e, 0x65, 0x74, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x2e, 0x53, 0x75, 0x63, 0x63, 0x65, 0x73, 0x73, 0xb, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x6, 0xd, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x1 }, [=]( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			Assert::AreEqual( 4u, ary->Size );
			Assert::AreEqual( L"_result", ary->GetStringAt( 0 )->Data() );
			Assert::AreEqual( 1.0, ary->GetNumberAt( 1 ) );

			const auto& objLapped = ary->GetAt( 2 );
			Assert::IsTrue( objLapped->ValueType == AmfValueType::Object );

			const auto& obj = objLapped->GetObject();
			Assert::AreEqual( L"FMS/3,0,1,123", obj->GetNamedString( "fmsVer" )->Data() );
			Assert::AreEqual( 31.0, obj->GetNamedNumber( "capabilities" ) );

			const auto& objLapped2 = ary->GetAt( 3 );
			Assert::IsTrue( objLapped2->ValueType == AmfValueType::Object );

			const auto& obj2 = objLapped2->GetObject();
			Assert::AreEqual( L"status", obj2->GetNamedString( "level" )->Data() );
			Assert::AreEqual( L"NetConnection.Connect.Success", obj2->GetNamedString( "code" )->Data() );
			Assert::AreEqual( L"Connection succeeded", obj2->GetNamedString( "description" )->Data() );
			Assert::AreEqual( 0.0, obj2->GetNamedNumber( "objectEncoding" ) );

			SequencerTest( val );
		} );
	}

	TEST_METHOD( Amf3_ⓍMasterTest‐1_ReferenceTest )
	{
		Test( ref new U8Array{ 0x9, 0xb, 0x1, 0x9, 0xd, 0x1, 0xa, 0xb, 0x1, 0x3, 0x62, 0x3, 0x1, 0x6, 0x3, 0x74, 0xa, 0x1, 0x0, 0x2, 0x1, 0xa, 0x4, 0xa, 0x6, 0xa, 0x13, 0x3, 0x78, 0x4, 0x4, 0x17, 0xa, 0x6, 0xa, 0x4, 0x9, 0x2, 0xa, 0x8 }, []( IAmfValue^ val )
		{
			Assert::IsTrue( val->ValueType == AmfValueType::Array );

			const auto& ary = val->GetArray();
			Assert::AreEqual( 5u, ary->Size );

			const auto& first = ary->GetArrayAt( 0 );
			Assert::AreEqual( 6u, first->Size );

			const auto& objA = first->GetObjectAt( 0 );
			Assert::AreEqual( 1u, objA->Size );
			Assert::IsTrue( objA->GetNamedBoolean( "b" ) );

			const auto& str = first->GetStringAt( 1 );
			Assert::AreEqual( L"t", str );

			const auto& objB = first->GetObjectAt( 2 );
			Assert::AreEqual( 1u, objB->Size );
			Assert::IsFalse( objB->GetNamedBoolean( "b" ) );

			const auto& objARef1 = first->GetObjectAt( 3 );
			Assert::IsTrue( objARef1 == objA );

			const auto& objBRef1 = first->GetObjectAt( 4 );
			Assert::IsTrue( objBRef1 == objB );

			const auto& objC = first->GetObjectAt( 5 );
			Assert::AreEqual( 1u, objC->Size );
			Assert::AreEqual( L"x", objC->ClassName );
			Assert::AreEqual( 23.0, objC->GetNamedNumber( "x" ) );

			const auto& objBRef2 = ary->GetObjectAt( 1 );
			Assert::IsTrue( objBRef2 == objB );

			const auto& objARef2 = ary->GetObjectAt( 2 );
			Assert::IsTrue( objARef2 == objA );

			const auto& firstRef1 = ary->GetArrayAt( 3 );
			Assert::IsTrue( firstRef1 == first );

			const auto& objCRef1 = ary->GetObjectAt( 4 );
			Assert::IsTrue( objCRef1 == objC );
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
		const auto& amf = amf3_parser::parse( expected );
		const auto& str = amf->ToString();
		Logger::WriteMessage( str->Data() );
		Logger::WriteMessage( L"\n" );
		checkHandler( amf );
		return amf;
	}

	U8Array^ SequencerTest( IAmfValue^ val )
	{
		return amf3_sequencer::sequencify( val );
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