#include "pch.h"
#include "com_exception_helper.h"
#include <corerror.h>

using namespace mntone::data::amf;
		
Platform::Exception^ com_exception_helper::create_invalid_operation_exception( Platform::String^ message )
{
	return Platform::Exception::CreateException( COR_E_INVALIDOPERATION, message );
}