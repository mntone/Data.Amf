#include "pch.h"
#include "utility.h"

using namespace mntone::data::amf;

void utility::convert_big_endian( const void* first, size_t size, void* dest )
{
	auto ptr = reinterpret_cast<const uint8*>( first ) + size;
	auto pdest = reinterpret_cast<uint8*>( dest );

	for( ; first != ptr; ++pdest )
		*pdest = *--ptr;
}


Platform::String^ utility::char_utf8_to_platform_string( const uint8_t* const ptr, const int32 utf8_length )
{
	const auto& str = reinterpret_cast<const char* const>( ptr );
	const auto& utf16_length = MultiByteToWideChar( CP_UTF8, 0, str, utf8_length, nullptr, 0 );
	if( utf16_length == 0 )
		return "";

	const auto& buffer_length = utf16_length + 1;
	std::vector<char16> buffer( buffer_length, 0 );
	if( MultiByteToWideChar( CP_UTF8, 0, str, utf8_length, buffer.data(), buffer_length ) == 0 )
		throw ref new Platform::InvalidArgumentException( "Invaild text" );
	return ref new Platform::String( buffer.data(), utf16_length );
}

std::string utility::platform_string_to_char_utf8( Platform::String^ platform_string )
{
	const auto& utf8_length = WideCharToMultiByte( CP_UTF8, 0, platform_string->Data(), platform_string->Length(), nullptr, 0, nullptr, nullptr );
	if( utf8_length == 0 )
		return std::string( "" );

	std::string buffer( utf8_length, 0 );
	if( WideCharToMultiByte( CP_UTF8, 0, platform_string->Data(), platform_string->Length(), &buffer[0], utf8_length, nullptr, nullptr ) == 0 )
		throw ref new Platform::InvalidArgumentException( "Invaild text" );
	return buffer;
}

uint64 utility::date_time_to_unix_time( Windows::Foundation::DateTime date_time )
{
	return ( date_time.UniversalTime - 116444736000000000ull ) / 10000ull;
}

Windows::Foundation::DateTime utility::unix_time_to_date_time( const uint64 date_time )
{
	Windows::Foundation::DateTime d;
	d.UniversalTime = 10000ll * date_time + 116444736000000000ll;
	return d;
}