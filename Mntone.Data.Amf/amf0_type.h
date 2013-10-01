#pragma once

namespace Mntone { namespace Data { namespace Amf {

	enum amf0_type: uint8
	{
		amf0_number = 0x00,
		amf0_boolean = 0x01,
		amf0_string = 0x02,
		amf0_object = 0x03,
		//amf0_movie_clip = 0x04, // reserved
		amf0_null = 0x05,
		amf0_undefined = 0x06,
		amf0_reference = 0x07,
		amf0_ecma_array = 0x08,
		//amf0_object_end = 0x09, // no use
		amf0_strict_array = 0x0a,
		amf0_date = 0x0b,
		amf0_long_string = 0x0c,
		//amf0_unsupported = 0x0d, // no use
		//amf0_recordset = 0x0e, // reserved
		amf0_xml_document = 0x0f,
		amf0_typed_object = 0x10,
		//amf0_avmplus_object = 0x11, // no support

		// original type
		_amf0_flexible_array = 0x80,
	};

} } }
