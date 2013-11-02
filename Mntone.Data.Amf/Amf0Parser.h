#pragma once
#include "IAmfValue.h"

namespace Mntone { namespace Data { namespace Amf {

#if _DEBUG
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Amf0Parser sealed
	{
	public:
#else
	ref class Amf0Parser sealed
	{
	internal:
#endif
		static IAmfValue^ Parse( const Platform::Array<uint8>^ input );
		static bool TryParse( const Platform::Array<uint8>^ input, IAmfValue^* result );

	internal:
		static IAmfValue^ ParseValue( uint8*& input, uint32& length );

		static IAmfValue^ ParseNumber( uint8*& input, uint32& length );
		static IAmfValue^ ParseBoolean( uint8*& input, uint32& length );
		static IAmfValue^ ParseNull( uint8*& input, uint32& length );
		static IAmfValue^ ParseUndefined( uint8*& input, uint32& length );
		static IAmfValue^ ParseReference( uint8*& input, uint32& length );
		static IAmfValue^ ParseDate( uint8*& input, uint32& length );

		static IAmfValue^ ParseString( uint8*& input, uint32& length );
		static IAmfValue^ ParseLongString( uint8*& input, uint32& length );
		static IAmfValue^ ParseXmlDocument( uint8*& input, uint32& length );

		static IAmfValue^ ParseEcmaArray( uint8*& input, uint32& length );
		static IAmfValue^ ParseStrictArray( uint8*& input, uint32& length );
		static IAmfValue^ ParseFlexibleArray( uint8*& input, uint32& length );

		static Platform::String^ ParseUtf8( uint8*& input, uint32& length );
		static Platform::String^ ParseUtf8Long( uint8*& input, uint32& length );
		static Platform::String^ ParseUtf8Base( uint8*& input, uint32& length, const uint32 textLength );

		static IAmfValue^ ParseObject( uint8*& input, uint32& length );
		static IAmfValue^ ParseTypedObject( uint8*& input, uint32& length );
		static std::map<Platform::String^, IAmfValue^> ParseObjectBase( uint8*& input, uint32& length );
		static std::pair<Platform::String^, IAmfValue^> ParseProperty( uint8*& input, uint32& length );
	};

} } }
