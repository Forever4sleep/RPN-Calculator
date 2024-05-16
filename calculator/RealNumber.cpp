#include "RealNumber.h"
#include <string>
#include "exception.h"

RealNumber::RealNumber(float _data)
{
    this->_data = _data;
}

RealNumber::RealNumber()
{
    this->_data = 0;
}

RealNumber RealNumber::operator+(RealNumber& right)
{
    return RealNumber(this->_data + right._data);
}

RealNumber RealNumber::operator-(RealNumber& right)
{
    return RealNumber(this->_data - right._data);
}

RealNumber RealNumber::operator*(RealNumber& right)
{
    return RealNumber(this->_data * right._data);
}

RealNumber RealNumber::operator/(RealNumber& right)
{
    if (right._data == 0)
        throw own_exception("trying to divide by zero? you are a goofy ass nigger", own_exception::exception_type::ZERO_DIVISION);
    return RealNumber(this->_data / right._data);
}

RealNumber RealNumber::operator^(RealNumber& right)
{
    if (std::floor(right._data) != right._data)
        throw own_exception("Can't raise real number to a fucked up power", own_exception::exception_type::BAD_POWER);
    
    return RealNumber(std::pow(this->_data, right._data));
}

std::string RealNumber::get_str()
{
    return std::to_string(_data);
}

RealNumber RealNumber::from_json(std::string key, nlohmann::json data)
{
    return RealNumber(data[key].get<float>());
}

std::istream& operator>>(std::istream& in, RealNumber& c)
{
    in >> c._data;
    return in;
}

std::ostream& operator<<(std::ostream& out, RealNumber& r)
{
    out << r._data;
    return out;
}
