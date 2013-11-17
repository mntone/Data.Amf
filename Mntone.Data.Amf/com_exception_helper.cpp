#include "pch.h"
#include "com_exception_helper.h"
#include "corerror.h"

using namespace mntone::data::amf;
		
Platform::COMException^	com_exception_helper::create_invalid_operation_exception( Platform::String^ message )
{
	return ref new Platform::COMException( COR_E_INVALIDOPERATION, message );
}