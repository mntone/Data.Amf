#pragma once
#include "IAmfValue.h"

namespace Mntone { namespace Data { namespace Amf {

#if _DEBUG
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Amf0Sequencer sealed
	{
	public:
#else
	ref class Amf0Sequencer sealed
	{
	internal:
#endif
		static Platform::Array<uint8>^ Sequenceify( IAmfValue^ input );

	private:
		Amf0Sequencer( void );

		void SequenceifyValue( IAmfValue^ input, std::basic_stringstream<uint8>& stream );

		void SequenceifyUndefined( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyNull( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyBoolean( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyDouble( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyInteger( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyString( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyDate( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyXml( IAmfValue^ input, std::basic_stringstream<uint8>& stream );

		void SequenceifyObject( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyEcmaArray( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyObjectBase( AmfObject^ input, std::basic_stringstream<uint8>& stream );

		void SequenceifyStrictArray( IAmfValue^ input, std::basic_stringstream<uint8>& stream );

		void SequenceifyUtf8( const std::string& input, std::basic_stringstream<uint8>& stream );
		void SequenceifyUtf8( Platform::String^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyUtf8( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyUtf8Long( const std::string& input, std::basic_stringstream<uint8>& stream );
		void SequenceifyUtf8Long( Platform::String^ input, std::basic_stringstream<uint8>& stream );
		void SequenceifyUtf8Long( IAmfValue^ input, std::basic_stringstream<uint8>& stream );

		int32 IsReference( IAmfValue^ input );
		void SequenceifyReference( int32 input, std::basic_stringstream<uint8>& stream );

	private:
		std::vector<IAmfValue^> referenceBuffer_;
	};

} } }
