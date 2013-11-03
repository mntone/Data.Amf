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

		IAmfValue^ ParseValue( uint8*& input, size_t& length );

		IAmfValue^ ParseNumber( uint8*& input, size_t& length );
		IAmfValue^ ParseBoolean( uint8*& input, size_t& length );
		IAmfValue^ ParseNull( uint8*& input, size_t& length );
		IAmfValue^ ParseUndefined( uint8*& input, size_t& length );
		IAmfValue^ ParseReference( uint8*& input, size_t& length );
		IAmfValue^ ParseDate( uint8*& input, size_t& length );

		IAmfValue^ ParseString( uint8*& input, size_t& length );
		IAmfValue^ ParseLongString( uint8*& input, size_t& length );
		IAmfValue^ ParseXmlDocument( uint8*& input, size_t& length );

		IAmfValue^ ParseEcmaArray( uint8*& input, size_t& length );
		IAmfValue^ ParseStrictArray( uint8*& input, size_t& length );
		IAmfValue^ ParseFlexibleArray( uint8*& input, size_t& length );

		IAmfValue^ ParseObject( uint8*& input, size_t& length );
		IAmfValue^ ParseTypedObject( uint8*& input, size_t& length );
		std::unordered_map<Platform::String^, IAmfValue^> ParseObjectBase( uint8*& input, size_t& length );
		std::pair<Platform::String^, IAmfValue^> ParseProperty( uint8*& input, size_t& length );

		Platform::String^ ParseUtf8( uint8*& input, size_t& length );
		Platform::String^ ParseUtf8Long( uint8*& input, size_t& length );
		Platform::String^ ParseUtf8Base( uint8*& input, size_t& length, const uint32 textLength );

	private:
		std::vector<IAmfValue^> referenceBuffer_;
	};

} } }
