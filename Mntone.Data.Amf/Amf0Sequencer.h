#pragma once
#include "pch.h"
#include "IAmfValue.h"

namespace Mntone { namespace Data { namespace Amf {

#if _DEBUG
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Amf0Sequencer sealed
#else
	ref class Amf0Sequencer
#endif
	{
	public:
		static Platform::Array<uint8>^ Sequenceify( IAmfValue^ input );

	internal:
		static void SequenceifyValue( IAmfValue^ input, std::basic_stringstream<uint8>& stream );

		static void SequenceifyUndefined( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		static void SequenceifyNull( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		static void SequenceifyBoolean( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		static void SequenceifyDouble( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		static void SequenceifyInteger( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		static void SequenceifyString( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		static void SequenceifyReference( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		static void SequenceifyDate( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		static void SequenceifyXml( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		static void SequenceifyObject( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		static void SequenceifyArray( IAmfValue^ input, std::basic_stringstream<uint8>& stream );

		static void SequenceifyUtf8( const std::string& input, std::basic_stringstream<uint8>& stream );
		static void SequenceifyUtf8( Platform::String^ input, std::basic_stringstream<uint8>& stream );
		static void SequenceifyUtf8( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
		static void SequenceifyUtf8Long( const std::string& input, std::basic_stringstream<uint8>& stream );
		static void SequenceifyUtf8Long( Platform::String^ input, std::basic_stringstream<uint8>& stream );
		static void SequenceifyUtf8Long( IAmfValue^ input, std::basic_stringstream<uint8>& stream );
	};

} } }
