#pragma once
#include "IAmfValue.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::DualApiPartition( version = NTDDI_WIN8 )]
	[Windows::Foundation::Metadata::MarshalingBehavior( Windows::Foundation::Metadata::MarshalingType::Agile )]
	[Windows::Foundation::Metadata::Threading( Windows::Foundation::Metadata::ThreadingModel::Both )]
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class AmfObject sealed:
		public IAmfValue,
		public Windows::Foundation::Collections::IMap<Platform::String^, IAmfValue^>
	{
	public:
		AmfObject( void );
		AmfObject( Platform::String^ className );

		// IAmfValue
		virtual Platform::Array<uint8>^ Sequencify( void );
		virtual Platform::Array<uint8>^ Sequencify( AmfEncodingType type );
		virtual bool GetBoolean( void );
		virtual float64 GetDouble( void );
		virtual int32 GetInteger( void );
		virtual Platform::String^ GetString( void );
		virtual Windows::Foundation::DateTime GetDate( void );
		virtual Platform::Array<uint8>^ GetByteArray( void );
		virtual Windows::Foundation::Collections::IVector<int32>^ GetVectorInt( void );
		virtual Windows::Foundation::Collections::IVector<uint32>^ GetVectorUint( void );
		virtual Windows::Foundation::Collections::IVector<float64>^ GetVectorDouble( void );
		virtual Windows::Foundation::Collections::IVector<IAmfValue^>^ GetVectorObject( void );
		virtual AmfObject^ GetObject( void );
		virtual AmfArray^ GetArray( void );

		// AmfObject
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
#if !_WINDOWS_PHONE
		virtual Platform::String^ ToString( void ) override sealed;
#endif

		static AmfObject^ CreateEcmaArray( void );

		static AmfObject^ Parse( const Platform::Array<uint8>^ input );
		static AmfObject^ Parse( const Platform::Array<uint8>^ input, AmfEncodingType type );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfObject^* result );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfObject^* result );

	internal:
#if _WINDOWS_PHONE
		void SetData( std::map<Platform::String^, IAmfValue^> data );
#else
		void SetData( std::unordered_map<Platform::String^, IAmfValue^> data );
#endif

	public:
		// IAmfValue
		property AmfValueType ValueType
		{
			virtual AmfValueType get( void ) { return ValueType_; }
		}

		// AmfObject
		property Platform::String^ ClassName
		{
			Platform::String^ get( void ) { return ClassName_; }
			void set( Platform::String^ value ) { ClassName_ = value; }
		}
		property bool Externalizable
		{
			bool get( void ) { return Externalizable_; }
			void set( bool value ) { Externalizable_ = value; }
		}

		// IMap
		property uint32 Size
		{
			virtual uint32 get( void ) { return map_->Size; }
		}

	private:
		AmfValueType ValueType_;
#if _WINDOWS_PHONE
		Platform::Collections::Map<Platform::String^, IAmfValue^>^ map_;
#else
		Platform::Collections::UnorderedMap<Platform::String^, IAmfValue^>^ map_;
#endif

		Platform::String^ ClassName_;
		bool Externalizable_;
	};

} } }
