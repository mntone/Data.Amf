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

		void SequenceifyUnsigned29bitInteger( uint32 input, std::basic_stringstream<uint8>& stream );

	private:
		std::vector<IAmfValue^> referenceBuffer_;
	};

} } }
