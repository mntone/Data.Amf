#pragma once
#include "IAmfValue.h"

#if _DEBUG
namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class amf0_sequencer sealed
#else
namespace mntone { namespace data { namespace amf {

	class amf0_sequencer
#endif
	{
	public:
		static Platform::Array<uint8>^ sequencify( Mntone::Data::Amf::IAmfValue^ input );

	private:
		amf0_sequencer();
#if !_DEBUG &&!_WINDOWS_PHONE
		amf0_sequencer( const amf0_sequencer& ) = delete;
		amf0_sequencer( amf0_sequencer&& ) = delete;

		amf0_sequencer& operator=( const amf0_sequencer& ) = delete;
		amf0_sequencer& operator=( amf0_sequencer&& ) = delete;
#endif

		void sequencify_value( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );

		void sequencify_undefined( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_null( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_boolean( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_number( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_string( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_date( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_xml( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );

		void sequencify_object( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_ecma_array( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_object_base( Mntone::Data::Amf::AmfObject^ input, std::basic_ostringstream<uint8>& stream );

		void sequencify_strict_array( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );

		void sequencify_utf8( const std::string& input, std::basic_ostringstream<uint8>& stream );
		void sequencify_utf8( Platform::String^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_utf8( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_utf8_long( const std::string& input, std::basic_ostringstream<uint8>& stream );
		void sequencify_utf8_long( Platform::String^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_utf8_long( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );

		int32 index_of_object_identical_to( Mntone::Data::Amf::IAmfValue^ input );
		void sequencify_reference( int32 input, std::basic_ostringstream<uint8>& stream );

	private:
		std::vector<Mntone::Data::Amf::IAmfValue^> reference_buffer_;
	};

} } }
