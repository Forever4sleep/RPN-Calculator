#pragma once
#include "icalculable.h"
#include "igettable.h"
#include "ijsonpresentable.h"

class Fraction : public ICalculable<Fraction>, public IGettable, public IJSONPresentable<Fraction>
{
public:
	Fraction(int numerator, int denominator);
	Fraction(int numerator);
	Fraction();
	virtual Fraction operator+(Fraction& right) override;
	virtual Fraction operator-(Fraction& right) override;
	virtual Fraction operator*(Fraction& right) override;
	virtual Fraction operator/(Fraction& right) override;
	virtual Fraction operator^(Fraction& right) override;

	virtual std::string get_str() override;
	friend std::istream& operator>>(std::istream& in, Fraction& r);
	friend std::ostream& operator<<(std::ostream& out, Fraction& r);
	virtual Fraction from_json(std::string key, nlohmann::json data) override;
private:
	int _numerator = 0, _denominator = 1;
};

