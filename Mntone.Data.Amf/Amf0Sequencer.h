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
		static Platform::Array<uint8>^ Sequencify( IAmfValue^ input );

	private:
		Amf0Sequencer( void );

		void SequencifyValue( IAmfValue^ input, std::basic_ostringstream<uint8>& stream );

		void SequencifyUndefined( IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void SequencifyNull( IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void SequencifyBoolean( IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void SequencifyNumber( IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void SequencifyString( IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void SequencifyDate( IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void SequencifyXml( IAmfValue^ input, std::basic_ostringstream<uint8>& stream );

		void SequencifyObject( IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void SequencifyEcmaArray( IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void SequencifyObjectBase( AmfObject^ input, std::basic_ostringstream<uint8>& stream );

		void SequencifyStrictArray( IAmfValue^ input, std::basic_ostringstream<uint8>& stream );

		void SequencifyUtf8( const std::string& input, std::basic_ostringstream<uint8>& stream );
		void SequencifyUtf8( Platform::String^ input, std::basic_ostringstream<uint8>& stream );
		void SequencifyUtf8( IAmfValue^ input, std::basic_ostringstream<uint8>& stream );
		void SequencifyUtf8Long( const std::string& input, std::basic_ostringstream<uint8>& stream );
		void SequencifyUtf8Long( Platform::String^ input, std::basic_ostringstream<uint8>& stream );
		void SequencifyUtf8Long( IAmfValue^ input, std::basic_ostringstream<uint8>& stream );

		int32 IndexOfObjectIdenticalTo( IAmfValue^ input );
		void SequencifyReference( int32 input, std::basic_ostringstream<uint8>& stream );

	private:
		std::vector<IAmfValue^> referenceBuffer_;
	};

} } }
