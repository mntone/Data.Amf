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

#if !_WINDOWS_PHONE8
Platform::String^ AmfPair::ToString()
{
	std::wstring buf;
	{
		const auto& key = Key->ToString();
		buf += std::wstring( key->Data(), key->Length() );
	}
	buf += L": ";
	{
		const auto& value = Value->ToString();
		buf += std::wstring( value->Data(), value->Length() );
	}

	return Platform::StringReference( buf.c_str(), buf.length() );
}
#endif