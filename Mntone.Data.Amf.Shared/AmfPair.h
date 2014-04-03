#pragma once
#include "IAmfPair.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::DualApiPartition( version = NTDDI_WIN8 )]
	[Windows::Foundation::Metadata::MarshalingBehavior( Windows::Foundation::Metadata::MarshalingType::Agile )]
	[Windows::Foundation::Metadata::Threading( Windows::Foundation::Metadata::ThreadingModel::Both )]
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class AmfPair sealed:
		public IAmfPair
	{
	public:
		AmfPair();
		AmfPair( Windows::Foundation::Collections::IKeyValuePair<IAmfValue^, IAmfValue^>^ value );
		AmfPair( IAmfValue^ key, IAmfValue^ value );

		// IStringable
#if !_WINDOWS_PHONE
		virtual Platform::String^ ToString() override sealed;
#endif

	public:
		property AmfValueType KeyType
		{
			virtual AmfValueType get() { return key_->ValueType; }
		}
		property IAmfValue^ Key
		{
			virtual IAmfValue^ get() { return key_; }
			virtual void set( IAmfValue^ value ) { key_ = std::move( value ); }
		}
		property AmfValueType ValueType
		{
			virtual AmfValueType get() { return value_->ValueType; }
		}
		property IAmfValue^ Value
		{
			virtual IAmfValue^ get() { return value_; }
			virtual void set( IAmfValue^ value ) { value_ = std::move( value ); }
		}

	private:
		IAmfValue^ key_;
		IAmfValue^ value_;
	};

} } }
