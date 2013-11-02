#pragma once
#include "IAmfArray.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::DualApiPartition( version = NTDDI_WIN8 )]
	[Windows::Foundation::Metadata::MarshalingBehavior( Windows::Foundation::Metadata::MarshalingType::Agile )]
	[Windows::Foundation::Metadata::Threading( Windows::Foundation::Metadata::ThreadingModel::Both )]
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class AmfArray sealed:
		public IAmfArray,
		public Windows::Foundation::Collections::IVector<IAmfValue^>
	{
	public:
		AmfArray( void );

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

		// IAmfArray
		virtual bool GetBooleanAt( uint32 index );
		virtual float64 GetDoubleAt( uint32 index );
		virtual int32 GetIntegerAt( uint32 index );
		virtual Platform::String^ GetStringAt( uint32 index );
		virtual Windows::Foundation::DateTime GetDateAt( uint32 index );
		virtual AmfObject^ GetObjectAt( uint32 index );
		virtual AmfArray^ GetArrayAt( uint32 index );

		// IIterable
		virtual Windows::Foundation::Collections::IIterator<IAmfValue^>^ First( void );

		// IVector: read methods
		virtual IAmfValue^ GetAt( uint32 index );
		virtual Windows::Foundation::Collections::IVectorView<IAmfValue^>^ GetView( void );
		virtual bool IndexOf( IAmfValue^ value, uint32 *index );

		// IVector: write methods
		virtual void SetAt( uint32 index, IAmfValue^ value );
		virtual void InsertAt( uint32 index, IAmfValue^ value );
		virtual void RemoveAt( uint32 index );
		virtual void Append( IAmfValue^ value );
		virtual void RemoveAtEnd( void );
		virtual void Clear( void );

		// IVector: bulk transfer methods
		virtual uint32 GetMany( uint32 startIndex, Platform::WriteOnlyArray<IAmfValue^>^ items );
		virtual void ReplaceAll( const Platform::Array<IAmfValue^>^ items );

		// IStringable
		virtual Platform::String^ ToString( void ) override sealed;

		static AmfArray^ CreateStrictArray( void );

		static AmfArray^ Parse( const Platform::Array<uint8>^ input );
		static AmfArray^ Parse( const Platform::Array<uint8>^ input, AmfEncodingType type );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfArray^* result );
		static bool TryParse( const Platform::Array<uint8>^ input, AmfEncodingType type, AmfArray^* result );

	internal:
		void SetData( std::vector<IAmfValue^> data );

	public:
		// IAmfValue
		property AmfValueType ValueType
		{
			virtual AmfValueType get( void ) { return _ValueType; }
		}

		// IVector
		property uint32 Size
		{
			virtual uint32 get( void ) { return _vector->Size; }
		}

	internal:
		property bool Strict
		{
			bool get( void ) { return _Strict; }
		}

	private:
		AmfValueType _ValueType;
		Platform::Collections::Vector<IAmfValue^>^ _vector;

		bool _Strict;
	};

} } }
