#pragma once
#include "pch.h"
#include "IAmfValue.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::WebHostHidden]
	public interface class IAmfObject: IAmfValue
	{
		AmfValue^ GetNamedValue( Platform::String^ name );
		void SetNamedValue( Platform::String^ name, IAmfValue^ value );

		bool GetNamedBoolean( Platform::String^ name );
		float64 GetNamedDouble( Platform::String^ name );
		int32 GetNamedInteger( Platform::String^ name );
		Platform::String^ GetNamedString( Platform::String^ name );
		uint16 GetNamedReference( Platform::String^ name );
		Windows::Foundation::DateTime GetNamedDate( Platform::String^ name );
		AmfObject^ GetNamedObject( Platform::String^ name );
		AmfArray^ GetNamedArray( Platform::String^ name );
	};

} } }
