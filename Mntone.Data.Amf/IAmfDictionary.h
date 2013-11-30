#pragma once
#include "AmfPair.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::WebHostHidden]
	public interface class IAmfDictionary:
		public IAmfValue,
		public Windows::Foundation::Collections::IVector<AmfPair^>
	{
		// IAmfDictionary: write methods
		void SetPairAt( uint32 index, IAmfValue^ key, IAmfValue^ value );
		void InsertPairAt( uint32 index, IAmfValue^ key, IAmfValue^ value );
		void AppendPair( IAmfValue^ key, IAmfValue^ value );
	};

} } }
