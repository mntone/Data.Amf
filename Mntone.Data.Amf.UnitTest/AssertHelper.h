#pragma once

class AssertHelper
{
public:
	static void AreArrayEqual( const Platform::Array<uint8>^ expected, const Platform::Array<uint8>^ actual );

	static Windows::Foundation::DateTime GetDate( int32 year, int32 month, int32 day );
	static Windows::Foundation::DateTime GetDate( int32 year, int32 month, int32 day, int32 hour, int32 minute, int32 second );
	static Windows::Foundation::DateTime GetDate( int32 year, int32 month, int32 day, int32 hour, int32 minute, int32 second, int32 nanosecond );
};
