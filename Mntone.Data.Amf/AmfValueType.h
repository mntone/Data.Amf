#pragma once
#include "pch.h"

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::WebHostHidden]
	public enum class AmfValueType
	{
		Undefined,
		Null,
		Boolean,
		Double,
		Integer,
		String,
		Reference,
		Date,
		Xml,
		Object,
		Array,
	};

} } }