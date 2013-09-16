#pragma once
#include "pch.h"

namespace Mntone { namespace Data { namespace Amf {

	extern void ConvertBigEndian( const void *const from, void *const to, const size_t size );

	extern Platform::String^ CharUtf8ToPlatformString( const std::string& charUtf8 );
	extern std::string PlatformStringToCharUtf8( Platform::String^ platformString );

	// Windows Time (1 ns units), Unix Time (1 ms units; however, default Unix Time 1 s units)
	extern uint64 WindowsTimeToUnixTime( const int64 windowsTime );
	extern int64 UnixTimeToWindowsTime( const uint64 unixTime );

	extern uint64 DateTimeToUnixTime( Windows::Foundation::DateTime dateTime );
	extern Windows::Foundation::DateTime UnixTimeToDateTime( const uint64 unixTime );

} } }
