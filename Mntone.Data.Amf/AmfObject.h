#pragma once
#include "IAmfObject.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::DualApiPartition( version = NTDDI_WIN8 )]
	[Windows::Foundation::Metadata::MarshalingBehavior( Windows::Foundation::Metadata::MarshalingType::Agile )]
	[Windows::Foundation::Metadata::Threading( Windows::Foundation::Metadata::ThreadingModel::Both )]
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class AmfObject sealed:
		public IAmfObject,
		public Windows::Foundation::Collections::IMap<Platform::String^, IAmfValue^>
	{
	public:
		AmfObject( void );

		// IAmfValue
		virtual Platform::Array<uint8>^ Sequenceify( void );
		virtual Platform::Array<uint8>^ Sequenceify( AmfEncodingType type );
		virtual bool GetBoolean( void );
		virtual float64 GetDouble( void );
		virtual int32 GetInteger( void );
		virtual Platform::String^ GetString( void );
		virtual Windows::Foundation::DateTime GetDate( void );
		virtual AmfObject^ GetObject( void );
		virtual AmfArray^ GetArray( void );

		// IAmfObject
		virtual AmfValue^ GetNamedValue( Platform::String^ name );
		virtual void SetNamedValue( Platform::String^ name, IAmfValue^ value );
		virtual bool GetNamedBoolean( Platform::String^ name );
		virtual float64 GetNamedDouble( Platform::String^ name );
		virtual int32 GetNamedInteger( Platform::String^ name );
		virtual Platform::String^ GetNamedString( Platform::String^ name );
		virtual Windows::Foundation::DateTime GetNamedDate( Platform::String^ name );
		virtual AmfObject^ GetNamedObject( Platform::String^ name );
		virtual AmfArray^ GetNamedArray( Platform::String^ name );

		// IIterator
		virtual Windows::Foundation::Collections::IIterator<Windows::Foundation::Collections::IKeyValuePair<Platform::String^, IAmfValue^>^>^ First( void );

		// IMap: read methods
		virtual IAmfValue^ Lookup( Platform::String^ key );
		virtual bool HasKey( Platform::String^ key );
		virtual Windows::Foundation::Collections::IMapView<Platform::String^, IAmfValue^>^ GetView( void );

		// IMap: write methods
		virtual bool Insert( Platform::String^ key, IAmfValue^ value );
		virtual void Remove( Platform::String^ key );
		virtual void Clear( void );

		// IStringable
		virtual Platform::String^ ToString( void ) override sealed;

		static AmfObject^ CreateTypedObject( Platform::String^ className );

		static AmfObject^ Parse( const Platform::Array<uint8>^ input );
		static AmfObject^ Parse( const Platform::Array<uint8>^ input, AmfEncodingType type );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfObject^* result );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfObject^* result );

	internal:
		void SetData( std::unordered_map<Platform::String^, IAmfValue^> data );

	public:
		// IAmfValue
		property AmfValueType ValueType
		{
			virtual AmfValueType get( void ) { return ValueType_; }
		}

		// IAmfObject
		property Platform::String^ ClassName
		{
			virtual Platform::String^ get( void ) { return ClassName_; }
			virtual void set( Platform::String^ value ) { ClassName_ = value; }
		}

		// IMap
		property uint32 Size
		{
			virtual uint32 get( void ) { return map_->Size; }
		}

	private:
		AmfValueType ValueType_;
		Platform::Collections::UnorderedMap<Platform::String^, IAmfValue^>^ map_;

		Platform::String^ ClassName_;
	};

} } }
