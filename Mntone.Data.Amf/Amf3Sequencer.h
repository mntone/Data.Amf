#pragma once
#include "IAmfValue.h"

namespace Mntone { namespace Data { namespace Amf {

#if _DEBUG
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Amf3Sequencer sealed
	{
	public:
#else
	ref class Amf3Sequencer sealed
	{
	internal:
#endif
		static Platform::Array<uint8>^ Sequencify( IAmfValue^ input );

	private:
		Amf3Sequencer( void );

		void SequencifyValue( IAmfValue^ input, std::basic_stringstream<uint8>& stream );

		void SequencifyUndefined( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequencifyNull( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequencifyBoolean( IAmfValue^ input, std::basic_stringstream<uint8>& stream );

		void SequencifyInteger( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequencifyDouble( IAmfValue^ input, std::basic_stringstream<uint8>& stream );

		void SequencifyString( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequencifyStringBase( Platform::String^ input, std::basic_stringstream<uint8>& stream );

		void SequencifyDate( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequencifyXml( IAmfValue^ input, std::basic_stringstream<uint8>& stream );

		void SequencifyByteArray( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequencifyVectorInt( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequencifyVectorUint( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequencifyVectorDouble( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		template<typename T, size_t S>
		void SequencifyVectorBase( Windows::Foundation::Collections::IVector<T>^ input, std::basic_stringstream<uint8>& stream )
		{
			SequencifyUnsigned28bitIntegerAndReference( input->Size, false, stream );

			stream.put( 0 );
			for( const auto& item : input )
			{
				uint8 buf[S];
				ConvertBigEndian( &item, buf, S );
				stream.write( buf, S );
			}
		}

		void SequencifyUnsigned28bitIntegerAndReference( const size_t input, const bool reference, std::basic_stringstream<uint8>& stream );
		void SequencifyUnsigned29bitInteger( const size_t input, std::basic_stringstream<uint8>& stream );

		int32 IsObjectReference( IAmfValue^ input );

	private:
		std::vector<Platform::String^> stringReferenceBuffer_;
		std::vector<IAmfValue^> objectReferenceBuffer_;
	};

} } }
