#pragma once
#include "pch.h"
#include "IAmfValue.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::WebHostHidden]
	public interface class IAmfArray: IAmfValue
	{
		bool GetBooleanAt( uint32 index );
		float64 GetDoubleAt( uint32 index );
		int32 GetIntegerAt( uint32 index );
		Platform::String^ GetStringAt( uint32 index );
		uint16 GetReferenceAt( uint32 index );
		Windows::Foundation::DateTime GetDateAt( uint32 index );
		AmfObject^ GetObjectAt( uint32 index );
		AmfArray^ GetArrayAt( uint32 index );
	};

} } }
