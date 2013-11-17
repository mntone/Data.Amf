#pragma once
#include "pch.h"

namespace mntone { namespace data { namespace amf {

	class utilities
	{
	public:
		static void convert_big_endian( const void *const from, void *const to, const size_t size );

		static Platform::String^ char_utf8_to_platform_string( const std::string& char_utf8 );
		static std::string platform_string_to_char_utf8( Platform::String^ platform_string );

		static uint64 date_time_to_unix_time( Windows::Foundation::DateTime date_time );
		static Windows::Foundation::DateTime unix_time_to_date_time( const uint64 date_time );
	};

} } }
