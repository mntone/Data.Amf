#pragma once
#include "AmfEncodingType.h"
#include "AmfValueType.h"

namespace Mntone { namespace Data { namespace Amf {

	ref class AmfValue;
	ref class AmfObject;
	ref class AmfArray;
	ref class AmfDictionary;

	[Windows::Foundation::Metadata::WebHostHidden]
	public interface class IAmfValue
	{
		property AmfValueType ValueType
		{
			AmfValueType get();
		}
		
		Platform::Array<uint8>^ Sequencify();
		Platform::Array<uint8>^ Sequencify( AmfEncodingType type );

		bool GetBoolean();
		float64 GetNumber();
		Platform::String^ GetString();
		Windows::Foundation::DateTime GetDate();
		Platform::Array<uint8>^ GetByteArray();
		Windows::Foundation::Collections::IVector<int32>^ GetVectorInt();
		Windows::Foundation::Collections::IVector<uint32>^ GetVectorUint();
		Windows::Foundation::Collections::IVector<float64>^ GetVectorDouble();
		Windows::Foundation::Collections::IVector<IAmfValue^>^ GetVectorObject();
		AmfObject^ GetObject();
		AmfArray^ GetArray();
		AmfDictionary^ GetDictionary();
	};

} } }