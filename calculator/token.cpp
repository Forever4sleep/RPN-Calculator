#include "token.h"
#include "exception.h"

Token::Token(std::string val) : _value(val)
{
}

Token::Token(char value)
{
    _value = value;
}

bool Token::check_if_numeric()
{
    for (auto s : _value)  if (!isdigit(s) && s != '.') return false;
    return true;
}

int Token::get_precedence_level()
{
    if (_value == "(" || _value == ")") return 0;
    if (_value == "^") return 3;
    if (_value == "*" || _value == "/") return 2;
    if (_value == "+" || _value == "-") return 1;

            throw own_exception("invalid operator", own_exception::exception_type::BAD_POWER);; //undefined
}

bool Token::check_if_operator()
{
    return !(_value != " " && _value != ")" && _value != "(" && _value != ")" && _value != "+" && _value != "-" && _value != "/" && _value  != "^" && _value != "*");
}

std::string Token::get_value()
{
    return _value;
}

void Token::add_to_value(char k)
{
    _value = _value + k;
}

void Token::change_value(string s)
{
    _value = s;
}

bool Token::empty()
{
    return _value.empty();
}
