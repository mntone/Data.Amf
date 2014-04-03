#pragma once
#include "IAmfValue.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::DualApiPartition( version = NTDDI_WIN8 )]
	[Windows::Foundation::Metadata::MarshalingBehavior( Windows::Foundation::Metadata::MarshalingType::Agile )]
	[Windows::Foundation::Metadata::Threading( Windows::Foundation::Metadata::ThreadingModel::Both )]
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class AmfValue sealed:
		public IAmfValue
	{
	public:
		AmfValue();

		// IAmfValue
		virtual Platform::Array<uint8>^ Sequencify();
		virtual Platform::Array<uint8>^ Sequencify( AmfEncodingType type );
		virtual bool GetBoolean();
		virtual float64 GetNumber();
		virtual Platform::String^ GetString();
		virtual Windows::Foundation::DateTime GetDate();
		virtual Platform::Array<uint8>^ GetByteArray();
		virtual Windows::Foundation::Collections::IVector<int32>^ GetVectorInt();
		virtual Windows::Foundation::Collections::IVector<uint32>^ GetVectorUint();
		virtual Windows::Foundation::Collections::IVector<float64>^ GetVectorDouble();
		virtual Windows::Foundation::Collections::IVector<IAmfValue^>^ GetVectorObject();
		virtual AmfObject^ GetObject();
		virtual AmfArray^ GetArray();
		virtual AmfDictionary^ GetDictionary();

		// IStringable
#if !_WINDOWS_PHONE
		virtual Platform::String^ ToString() override sealed;
#endif

		static AmfValue^ CreateUndefinedValue();
		static AmfValue^ CreateBooleanValue( bool input );
		static AmfValue^ CreateNumberValue( float64 input );
		static AmfValue^ CreateStringValue( Platform::String^ input );
		static AmfValue^ CreateDateValue( Windows::Foundation::DateTime input );
		static AmfValue^ CreateXmlValue( Platform::String^ input );
		static AmfValue^ CreateByteArrayValue( const Platform::Array<uint8>^ input );
		static AmfValue^ CreateVectorIntValue( Windows::Foundation::Collections::IVector<int32>^ input );
		static AmfValue^ CreateVectorUintValue( Windows::Foundation::Collections::IVector<uint32>^ input );
		static AmfValue^ CreateVectorDoubleValue( Windows::Foundation::Collections::IVector<float64>^ input );
		static AmfValue^ CreateVectorObjectValue( Windows::Foundation::Collections::IVector<IAmfValue^>^ input );

		static AmfValue^ Parse( const Platform::Array<uint8>^ input );
		static AmfValue^ Parse( const Platform::Array<uint8>^ input, AmfEncodingType type );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfValue^* result );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfValue^* result );

	internal:
		void SetData( Platform::Object^ input );

		static AmfValue^ CreateByteArrayValue( std::vector<uint8> input );
		static AmfValue^ CreateVectorObjectValue();

	public:
		// IAmfValue
		property AmfValueType ValueType
		{
			virtual AmfValueType get() { return ValueType_; }
		}

	private:
		AmfValueType ValueType_;
		Platform::Object^ value_;
	};

} } }
