#pragma once
#include "icalculable.h"
#include "igettable.h"
#include <iostream>
#include "ijsonpresentable.h"
class ComplexNumber : public ICalculable<ComplexNumber>, public IGettable,
	public IJSONPresentable<ComplexNumber>
{
public:
	ComplexNumber(double real, double imag);
	ComplexNumber(double real);
	ComplexNumber();

	float get_angle();
	virtual ComplexNumber operator+(ComplexNumber& right) override;
	virtual ComplexNumber operator-(ComplexNumber& right) override;
	virtual ComplexNumber operator*(ComplexNumber& right) override;
	virtual ComplexNumber operator/(ComplexNumber& right) override;
	virtual ComplexNumber operator^(ComplexNumber& right) override;

	virtual std::string get_str();

	friend std::istream& operator>>(std::istream& in, ComplexNumber& r);
	friend std::ostream& operator<<(std::ostream& out, ComplexNumber& r);

	virtual ComplexNumber from_json(std::string key, nlohmann::json data);
private:
	double real = 0, imaginary = 0;
};

