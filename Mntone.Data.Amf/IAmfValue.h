#pragma once
#include "pch.h"
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
		
		Platform::Array<uint8>^ Sequenceify( void );
		Platform::Array<uint8>^ Sequenceify( AmfEncodingType type );

		bool GetBoolean( void );
		float64 GetDouble( void );
		int32 GetInteger( void );
		Platform::String^ GetString( void );
		uint16 GetReference( void );
		Windows::Foundation::DateTime GetDate( void );
		AmfObject^ GetObject( void );
		AmfArray^ GetArray( void );
	};

} } }
