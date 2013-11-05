#pragma once
#include "IAmfValue.h"
#include "amf3_traits_info.h"

namespace Mntone { namespace Data { namespace Amf {

#if _DEBUG
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Amf3Parser sealed
	{
	public:
#else
	ref class Amf3Parser sealed
	{
	internal:
#endif
		static IAmfValue^ Parse( const Platform::Array<uint8>^ input );
		static bool TryParse( const Platform::Array<uint8>^ input, IAmfValue^* result );

	private:
		IAmfValue^ ParseValue( uint8*& input, size_t& length );

		IAmfValue^ ParseUndefined( uint8*& input, size_t& length );
		IAmfValue^ ParseNull( uint8*& input, size_t& length );
		IAmfValue^ ParseFalse( uint8*& input, size_t& length );
		IAmfValue^ ParseTrue( uint8*& input, size_t& length );

		IAmfValue^ ParseInteger( uint8*& input, size_t& length );
		IAmfValue^ ParseDouble( uint8*& input, size_t& length );

		IAmfValue^ ParseString( uint8*& input, size_t& length );
		Platform::String^ ParseStringBase( uint8*& input, size_t& length );
		IAmfValue^ ParseXml( uint8*& input, size_t& length );
		IAmfValue^ ParseDate( uint8*& input, size_t& length );
		
		IAmfValue^ ParseArray( uint8*& input, size_t& length );
		IAmfValue^ ParseObject( uint8*& input, size_t& length );
		
		IAmfValue^ ParseByteArray( uint8*& input, size_t& length );
		IAmfValue^ ParseVectorInt( uint8*& input, size_t& length );
		IAmfValue^ ParseVectorUint( uint8*& input, size_t& length );
		IAmfValue^ ParseVectorDouble( uint8*& input, size_t& length );
		template<typename T>
		std::vector<T> ParseVectorBase( uint8*& input, size_t& length, const size_t arrayLength );
		IAmfValue^ ParseVectorObject( uint8*& input, size_t& length );

		//IAmfValue^ ParseDictionary( uint8*& input, size_t& length );

		Platform::String^ ParseUtf8( uint8*& input, size_t& length, const uint32 textLength );
		uint32 ParseUnsigned29bitInteger( uint8*& input, size_t& length );
		IAmfValue^ GetObject( const size_t& input );

	private:
		std::vector<Platform::String^> stringReferenceBuffer_;
		std::vector<IAmfValue^> objectReferenceBuffer_;
		std::vector<IAmfValue^> arrayReferenceBuffer_;
		std::vector<std::shared_ptr<amf3_traits_info>> traitsReferenceBuffer_;
	};

} } }
