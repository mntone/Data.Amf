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

	private:
		Amf0Parser( void );

		IAmfValue^ ParseValue( uint8*& input, uint32& length );

		IAmfValue^ ParseNumber( uint8*& input, uint32& length );
		IAmfValue^ ParseBoolean( uint8*& input, uint32& length );
		IAmfValue^ ParseNull( uint8*& input, uint32& length );
		IAmfValue^ ParseUndefined( uint8*& input, uint32& length );
		IAmfValue^ ParseReference( uint8*& input, uint32& length );
		IAmfValue^ ParseDate( uint8*& input, uint32& length );

		IAmfValue^ ParseString( uint8*& input, uint32& length );
		IAmfValue^ ParseLongString( uint8*& input, uint32& length );
		IAmfValue^ ParseXmlDocument( uint8*& input, uint32& length );

		IAmfValue^ ParseEcmaArray( uint8*& input, uint32& length );
		IAmfValue^ ParseStrictArray( uint8*& input, uint32& length );
		IAmfValue^ ParseFlexibleArray( uint8*& input, uint32& length );

		IAmfValue^ ParseObject( uint8*& input, uint32& length );
		IAmfValue^ ParseTypedObject( uint8*& input, uint32& length );
		std::unordered_map<Platform::String^, IAmfValue^> ParseObjectBase( uint8*& input, uint32& length );
		std::pair<Platform::String^, IAmfValue^> ParseProperty( uint8*& input, uint32& length );

		Platform::String^ ParseUtf8( uint8*& input, uint32& length );
		Platform::String^ ParseUtf8Long( uint8*& input, uint32& length );
		Platform::String^ ParseUtf8Base( uint8*& input, uint32& length, const uint32 textLength );

	private:
		std::vector<IAmfValue^> _referenceBuffer;
	};

} } }
