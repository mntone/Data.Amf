#pragma once
#include "IAmfValue.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::WebHostHidden]
	public interface class IAmfObject: IAmfValue
	{
		property Platform::String^ ClassName
		{
			Platform::String^ get( void );
			void set( Platform::String^ value );
		}
		property bool Externalizable
		{
			bool get( void );
			void set( bool value );
		}

		AmfValue^ GetNamedValue( Platform::String^ name );
		void SetNamedValue( Platform::String^ name, IAmfValue^ value );

		bool GetNamedBoolean( Platform::String^ name );
		float64 GetNamedDouble( Platform::String^ name );
		int32 GetNamedInteger( Platform::String^ name );
		Platform::String^ GetNamedString( Platform::String^ name );
		Windows::Foundation::DateTime GetNamedDate( Platform::String^ name );
		Platform::Array<uint8>^ GetNamedByteArray( Platform::String^ name );
		Windows::Foundation::Collections::IVector<int32>^ GetNamedVectorInt( Platform::String^ name );
		Windows::Foundation::Collections::IVector<uint32>^ GetNamedVectorUint( Platform::String^ name );
		Windows::Foundation::Collections::IVector<float64>^ GetNamedVectorDouble( Platform::String^ name );
		Windows::Foundation::Collections::IVector<IAmfValue^>^ GetNamedVectorObject( Platform::String^ name );
		AmfObject^ GetNamedObject( Platform::String^ name );
		AmfArray^ GetNamedArray( Platform::String^ name );
	};

} } }
