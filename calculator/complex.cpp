#include "complex.h"
#include <math.h>
#include <string>
#include "exception.h"
#define M_PI 3.14159265358979323846


ComplexNumber::ComplexNumber(double real, double imag)
{
    this->real = real;
    imaginary = imag;
}

ComplexNumber::ComplexNumber()
{
}

ComplexNumber::ComplexNumber(double real)
{
    this->real = real;
}

float ComplexNumber::get_angle()
{
    float x = std::abs(real), y = std::abs(imaginary);
    if (x > 0 && y >= 0) return atan(y / x);
    if (x < 0 && y >= 0) return M_PI - atan(y / x);
    if (x < 0 && y < 0) return M_PI + atan(y / x);
    if (x > 0 && y < 0) return 2 * M_PI - atan(y / x);
    if (x == 0 && y > 0) return M_PI / 2;
    if (x == 0 && y < 0) return 3 * M_PI / 2;
}

ComplexNumber ComplexNumber::operator+(ComplexNumber& right)
{
    return ComplexNumber(this->real + right.real, this->imaginary + right.imaginary);
}

ComplexNumber ComplexNumber::operator-(ComplexNumber& right)
{
    return ComplexNumber(this->real -right.real, this->imaginary -right.imaginary);
}

ComplexNumber ComplexNumber::operator*(ComplexNumber& right)
{
    return ComplexNumber(this->real * right.real - this->imaginary * right.imaginary, this->real * right.imaginary + this->imaginary * right.real);
}

ComplexNumber ComplexNumber::operator/(ComplexNumber& right)
{
    return ComplexNumber(
        (real * right.real + imaginary * right.imaginary)/(right.real * right.real + right.imaginary * right.imaginary),
        (imaginary * right.real - real * right.imaginary)/(right.real * right.real + right.imaginary * right.imaginary));
}

ComplexNumber ComplexNumber::operator^(ComplexNumber& right)
{
    if (right.imaginary != 0 || std::floor(right.real) != right.real)
        throw own_exception("asd", own_exception::exception_type::BAD_POWER);

    float length = sqrt(real * real + imaginary * imaginary);
    auto radius_n = std::pow(length, right.real);

    return ComplexNumber(radius_n * cos(right.real * get_angle()), radius_n * sin(right.real * get_angle()));
}

std::string ComplexNumber::get_str()
{
    std::string res;
    if (real != 0) res += std::to_string(real);
    if (imaginary != 0) if (imaginary > 0) res += " + " + std::to_string(imaginary) + "i"; else res += " - " + std::to_string(0 - imaginary) + "i";

    return res;
}

ComplexNumber ComplexNumber::from_json(std::string key, nlohmann::json data)
{
    return ComplexNumber(data[key][0].get<double>(), data[key][1].get<double>());
}

double get_input(std::istream& in)
{
    std::string s; std::getline(in, s);
    s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
    
    double x = std::stof(s);
    return x;
}

std::istream& operator>>(std::istream& in, ComplexNumber& r)
{
 /*   double real = get_input(in);
    double im = get_input(in);
 */  // r.real = real;
   // r.imaginary = im;
    in >> r.real;
    in >> r.imaginary;
    return in;
}

std::ostream& operator<<(std::ostream& out, ComplexNumber& r)
{
    if (r.real != 0)
        out << r.real << " ";
    if (r.imaginary != 0)
        if (r.imaginary < 0) out << "- " << std::abs(r.imaginary) << "i";
        else out << "+ " << r.imaginary << "i";

    return out;
}
