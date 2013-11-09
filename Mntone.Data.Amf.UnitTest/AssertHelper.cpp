#include <pch.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void AssertHelper::AreArrayEqual( const Platform::Array<uint8>^ expected, const Platform::Array<uint8>^ actual )
{
	const auto& length = expected->Length;
	Assert::AreEqual( length, actual->Length );

	std::wstringstream buf;
	for( auto i = 0u; i < length; ++i )
	{
		buf << '0' << 'x' << std::hex << actual[i] << ',' << ' ';
		if( !expected[i].Equals( actual[i] ) )
		{
			buf << '\n';
			Logger::WriteMessage( buf.str().c_str() );
			Assert::Fail();
			return;
		}
	}

	buf << '\n';
	Logger::WriteMessage( buf.str().c_str() );
}

Windows::Foundation::DateTime AssertHelper::GetDate( int32 year, int32 month, int32 day )
{
	return GetDate( year, month, day, 0, 0, 0 );
}

Windows::Foundation::DateTime AssertHelper::GetDate( int32 year, int32 month, int32 day, int32 hour, int32 minute, int32 second )
{
	return GetDate( year, month, day, hour, minute, second, 0 );
}

Windows::Foundation::DateTime AssertHelper::GetDate( int32 year, int32 month, int32 day, int32 hour, int32 minute, int32 second, int32 nanosecond )
{
	const auto& calender = ref new Windows::Globalization::Calendar();
	calender->Year = year;
	calender->Month = month;
	calender->Day = day;
	calender->Hour = hour;
	calender->Minute = minute;
	calender->Second = second;
	calender->Nanosecond = nanosecond;
	return calender->GetDateTime();
}