#pragma once

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
		Date,
		Xml,
		Object,
		EcmaArray,
		Array,
	};

} } }
