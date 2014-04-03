#pragma once
#include "amf3_traits_info.h"
#include "IAmfValue.h"

#if _DEBUG
namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class amf3_parser sealed
#else
namespace mntone { namespace data { namespace amf {

	class amf3_parser
#endif
	{
public:
		static Mntone::Data::Amf::IAmfValue^ parse( const Platform::Array<uint8>^ input );
		static bool try_parse( const Platform::Array<uint8>^ input, Mntone::Data::Amf::IAmfValue^* result );

#if _DEBUG
	internal:
#else
	public:
#endif
		amf3_parser();
#if !_DEBUG &&!_WINDOWS_PHONE8
		amf3_parser( const amf3_parser& ) = delete;
		amf3_parser( amf3_parser&& ) = delete;

		amf3_parser& operator=( const amf3_parser& ) = delete;
		amf3_parser& operator=( amf3_parser&& ) = delete;
#endif

		Mntone::Data::Amf::IAmfValue^ parse_value( uint8*& input, size_t& length );

	private:
		Mntone::Data::Amf::IAmfValue^ parse_undefined( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_null( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_false( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_true( uint8*& input, size_t& length );

		Mntone::Data::Amf::IAmfValue^ parse_integer( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_double( uint8*& input, size_t& length );

		Mntone::Data::Amf::IAmfValue^ parse_string( uint8*& input, size_t& length );
		Platform::String^ parse_string_base( uint8*& input, size_t& length );

		Mntone::Data::Amf::IAmfValue^ parse_xml( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_date( uint8*& input, size_t& length );
		
		Mntone::Data::Amf::IAmfValue^ parse_array( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_object( uint8*& input, size_t& length );
		
		Mntone::Data::Amf::IAmfValue^ parse_byte_array( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_vector_int( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_vector_uint( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_vector_double( uint8*& input, size_t& length );
		template<typename T>
		Windows::Foundation::Collections::IVector<T>^ parse_vector_base( uint8*& input, size_t& length, const size_t array_length )
		{
			//const auto& fixed = *value;
			input += 1;
			length -= 1;

			const auto& size = sizeof( T );
			std::vector<T> vector( array_length );
			for( size_t i = 0; i < array_length; ++i, input += size, length -= size )
			{
				T data;
				utility::convert_big_endian( input, size, &data );
				vector[i] = data;
			}

			return ref new Platform::Collections::Vector<T>( std::move( vector ) );
		}
		Mntone::Data::Amf::IAmfValue^ parse_vector_object( uint8*& input, size_t& length );

		Mntone::Data::Amf::IAmfValue^ parse_dictionary( uint8*& input, size_t& length );

		Platform::String^ parse_utf8( uint8*& input, size_t& length, const uint32 text_length );
		uint32 parse_unsigned_29bit_integer( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ get_object( const size_t input );

	private:
		std::vector<Platform::String^> string_reference_buffer_;
		std::vector<Mntone::Data::Amf::IAmfValue^> object_reference_buffer_;
		std::vector<std::shared_ptr<mntone::data::amf::amf3_traits_info>> traits_info_buffer_;
	};

} } }
