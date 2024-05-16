#pragma once
#include <iostream>
class own_exception : std::runtime_error
{
public:
	enum class exception_type
	{
		ZERO_DIVISION,
		MATRIX_DIVISION,
		BAD_SIZE,
		BAD_POWER,
		BAD_FORMULA,
		BAD_JSON,
	};
	const char* what() const override;
	own_exception(const char* message, exception_type type);
private:
	const char* _message;
	exception_type _type;
};