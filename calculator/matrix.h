#pragma once
#include "icalculable.h"
#include "ijsonpresentable.h"
#include "igettable.h"
#include <iostream>
#include <vector>

class Matrix : public ICalculable<Matrix>, public IGettable, public IJSONPresentable<Matrix>

{
public:
	Matrix(unsigned int rows, unsigned int cols);
	Matrix(unsigned int rows, unsigned int cols, double value);
	Matrix(double value);
	Matrix();
	virtual Matrix operator+(Matrix& right) override;
	virtual Matrix operator-(Matrix& right) override;
	virtual Matrix operator*(Matrix& right) override;
	virtual Matrix operator/(Matrix& right) override;
	virtual Matrix operator^(Matrix& right) override;
	virtual std::string get_str() override;

	friend std::istream& operator>>(std::istream& in, Matrix& r);
	friend std::ostream& operator<<(std::ostream& out, Matrix& r);
	virtual Matrix from_json(std::string key, nlohmann::json data) override;
private:
	unsigned int rows = 1, cols = 1;
	std::vector<std::vector<double>> matrix;

	// Inherited via IJSONPresentable
	// Inherited via IGettable
	// Inherited via ICalculable
};

