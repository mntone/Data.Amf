#pragma once
#include "IAmfValue.h"

#if _DEBUG
namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class amf0_parser sealed
#else
namespace mntone { namespace data { namespace amf {

	class amf0_parser
#endif
	{
	public:
		static Mntone::Data::Amf::IAmfValue^ parse( const Platform::Array<uint8>^ input );
		static bool try_parse( const Platform::Array<uint8>^ input, Mntone::Data::Amf::IAmfValue^* result );

	private:
		amf0_parser();
#if !_DEBUG &&!_WINDOWS_PHONE8
		amf0_parser( const amf0_parser& ) = delete;
		amf0_parser( amf0_parser&& ) = delete;

		amf0_parser& operator=( const amf0_parser& ) = delete;
		amf0_parser& operator=( amf0_parser&& ) = delete;
#endif

		Mntone::Data::Amf::IAmfValue^ parse_value( uint8*& input, size_t& length );

		Mntone::Data::Amf::IAmfValue^ parse_number( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_boolean( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_null( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_undefined( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_reference( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_date( uint8*& input, size_t& length );

		Mntone::Data::Amf::IAmfValue^ parse_string( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_long_string( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_xml_document( uint8*& input, size_t& length );

		Mntone::Data::Amf::IAmfValue^ parse_strict_array( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_flexible_array( uint8*& input, size_t& length );

		Mntone::Data::Amf::IAmfValue^ parse_object( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_ecma_array( uint8*& input, size_t& length );
		Mntone::Data::Amf::IAmfValue^ parse_typed_object( uint8*& input, size_t& length );
#if _WINDOWS_PHONE8
		std::map<Platform::String^, Mntone::Data::Amf::IAmfValue^> parse_object_base( uint8*& input, size_t& length );
#else
		std::unordered_map<Platform::String^, Mntone::Data::Amf::IAmfValue^> parse_object_base( uint8*& input, size_t& length );
#endif
		std::pair<Platform::String^, Mntone::Data::Amf::IAmfValue^> parse_property( uint8*& input, size_t& length );

		Mntone::Data::Amf::IAmfValue^ parse_avmplus_object( uint8*& input, size_t& length );

		Platform::String^ parse_utf8( uint8*& input, size_t& length );
		Platform::String^ parse_utf8_long( uint8*& input, size_t& length );
		Platform::String^ parse_utf8_base( uint8*& input, size_t& length, const size_t text_length );

	private:
		std::vector<Mntone::Data::Amf::IAmfValue^> reference_buffer_;
	};

} } }
