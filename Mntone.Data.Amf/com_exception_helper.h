#pragma once

namespace mntone { namespace data { namespace amf {

	class com_exception_helper
	{
	public:
		static Platform::Exception^ create_invalid_operation_exception( Platform::String^ message );
	};

} } }