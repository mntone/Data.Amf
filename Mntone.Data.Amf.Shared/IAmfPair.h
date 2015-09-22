#pragma once
#include "IAmfArray.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::WebHostHidden]
	public interface class IAmfPair
	{
		property AmfValueType KeyType
		{
			AmfValueType get();
		}
		property IAmfValue^ Key
		{
			IAmfValue^ get();
			void set( IAmfValue^ value );
		}
		property AmfValueType ValueType
		{
			AmfValueType get();
		}
		property IAmfValue^ Value
		{
			IAmfValue^ get();
			void set( IAmfValue^ value );
		}
	};

} } }
