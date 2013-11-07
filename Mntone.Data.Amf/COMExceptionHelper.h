#pragma once

namespace Mntone {namespace Data {namespace Amf {

	class COMExceptionHelper
	{

	public:

		static Platform::COMException^ CreateInvalidOperationException(Platform::String^ message);
	};


}}}

