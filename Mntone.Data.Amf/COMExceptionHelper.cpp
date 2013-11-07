#include "pch.h"
#include "COMExceptionHelper.h"
#include "corerror.h"

namespace Mntone {namespace Data {namespace Amf {
			

		
    Platform::COMException^	COMExceptionHelper::CreateInvalidOperationException(Platform::String^ message){
		
		return ref new Platform::COMException(COR_E_INVALIDOPERATION, message);
	}
}}}
