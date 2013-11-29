#pragma once
#include "amf3_traits_info.h"
#include "IAmfValue.h"

#if _DEBUG
namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class amf3_sequencer sealed
#else
namespace mntone { namespace data { namespace amf {

	class amf3_sequencer
#endif
	{
	public:
		static Platform::Array<uint8>^ sequencify( Mntone::Data::Amf::IAmfValue^ input );

	private:
		amf3_sequencer( void );

		void sequencify_value( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );

		void sequencify_undefined( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_null( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_boolean( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );

		void sequencify_integer( const float64 input, std::basic_ostringstream<uint8>& stream );
		void sequencify_double( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );

		void sequencify_string( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_string_base( Platform::String^ input, std::basic_ostringstream<uint8>& stream );

		void sequencify_date( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_xml( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );

		void sequencify_byte_array( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_vector_int( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_vector_uint( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_vector_double( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		template<typename T, size_t S>
		void sequencify_vector_base( Windows::Foundation::Collections::IVector<T>^ input, std::basic_ostringstream<uint8>& stream )
		{
			const auto& length = input->Size;
			sequencify_unsigned_28bit_integer_and_reference( length, false, stream );

			stream.put( 0 );
			for( uint32 i = 0u; i < length; ++i )
			{
				const auto& data = input->GetAt( i );
				uint8 buf[S];
				utilities::convert_big_endian( &data, buf, S );
				stream.write( buf, S );
			}
		}
		void sequencify_vector_object( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );

		void sequencify_object( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_ecma_array( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void sequencify_array( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );

		void sequencify_dictionary( Mntone::Data::Amf::IAmfValue^ input, std::basic_ostringstream<uint8>& stream );

		void sequencify_unsigned_28bit_integer_and_reference( const size_t input, const bool reference, std::basic_ostringstream<uint8>& stream );
		void sequencify_unsigned_29bit_integer( const size_t input, std::basic_ostringstream<uint8>& stream );

		int32 index_of_object_identical_to( Mntone::Data::Amf::IAmfValue^ input );

	private:
		std::vector<Platform::String^> string_reference_buffer_;
		std::vector<Mntone::Data::Amf::IAmfValue^> object_reference_buffer_;
		std::vector<std::shared_ptr<mntone::data::amf::amf3_traits_info>> traits_info_buffer_;
	};

} } }
