#include "exception.h"
#include <string>

const char* own_exception::what() const
{
	return _message;
	/*switch (_type)
	{
	case exception_type::MATRIX_DIVISION:
		return "You cannot divide matrices";
	case exception_type::BAD_SIZE:
		return "Bad matrix sizes";
	case exception_type::BAD_POWER:
		return "Power must be natural and non-negative";
	case exception_type::BAD_FORMULA:
		return "Error in formula";
	}*/

	//return "Unknown";
}

own_exception::own_exception(const char* message, exception_type type) : std::runtime_error(message)
{
	_type = type;
	_message = message;
}
