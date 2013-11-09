#include "pch.h"
#include "COMExceptionHelper.h"
#include "corerror.h"

using namespace Mntone::Data::Amf;
		
Platform::COMException^	COMExceptionHelper::CreateInvalidOperationException( Platform::String^ message )
{
	return ref new Platform::COMException( COR_E_INVALIDOPERATION, message );
}