#include "pch.h"
#include "AmfPair.h"

using namespace mntone::data::amf;
using namespace Mntone::Data::Amf;

AmfPair::AmfPair()
{ }

AmfPair::AmfPair( Windows::Foundation::Collections::IKeyValuePair<IAmfValue^, IAmfValue^>^ value ) :
	key_( std::move( value->Key ) ), value_( std::move( value->Value ) )
{ }

AmfPair::AmfPair( IAmfValue^ key, IAmfValue^ value ) :
	key_( std::move( key ) ), value_( std::move( value ) )
{ }

#if !_WINDOWS_PHONE
Platform::String^ AmfPair::ToString()
{
	const auto& key = Key->ToString();
	const auto& value = Value->ToString();

	std::wostringstream buf;
	buf.write( key->Data(), key->Length() );
	buf.write( L": ", 2 );
	buf.write( value->Data(), value->Length() );

	auto str = buf.str();
	return ref new Platform::String( str.c_str(), static_cast<uint32>( str.length() ) );
}
#endif