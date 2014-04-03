#pragma once

namespace Mntone { namespace Data { namespace Amf {

	[Windows::Foundation::Metadata::WebHostHidden]
	public enum class AmfValueType
	{
		Undefined,
		Null,
		Boolean,
		Number,
		String,
		Date,
		Xml,
		ByteArray,
		VectorInt,
		VectorUint,
		VectorDouble,
		VectorObject,
		Object,
		EcmaArray,
		Array,
		Dictionary,
	};

} } }
