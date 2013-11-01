#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Mntone::Data::Amf;
using namespace Windows::Globalization;


typedef Platform::Array<uint8> testByteArray;


namespace Mntone_Data_Amf_UnitTest
{
    TEST_CLASS(Amf0UnitTest)
    {
    
	public:


		TEST_METHOD(NumberTest_0_0){
			testAmf0(ref new testByteArray{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, [](IAmfValue^ amfValue)
			{
				Assert::AreEqual(amfValue->GetDouble(), 0.0);
			});
		}

		TEST_METHOD(NumbetTest_0_5){
			testAmf0(ref new testByteArray{ 0, 0x3f, 0xe0, 0, 0, 0, 0, 0, 0 }, [](IAmfValue^ amfValue){
				Assert::AreEqual(amfValue->GetDouble(), 0.5);
			});
		}

		TEST_METHOD(BooleanTest_True){
			testAmf0(ref new testByteArray{ 1, 1 }, [](IAmfValue^ amfValue){
				Assert::IsTrue(amfValue->GetBoolean());
			});
		}

		TEST_METHOD(BooleanTest_False){
			testAmf0(ref new testByteArray{ 1, 0 }, [](IAmfValue^ amfValue){
				Assert::IsFalse(amfValue->GetBoolean());
			});
		}

		TEST_METHOD(StringTest_Null){
			testAmf0(ref new testByteArray{ 2, 0, 0 }, [](IAmfValue^ amfValue){
				Assert::IsNull(reinterpret_cast<void*>( amfValue->GetString()));
			});

			
		}

		TEST_METHOD(Stringtest_Ascii){
			testAmf0(ref new testByteArray{ 2, 0, 5, 0x41, 0x53, 0x43, 0x49, 0x49 }, [](IAmfValue^ amfValue){
				Assert::AreEqual(amfValue->GetString(),ref new Platform::String( L"ASCII"));
			});
		}


		TEST_METHOD(StringTest_RandomCharactors1){
			testAmf0(ref new testByteArray{ 2, 0, 6, 0xc2, 0xbd, 0x3a, 0x20, 0x32, 0x42 }, [](IAmfValue^ amfValue){
				Assert::AreEqual(amfValue->GetString(), ref new Platform::String(L"½: 2B"));
			});

		}

		TEST_METHOD(StringTest_RandomCharactors2){
			testAmf0(ref new testByteArray{ 2, 0, 7, 0xe2, 0x91, 0xb4, 0x3a, 0x20, 0x33, 0x42 }, [](IAmfValue^ amfValue){
				Assert::AreEqual(amfValue->GetString(), ref new Platform::String(L"⑴: 3B"));
			});
		
		}

		TEST_METHOD(ObjectTest_Null){
			testAmf0(ref new testByteArray{ 3, 0, 0, 9 }, [](IAmfValue^ amfValue){
				Assert::IsTrue(amfValue->ValueType  == AmfValueType::Object);
			});
		}

		TEST_METHOD(ObjectTest_BStringNull){
			testAmf0(ref new testByteArray{ 3, 0, 1, 0x42, 2, 0, 0, 0, 0, 9 }, [](IAmfValue^ amfValue){
				Assert::IsNull(amfValue->GetObject()->GetNamedString("B"));
			});
		}

		TEST_METHOD(ValueTypeTest_Null){

			testAmf0(ref new testByteArray{ 5 }, [](IAmfValue^ amfValue){
				Assert::IsTrue(amfValue->ValueType == AmfValueType::Null);
			});

		}

		TEST_METHOD(ValueTypeTest_Undefined){

			testAmf0(ref new testByteArray{ 6 }, [](IAmfValue^ amfValue){
				Assert::IsTrue(amfValue->ValueType == AmfValueType::Undefined);
			});

		}

		TEST_METHOD(ReferenceTest_0){
			testAmf0(ref new testByteArray{ 7, 0, 0 }, [](IAmfValue^ amfValue){
				Assert::AreEqual<int>(amfValue->GetReference() ,(0));
			});
		}
		

		TEST_METHOD(ReferenceTest_4369){

			testAmf0(ref new testByteArray{ 7, 0x11, 0x11 }, [](IAmfValue^ amfValue){
				Assert::AreEqual<int>(amfValue->GetReference(),(4369));
			});
		}

		TEST_METHOD(EcmaArrayTest_Null){

			testAmf0(ref new testByteArray{ 8, 0, 0, 0, 0, 0, 0, 9 }, [](IAmfValue^ amfValue){
				Assert::IsTrue(amfValue->ValueType == AmfValueType::EcmaArray);	

			});
		}

		TEST_METHOD(EcmaArrayTest_String_Null){

			testAmf0(ref new testByteArray{ 8, 0, 0, 0, 1, 0, 1, 0x42, 2, 0, 0, 0, 0, 9 }, [](IAmfValue^ amfValue){

				Assert::IsNull(amfValue->GetObject()->GetNamedString("B"));
				Assert::IsTrue(amfValue->GetObject()->GetAssociativeCount() == static_cast<uint32>( 1));

			});
		}


		TEST_METHOD(StrictArrayTest_Null){
			testAmf0(ref new testByteArray{ 10, 0, 0, 0, 0 }, [](IAmfValue^ amfValue){
				Assert::IsTrue(amfValue->ValueType == AmfValueType::Array);
			});
		}

		TEST_METHOD(StrinctArray_0_True){
			testAmf0(ref new testByteArray{ 10, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 }, [](IAmfValue^ amfValue){
				Assert::AreEqual(amfValue->GetArray()->GetAt(0)->GetDouble(), 0, 0);
				Assert::IsTrue(amfValue->GetArray()->GetAt(1)->GetBoolean());
			});
		}

		TEST_METHOD(DateTest_2013_10_13){

			testAmf0(ref new testByteArray{ 11, 0x42, 0x74, 0x1a, 0xd2, 0xe6, 0x18, 0x00, 0x00, 0, 0 }, [](IAmfValue^ amfValue){
				auto targetDate = amfValue->GetDate();
				auto dateFormat = ref new DateTimeFormatting::DateTimeFormatter(DateTimeFormatting::YearFormat::Full, DateTimeFormatting::MonthFormat::Numeric, DateTimeFormatting::DayFormat::Default,DateTimeFormatting::DayOfWeekFormat::None);
				auto dateStr = dateFormat->Format(targetDate);

				Assert::AreEqual(dateStr, safe_cast<Platform::String^>(L"‎2013‎年‎10‎月‎13‎日"));


			});
		}

		TEST_METHOD(LongStringTest){
			auto ls = ref new testByteArray(5 + 0x10000);
			ls[0] = 12; ls[1] = 0; ls[2] = 1; ls[3] = 0; ls[4] = 0;
			auto testLs = ref new Platform::String();
			for (auto i = 0; i < 0x4000; ++i)
			{
				ls[5 + 4 * i] = 0x71; ls[5 + 4 * i + 1] = 0x72; ls[5 + 4 * i + 2] = 0x73; ls[5 + 4 * i + 3] = 0x74;
				testLs += L"qrst";
			}

			testAmf0(ls, [testLs](IAmfValue^ amfValue){
				Assert::AreEqual(amfValue->GetString(), testLs);
			});
		}

		TEST_METHOD(XmlDocumentTest_RootNode){
			testAmf0(ref new testByteArray{ 0x0f, 0, 0, 0, 6, 0x3c, 0x72, 0x6f, 0x6f, 0x74, 0x3e }, [](IAmfValue^ amfValue){
				Assert::AreEqual(amfValue->GetString(), safe_cast<Platform::String^>(L"<root>"));
			});
		}

		TEST_METHOD(TypedObjectTest_Null){

			testAmf0(ref new testByteArray{ 0x10, 0, 4, 0x54, 0x65, 0x73, 0x74, 0, 0, 9 }, [](IAmfValue^ amfValue){
				Assert::IsTrue(amfValue->ValueType == AmfValueType::TypedObject);
			});
		}

		


		TEST_METHOD(FromValueParseTest_Double0){
			parseTest_Double0(valueParse);
		}

		TEST_METHOD(FromValueParseTest_ObjectNull){
			parseTest_ObjectNull(valueParse);
		}

		TEST_METHOD(FromValueParseTest_ArrayNull){
			parseTest_ArrayNull(valueParse);
		}

		TEST_METHOD(FromObjectParseTest_Double0){
			parseTest_Double0(objectParse);
		}

		TEST_METHOD(FromObjectParseTest_ObjectNull){
			parseTest_ObjectNull(objectParse);
		}

		TEST_METHOD(FromObjectParseTest_ArrayNull){
			parseTest_ArrayNull(objectParse);
		}

		TEST_METHOD(FromArrayParseTest_Double0){
			parseTest_Double0(arrayParse);
		}

		TEST_METHOD(FromArrayParseTest_ObjectNull){
			parseTest_ObjectNull(arrayParse);
		}

		TEST_METHOD(FromArrayParseTest_ArrayNull){
			parseTest_ArrayNull(arrayParse);
		}


		TEST_METHOD(FromValueTryParseTest_Double0){
			parseTest_Double0(valueTryParse);
		}

		TEST_METHOD(FromValueTryParseTest_ObjectNull){
			parseTest_ObjectNull(valueTryParse);
		}

		TEST_METHOD(FromValueTryParseTest_ArrayNull){
			parseTest_ArrayNull(valueTryParse);
		}


		TEST_METHOD(FromObjectTryParseTest_Double0){
			parseTest_Double0(objectTryParse);
		}

		TEST_METHOD(FromObjectTryParseTest_ObjectNull){
			parseTest_ObjectNull(objectTryParse);
		}

		TEST_METHOD(FromObjectTryParseTest_ArrayNull){
			parseTest_ArrayNull(objectTryParse);
		}

		TEST_METHOD(FromArrayTryParseTest_Double0){
			parseTest_Double0(arrayTryParse);
		}

		TEST_METHOD(FromArrayTryParseTest_ObjectNull){
			parseTest_ObjectNull(arrayTryParse);
		}

		TEST_METHOD(FromArrayTryParseTest_ArrayNull){
			parseTest_ArrayNull(arrayTryParse);
		}


		TEST_METHOD(MasterTest_RtmpCommandData){

			testAmf0(ref new testByteArray{ 10, 0, 0, 0, 4, 0x02, 0x00, 0x07, 0x5f, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x06, 0x66, 0x6d, 0x73, 0x56, 0x65, 0x72, 0x02, 0x00, 0x0d, 0x46, 0x4d, 0x53, 0x2f, 0x33, 0x2c, 0x30, 0x2c, 0x31, 0x2c, 0x31, 0x32, 0x33, 0x00, 0x0c, 0x63, 0x61, 0x70, 0x61, 0x62, 0x69, 0x6c, 0x69, 0x74, 0x69, 0x65, 0x73, 0x00, 0x40, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x03, 0x00, 0x05, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x02, 0x00, 0x06, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x00, 0x04, 0x63, 0x6f, 0x64, 0x65, 0x02, 0x00, 0x1d, 0x4e, 0x65, 0x74, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x2e, 0x53, 0x75, 0x63, 0x63, 0x65, 0x73, 0x73, 0x00, 0x0b, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x02, 0x00, 0x14, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x73, 0x75, 0x63, 0x63, 0x65, 0x65, 0x64, 0x65, 0x64, 0x00, 0x0e, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x45, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09 }, [](IAmfValue^ amfValue){
				Assert::IsTrue(amfValue->ValueType == AmfValueType::Array);
			});
		}
		

	private:

		static void parseTest_Double0(std::function<IAmfValue ^ (testByteArray^)> parseFunc){
			Assert::AreEqual(parseFunc(ref new testByteArray{ 0, 0, 0, 0, 0, 0, 0, 0, 0 })->GetDouble(), 0.0);
		}

		static void parseTest_ObjectNull(std::function<IAmfValue ^ (testByteArray^)> parseFunc){
			Assert::AreEqual<int>(parseFunc(ref new testByteArray{ 3, 0, 0, 9 })->GetObject()->Size, 0);
		}

		static void parseTest_ArrayNull(std::function<IAmfValue ^ (testByteArray^)> parseFunc){
			Assert::AreEqual<int>(parseFunc(ref new testByteArray{ 10, 0, 0, 0, 0 })->GetArray()->Size, 0);
		}

		static AmfValue^ valueParse(testByteArray^ byteArray){

			return AmfValue::Parse(byteArray, Mntone::Data::Amf::AmfEncodingType::Amf0);
		}

		static AmfValue^ valueTryParse(testByteArray^ byteArray){
			AmfValue^ outValue;
			AmfValue::TryParse(byteArray, Mntone::Data::Amf::AmfEncodingType::Amf0, &outValue);
			return outValue;
		}

		static AmfObject^ objectParse(testByteArray^ byteArray){
			return AmfObject::Parse(byteArray, AmfEncodingType::Amf0);
		}

		static AmfObject^ objectTryParse(testByteArray^ byteArray){
			AmfObject^ outObject;
			AmfObject::TryParse(byteArray, Mntone::Data::Amf::AmfEncodingType::Amf0, &outObject);
			return outObject;
		}

		static AmfArray^ arrayParse(testByteArray^ byteArray){
			return AmfArray::Parse(byteArray, AmfEncodingType::Amf0);
		}

		static AmfArray^ arrayTryParse(testByteArray^ byteArray){
			AmfArray^ outArray;
			AmfArray::TryParse(byteArray, Mntone::Data::Amf::AmfEncodingType::Amf0, &outArray);
			return outArray;
		}


		static void testAmf0(testByteArray^ rawData, std::function<void(IAmfValue^)> checkHandler){
			
			auto r = Amf0Parser::Parse(rawData);
			auto st = r->ToString();
			checkHandler(r);
			auto createData = Amf0Sequencer::Sequenceify(r);

			Assert::IsTrue(arrayEquals(rawData, createData));


		}

		static bool arrayEquals(Platform::Array<uint8>^ firstArray, Platform::Array<uint8>^ secondArray){
			if (firstArray->Length != secondArray->Length)
				return false;
			for (uint32 i = 0; i < firstArray->Length; i++)
			{
				if (!firstArray[i].Equals(secondArray[i]))
				{
					return false;
				}
			}
			return true;
		}

	
    };
}