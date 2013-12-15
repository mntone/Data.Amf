#pragma once

namespace mntone { namespace data { namespace amf { namespace utility {

	void convert_big_endian( const void* first, size_t size, void* dest );

	Platform::String^ char_utf8_to_platform_string( const std::string& char_utf8 );
	std::string platform_string_to_char_utf8( Platform::String^ platform_string );

	uint64 date_time_to_unix_time( Windows::Foundation::DateTime date_time );
	Windows::Foundation::DateTime unix_time_to_date_time( const uint64 date_time );

} } } }
