#include "pch.h"
#include "Utilities.h"

void Mntone::Data::Amf::ConvertBigEndian( const void *const from, void *const to, const size_t size )
{
	auto const from_ptr = reinterpret_cast<const uint8 *>( from );
	auto const to_ptr = reinterpret_cast<uint8 *>( to );

	for( auto i = 0u; i < size; ++i )
		to_ptr[i] = from_ptr[size - i - 1];
}

Platform::String^ Mntone::Data::Amf::CharUtf8ToPlatformString( const std::string& charUtf8 )
{
	const auto charUtf8Length = static_cast<int32>( charUtf8.length() );
	const auto length = MultiByteToWideChar( CP_UTF8, 0, charUtf8.c_str(), charUtf8Length, nullptr, 0 );
	if( length == 0 )
		return "";

	const auto bufferLength = length + 1;
	std::vector<char16> buffer( bufferLength, 0 );
	if( MultiByteToWideChar( CP_UTF8, 0, charUtf8.c_str(), charUtf8Length, buffer.data(), bufferLength ) == 0 )
		throw ref new Platform::InvalidArgumentException( "Invaild text" );
	return ref new Platform::String( buffer.data() );
}

std::string Mntone::Data::Amf::PlatformStringToCharUtf8( Platform::String^ platformString )
{
	const auto length = WideCharToMultiByte( CP_UTF8, 0, platformString->Data(), platformString->Length(), nullptr, 0, nullptr, nullptr );
	if( length == 0 )
		return std::string( "" );

	const auto bufferLength = length + 1;
	std::vector<char> buffer( bufferLength, 0 );
	if( WideCharToMultiByte( CP_UTF8, 0, platformString->Data(), platformString->Length(), buffer.data(), bufferLength, nullptr, nullptr ) == 0 )
		throw ref new Platform::InvalidArgumentException( "Invaild text" );
	return std::string( buffer.data() );
}

uint64 Mntone::Data::Amf::DateTimeToUnixTime( Windows::Foundation::DateTime dateTime )
{
	return ( dateTime.UniversalTime - 116444736000000000ull ) / 10000ull;
}

Windows::Foundation::DateTime Mntone::Data::Amf::UnixTimeToDateTime( const uint64 unixTime )
{
	Windows::Foundation::DateTime d;
	d.UniversalTime = 10000ll * unixTime + 116444736000000000ll;
	return d;
}