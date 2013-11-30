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
		AmfDictionary();

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

		// IAmfDictionary: read methods	
		virtual bool IndexOfPair( IAmfValue^ key, IAmfValue^ value, uint32* index );

		// IAmfDictionary: write methods
		virtual void SetPairAt( uint32 index, IAmfValue^ key, IAmfValue^ value );
		virtual void InsertPairAt( uint32 index, IAmfValue^ key, IAmfValue^ value );
		virtual void AppendPair( IAmfValue^ key, IAmfValue^ value );

		// IIterable
		virtual Windows::Foundation::Collections::IIterator<AmfPair^>^ First( );

		// IVector: read methods
		virtual AmfPair^ GetAt( uint32 index );
		virtual Windows::Foundation::Collections::IVectorView<AmfPair^>^ GetView( );
		virtual bool IndexOf( AmfPair^ value, uint32* index );

		// IVector: write methods
		virtual void SetAt( uint32 index, AmfPair^ value );
		virtual void InsertAt( uint32 index, AmfPair^ value );
		virtual void RemoveAt( uint32 index );
		virtual void Append( AmfPair^ value );
		virtual void RemoveAtEnd();
		virtual void Clear();

		// IVector: bulk transfer methods
		virtual uint32 GetMany( uint32 startIndex, Platform::WriteOnlyArray<AmfPair^>^ items );
		virtual void ReplaceAll( const Platform::Array<AmfPair^>^ items );

		// IStringable
#if !_WINDOWS_PHONE
		virtual Platform::String^ ToString() override sealed;
#endif

		static AmfDictionary^ Parse( const Platform::Array<uint8>^ input );
		static AmfDictionary^ Parse( const Platform::Array<uint8>^ input, AmfEncodingType type );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfDictionary^* result );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfDictionary^* result );

	internal:
		void SetData( std::vector<AmfPair^> data );

	public:
		// IAmfValue
		property AmfValueType ValueType
		{
			virtual AmfValueType get() { return ValueType_; }
		}

		// IVector
		property uint32 Size
		{
			virtual uint32 get() { return vector_->Size; }
		}

	private:
		AmfValueType ValueType_;
		Platform::Collections::Vector<AmfPair^>^ vector_;
	};

} } }
