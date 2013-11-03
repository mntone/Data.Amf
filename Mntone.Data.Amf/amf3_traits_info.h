#pragma once

namespace Mntone { namespace Data { namespace Amf {

	struct amf3_traits_info
	{
		Platform::String^ class_name;
		bool dynamic, externalizable;
		std::vector<Platform::String^> properites;
	};

} } }
