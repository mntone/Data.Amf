#pragma once
#include "pch.h"
#include "IAmfValue.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::WebHostHidden]
#if _DEBUG
	public
#endif
	ref class Amf0Parser
#if _DEBUG
	sealed
#endif
	{
#if _DEBUG
	public:
#else
	internal:
#endif
		static IAmfValue^ Parse( const Platform::Array<uint8>^ input );
		static bool TryParse( const Platform::Array<uint8>^ input, IAmfValue^* result );

#if _DEBUG
	internal:
#endif
		static IAmfValue^ ParseValue( uint8 *& input, uint32& length );

		static IAmfValue^ ParseNumber( uint8 *& input, uint32& length );
		static IAmfValue^ ParseBoolean( uint8 *& input, uint32& length );
		static IAmfValue^ ParseNull( uint8 *& input, uint32& length );
		static IAmfValue^ ParseUndefined( uint8 *& input, uint32& length );
		static IAmfValue^ ParseReference( uint8 *& input, uint32& length );
		static IAmfValue^ ParseStrictArray( uint8 *& input, uint32& length );
		static IAmfValue^ ParseDate( uint8 *& input, uint32& length );

		static IAmfValue^ ParseString( uint8 *& input, uint32& length );
		static IAmfValue^ ParseLongString( uint8 *& input, uint32& length );
		static IAmfValue^ ParseXmlDocument( uint8 *& input, uint32& length );

		static Platform::String^ ParseUtf8( uint8 *& input, uint32& length );
		static Platform::String^ ParseUtf8Long( uint8 *& input, uint32& length );
		static Platform::String^ ParseUtf8Base( uint8 *& input, uint32& length, const uint32 textLength );

		static IAmfValue^ ParseObject( uint8 *& input, uint32& length );
		static IAmfValue^ ParseEcmaArray( uint8 *& input, uint32& length );
		static IAmfValue^ ParseTypedObject( uint8 *& input, uint32& length );
		static std::pair<Platform::String^, IAmfValue^> ParseProperty( uint8 *& input, uint32& length );
	};

} } }
