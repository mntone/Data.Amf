#pragma once

namespace Mntone { namespace Data { namespace Amf {

	ref class COMExceptionHelper
	{
	public:
		static Platform::COMException^ CreateInvalidOperationException( Platform::String^ message );
	};

} } }