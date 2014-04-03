#pragma once
#include <exception>

namespace mntone { namespace data { namespace amf {

	class amf_exception: public std::exception
	{
	public:
		amf_exception( Platform::String^ message ):
			exception(),
			message_( message )
		{ }

	public:
		Platform::String^ get_message() const { return message_; }

	private:
		Platform::String^ message_;
	};

} } }