#pragma once
#include "IAmfValue.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::WebHostHidden]
	public interface class IAmfArray: IAmfValue
	{
		bool GetBooleanAt( uint32 index );
		float64 GetNumberAt( uint32 index );
		Platform::String^ GetStringAt( uint32 index );
		Windows::Foundation::DateTime GetDateAt( uint32 index );
		Platform::Array<uint8>^ GetByteArrayAt( uint32 index );
		Windows::Foundation::Collections::IVector<int32>^ GetVectorIntAt( uint32 index );
		Windows::Foundation::Collections::IVector<uint32>^ GetVectorUintAt( uint32 index );
		Windows::Foundation::Collections::IVector<float64>^ GetVectorDoubleAt( uint32 index );
		Windows::Foundation::Collections::IVector<IAmfValue^>^ GetVectorObjectAt( uint32 index );
		AmfObject^ GetObjectAt( uint32 index );
		AmfArray^ GetArrayAt( uint32 index );
	};

} } }
