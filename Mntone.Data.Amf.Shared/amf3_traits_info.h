#pragma once

namespace mntone { namespace data { namespace amf {

	struct amf3_traits_info
	{
		Platform::String^ class_name;
		bool dynamic, externalizable;
		std::vector<Platform::String^> properites;
	};

} } }
