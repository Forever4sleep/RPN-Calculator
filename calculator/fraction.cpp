#include "fraction.h"
#include <string>
#include "exception.h"


Fraction::Fraction(int numerator, int denominator)
{
    this->_numerator = numerator;
    this->_denominator = denominator;
    if (denominator == 0)         throw own_exception("Bad denominator (=0)", own_exception::exception_type::ZERO_DIVISION);

    if (numerator != 0)
    {
        if (denominator < 0)
        {
            this->_denominator = std::abs(denominator);
            this->_numerator *= -1;
        }

        numerator = std::abs(numerator);
        denominator = std::abs(denominator);
        
        int gcd = 1;
        while (numerator > 0 && denominator > 0)
        {
            if (std::max(numerator, denominator) == numerator)
                numerator = numerator % denominator;
            else denominator = denominator % numerator;
            gcd = std::max(numerator, denominator);
        }
        this->_denominator /= gcd;
        this->_numerator /= gcd;
    }
}

Fraction::Fraction(int numerator)
{
    this->_numerator = numerator;
    this->_denominator = 1;
}

Fraction::Fraction()
{
}

Fraction Fraction::operator+(Fraction& right)
{
    return Fraction(_numerator * right._denominator + _denominator * right._numerator, _denominator * right._denominator);
}

Fraction Fraction::operator-(Fraction& right)
{
    return Fraction(_numerator * right._denominator - _denominator * right._numerator, _denominator * right._denominator);
}

Fraction Fraction::operator*(Fraction& right)
{
    return Fraction(_numerator * right._numerator, _denominator * right._denominator);
}   

Fraction Fraction::operator/(Fraction& right)
{
    return Fraction(_numerator * right._denominator, _denominator * right._numerator);
}

Fraction Fraction::operator^(Fraction& right)
{
    if (right._denominator != 1)
    {
        throw own_exception("Bad power", own_exception::exception_type::BAD_POWER);
    }
    return Fraction((int)std::pow(this->_numerator, right._numerator), (int)std::pow(this->_denominator, right._numerator));
}

std::string Fraction::get_str()
{
    std::string s;
  //  if (_numerator < 0 && _denominator < 0 || _numerator > 0 && _denominator > 0)
    s += std::to_string(_numerator) + "/" + std::to_string(_denominator);
    //else s += "-"  + std::to_string(_numerator) + "/" + std::to_string(_denominator);
    return s;
}

Fraction Fraction::from_json(std::string key, nlohmann::json data)
{
    return Fraction(data[key][0].get<int>(), data[key][1].get<int>());
}

std::istream& operator>>(std::istream& in, Fraction& r)
{
 /*   std::string s;
    std::getline(in, s);
    int x = 0, y = 1;
    std::string number;
    bool saw_space = false; 
    for (auto character : s)
    {
        if (character != ' ')
            number += character;
        else if (!saw_space)
        {
            x = std::stoi(number);
            number = "";
            saw_space = true;
        }
    }
    if (!number.empty()) if (x == 0) x = std::stoi(number); else y = std::stoi(number);
    std::cout << "x = " << x << " y = " << y << std::endl;*/
    float x, y;
    in >> x; in >> y;
    r = Fraction(x, y);
    return in;
}

std::ostream& operator<<(std::ostream& out, Fraction& r)
{
    if (r._numerator < 0 && r._denominator < 0 || r._numerator > 0 && r._denominator > 0)
        out << r._numerator << "/" << r._denominator;
    else out << "-" << r._numerator << "/" << r._denominator;

    return out;
}
