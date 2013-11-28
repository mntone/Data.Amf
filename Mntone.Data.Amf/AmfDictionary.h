#pragma once
#include "IAmfDictionary.h"
#include "AmfPair.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::DualApiPartition( version = NTDDI_WIN8 )]
	[Windows::Foundation::Metadata::MarshalingBehavior( Windows::Foundation::Metadata::MarshalingType::Agile )]
	[Windows::Foundation::Metadata::Threading( Windows::Foundation::Metadata::ThreadingModel::Both )]
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class AmfDictionary sealed:
		public IAmfDictionary
	{
	public:
		AmfDictionary( void );

		// IAmfValue
		virtual Platform::Array<uint8>^ Sequencify( void );
		virtual Platform::Array<uint8>^ Sequencify( AmfEncodingType type );
		virtual bool GetBoolean( void );
		virtual float64 GetNumber( void );
		virtual Platform::String^ GetString( void );
		virtual Windows::Foundation::DateTime GetDate( void );
		virtual Platform::Array<uint8>^ GetByteArray( void );
		virtual Windows::Foundation::Collections::IVector<int32>^ GetVectorInt( void );
		virtual Windows::Foundation::Collections::IVector<uint32>^ GetVectorUint( void );
		virtual Windows::Foundation::Collections::IVector<float64>^ GetVectorDouble( void );
		virtual Windows::Foundation::Collections::IVector<IAmfValue^>^ GetVectorObject( void );
		virtual AmfObject^ GetObject( void );
		virtual AmfArray^ GetArray( void );
		virtual AmfDictionary^ GetDictionary( void );

		// IAmfDictionary: read methods	
		virtual bool IndexOfPair( IAmfValue^ key, IAmfValue^ value, uint32* index );

		// IAmfDictionary: write methods
		virtual void SetPairAt( uint32 index, IAmfValue^ key, IAmfValue^ value );
		virtual void InsertPairAt( uint32 index, IAmfValue^ key, IAmfValue^ value );
		virtual void AppendPair( IAmfValue^ key, IAmfValue^ value );

		// IIterable
		virtual Windows::Foundation::Collections::IIterator<IAmfPair^>^ First( void );

		// IVector: read methods
		virtual IAmfPair^ GetAt( uint32 index );
		virtual Windows::Foundation::Collections::IVectorView<IAmfPair^>^ GetView( void );
		virtual bool IndexOf( IAmfPair^ value, uint32* index );

		// IVector: write methods
		virtual void SetAt( uint32 index, IAmfPair^ value );
		virtual void InsertAt( uint32 index, IAmfPair^ value );
		virtual void RemoveAt( uint32 index );
		virtual void Append( IAmfPair^ value );
		virtual void RemoveAtEnd( void );
		virtual void Clear( void );

		// IVector: bulk transfer methods
		virtual uint32 GetMany( uint32 startIndex, Platform::WriteOnlyArray<IAmfPair^>^ items );
		virtual void ReplaceAll( const Platform::Array<IAmfPair^>^ items );

		// IStringable
#if !_WINDOWS_PHONE
		virtual Platform::String^ ToString( void ) override sealed;
#endif

		static AmfDictionary^ Parse( const Platform::Array<uint8>^ input );
		static AmfDictionary^ Parse( const Platform::Array<uint8>^ input, AmfEncodingType type );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfDictionary^* result );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfDictionary^* result );

	internal:
		void SetData( std::vector<IAmfPair^> data );

	public:
		// IAmfValue
		property AmfValueType ValueType
		{
			virtual AmfValueType get( void ) { return ValueType_; }
		}

		// IVector
		property uint32 Size
		{
			virtual uint32 get( void ) { return vector_->Size; }
		}

	private:
		AmfValueType ValueType_;
		Platform::Collections::Vector<IAmfPair^>^ vector_;
	};

} } }
