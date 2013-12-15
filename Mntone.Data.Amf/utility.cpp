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


Platform::String^ utility::char_utf8_to_platform_string( const std::string& char_utf8 )
{
	const auto& char_utf8_length = static_cast<int32>( char_utf8.length() );
	const auto& length = MultiByteToWideChar( CP_UTF8, 0, char_utf8.c_str(), char_utf8_length, nullptr, 0 );
	if( length == 0 )
		return "";

	const auto& buffer_length = length + 1;
	std::vector<char16> buffer( buffer_length, 0 );
	if( MultiByteToWideChar( CP_UTF8, 0, char_utf8.c_str(), char_utf8_length, buffer.data(), buffer_length ) == 0 )
		throw ref new Platform::InvalidArgumentException( "Invaild text" );
	return ref new Platform::String( buffer.data() );
}

std::string utility::platform_string_to_char_utf8( Platform::String^ platform_string )
{
	const auto& length = WideCharToMultiByte( CP_UTF8, 0, platform_string->Data(), platform_string->Length(), nullptr, 0, nullptr, nullptr );
	if( length == 0 )
		return std::string( "" );

	const auto& buffer_length = length + 1;
	std::vector<char> buffer( buffer_length, 0 );
	if( WideCharToMultiByte( CP_UTF8, 0, platform_string->Data(), platform_string->Length(), buffer.data(), buffer_length, nullptr, nullptr ) == 0 )
		throw ref new Platform::InvalidArgumentException( "Invaild text" );
	return std::string( buffer.data() );
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