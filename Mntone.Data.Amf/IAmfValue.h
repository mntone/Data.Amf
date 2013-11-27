#pragma once
#include "AmfEncodingType.h"
#include "AmfValueType.h"

namespace Mntone { namespace Data { namespace Amf {

	ref class AmfValue;
	ref class AmfObject;
	ref class AmfArray;

	[Windows::Foundation::Metadata::WebHostHidden]
	public interface class IAmfValue
	{
		property AmfValueType ValueType
		{
			AmfValueType get( void );
		}
		
		Platform::Array<uint8>^ Sequencify( void );
		Platform::Array<uint8>^ Sequencify( AmfEncodingType type );

		bool GetBoolean( void );
		float64 GetNumber( void );
		Platform::String^ GetString( void );
		Windows::Foundation::DateTime GetDate( void );
		Platform::Array<uint8>^ GetByteArray( void );
		Windows::Foundation::Collections::IVector<int32>^ GetVectorInt( void );
		Windows::Foundation::Collections::IVector<uint32>^ GetVectorUint( void );
		Windows::Foundation::Collections::IVector<float64>^ GetVectorDouble( void );
		Windows::Foundation::Collections::IVector<IAmfValue^>^ GetVectorObject( void );
		AmfObject^ GetObject( void );
		AmfArray^ GetArray( void );
	};

} } }