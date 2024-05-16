#pragma once
#include "icalculable.h"
#include <iostream>
#include "igettable.h"
#include "ijsonpresentable.h"

class RealNumber : public ICalculable<RealNumber>, public IJSONPresentable<RealNumber>
{
public:
	RealNumber(float _data);
	RealNumber();

	virtual RealNumber operator+(RealNumber& right) override;
	virtual RealNumber operator-(RealNumber& right) override;
	virtual RealNumber operator*(RealNumber& right) override;
	virtual RealNumber operator/(RealNumber& right) override;
	virtual RealNumber operator^(RealNumber& right) override;

	virtual std::string get_str();
	friend std::istream& operator>>(std::istream& in, RealNumber& r);
	friend std::ostream& operator<<(std::ostream& out, RealNumber& r);

	virtual RealNumber from_json(std::string key, nlohmann::json data) override;
private:
	float _data = 0;

	// Inherited via IJSONPresentable
};
	