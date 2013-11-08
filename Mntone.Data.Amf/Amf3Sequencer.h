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
		static Platform::Array<uint8>^ Sequenceify( IAmfValue^ input );

	private:
		Amf3Sequencer( void );

		void SequenceifyValue( IAmfValue^ input, std::basic_stringstream<uint8>& stream );

		void SequenceifyUndefined( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyNull( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyBoolean( IAmfValue^ input, std::basic_stringstream<uint8>& stream );

		void SequenceifyInteger( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyDouble( IAmfValue^ input, std::basic_stringstream<uint8>& stream );

		void SequenceifyString( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyStringBase( Platform::String^ input, std::basic_stringstream<uint8>& stream );

		void SequenceifyDate( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyXml( IAmfValue^ input, std::basic_stringstream<uint8>& stream );

		void SequenceifyByteArray( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyVectorInt( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyVectorUint( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyVectorDouble( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		template<typename T, size_t S>
		void SequenceifyVectorBase( Windows::Foundation::Collections::IVector<T>^ input, std::basic_stringstream<uint8>& stream )
		{
			SequenceifyUnsigned28bitIntegerAndReference( input->Size, false, stream );

			stream.put( 0 );
			for( const auto& item : input )
			{
				uint8 buf[S];
				ConvertBigEndian( &item, buf, S );
				stream.write( buf, S );
			}
		}

		void SequenceifyUnsigned28bitIntegerAndReference( const uint32 input, const bool reference, std::basic_stringstream<uint8>& stream );
		void SequenceifyUnsigned29bitInteger( const uint32 input, std::basic_stringstream<uint8>& stream );

		int32 IsObjectReference( IAmfValue^ input );

	private:
		std::vector<Platform::String^> stringReferenceBuffer_;
		std::vector<IAmfValue^> objectReferenceBuffer_;
	};

} } }
