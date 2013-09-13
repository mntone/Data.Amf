#pragma once
#include "pch.h"

namespace Mntone { namespace Data { namespace Amf {

	enum amf3_type: uint8
	{
		amf3_undefined = 0x00,
		amf3_null = 0x01,
		amf3_false = 0x02,
		amf3_true = 0x03,
		amf3_interger = 0x04,
		amf3_double = 0x05,
		amf3_string = 0x06,
		amf3_xml_document = 0x07,
		amf3_date = 0x08,
		amf3_array = 0x09,
		amf3_object = 0x0a,
		amf3_xml = 0x0b,
		amf3_byte_array = 0x0c,
		amf3_vector_int = 0x0d,
		amf3_vector_uint = 0x0e,
		amf3_vector_dobule = 0x0f,
		amf3_vector_object = 0x10,
		amf3_dictionary = 0x11,
	};

} } }
