#include "matrix.h"
#include <string>
#include "my_exception.h"
#include "exception.h"

Matrix::Matrix(unsigned int rows, unsigned int cols)
{
	this->rows = rows;
	this->cols = cols;

	matrix = std::vector<std::vector<double>>();
	matrix.resize(rows);
	for (int i = 0; i < rows; i++) matrix[i].resize(cols);
}

Matrix::Matrix(unsigned int rows, unsigned int cols, double value)
{
	this->rows = rows;
	this->cols = cols;

	matrix = std::vector<std::vector<double>>();
	matrix.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		matrix[i].resize(cols);
		for (int j = 0; j < cols; j++)
		{
			matrix[i][j] = value;
		}
	}
}

Matrix::Matrix(double value)
{
	this->rows = 1;
	this->cols = 1;

	matrix.push_back(std::vector<double>());
	matrix[0].push_back(value);
}

Matrix::Matrix()
{
	rows = 1;
	cols = 1;
}

Matrix Matrix::operator+(Matrix& right)
{
	if (rows != 1 || cols != 1)
		if (right.rows != 1 || right.cols != 1)
			if (right.cols != cols || right.rows != rows)
				throw own_exception("you can't divide matrices", own_exception::exception_type::BAD_SIZE);

	if (rows == 1 && cols == 1)
	{
		Matrix new_matr(right.rows, right.cols);
		for (int i = 0; i < right.rows; i++)
			for (int j = 0; j < right.cols; j++)
				new_matr.matrix[i][j] = right.matrix[i][j] + matrix[0][0];
		return new_matr;
	}
	Matrix new_matrix(rows, cols);
	if (right.rows == 1 && right.cols == 1)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				new_matrix.matrix[i][j] += matrix[i][j] + right.matrix[0][0];

		return new_matrix;
	}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			new_matrix.matrix[i][j] = matrix[i][j] + right.matrix[i][j];

	return new_matrix;
}

Matrix Matrix::operator-(Matrix& right)
{
	if (right.rows != right.rows || right.cols != right.cols)
		if (right.rows != 1 || right.cols != 1)
			throw own_exception("you can't divide matrices", own_exception::exception_type::BAD_SIZE);

	Matrix new_matrix(rows, cols);
	if (right.rows == 1 && right.cols == 1)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				new_matrix.matrix[i][j] -= right.matrix[0][0];

		return new_matrix;
	}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			new_matrix.matrix[i][j] = matrix[i][j] - right.matrix[i][j];

	return new_matrix;
}

Matrix Matrix::operator*(Matrix& right)
{
	if (rows != 1 || cols != 1)
		if (right.rows != 1 || right.cols != 1)
			if (cols != right.rows)
				throw own_exception("Bad matrix sizes", own_exception::exception_type::BAD_SIZE);

	if (right.cols == 1 && right.rows == 1)
	{
		Matrix new_matrix1(rows, cols);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				new_matrix1.matrix[i][j] = matrix[i][j] * right.matrix[0][0];

		return new_matrix1;
	}

	if (rows == 1 && cols == 1)
	{
		Matrix new_matrix2(right.rows, right.cols);
		for (int i = 0; i < right.rows; i++)
			for (int j = 0; j < right.cols; j++)
				new_matrix2.matrix[i][j] = matrix[0][0] * right.matrix[i][j];
		return new_matrix2;
	}

	Matrix new_matrix(rows, right.cols, 0);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < right.cols; j++)
			for (int k = 0; k < right.rows; k++)
				new_matrix.matrix[i][j] += matrix[i][k] * right.matrix[k][j];

	return new_matrix;
}

Matrix Matrix::operator/(Matrix& right)
{
	throw own_exception("you can't divide matrices", own_exception::exception_type::MATRIX_DIVISION);
}

Matrix Matrix::operator^(Matrix& right)
{
	if (right.rows != 1 || right.cols != 1 || right.matrix[0][0] <= 0)
		throw own_exception("Can't raise matrix to a bad power :(", own_exception::exception_type::BAD_POWER);

	Matrix source = *this;
	Matrix res = *this;
	for (int i = 1; i < right.matrix[0][0]; i++)
		res = res * source;

	return res;
}

std::string Matrix::get_str()
{
	std::string s;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			s += std::to_string(matrix[i][j]) + " ";
		}
		s += "\n";
	}

	return s;
}

Matrix Matrix::from_json(std::string key, nlohmann::json data)
{
	int rows = data[key]["rows"].get<int>();
	int cols = data[key]["cols"].get<int>();
	Matrix matrix(rows, cols, 0);
	if (data[key]["values"].size() != rows)
		throw own_exception("Bad json", own_exception::exception_type::BAD_JSON);

	try
	{
		for (int i = 0; i < rows; i++)
		{
			if (data[key]["values"][i].size() != cols)
				throw own_exception("Bad json", own_exception::exception_type::BAD_JSON);

			for (int j = 0; j < cols; j++)
			{
				matrix.matrix[i][j] = data[key]["values"][i][j].get<double>();
			}
		}
	}
	catch (std::runtime_error)
	{
		throw own_exception("Bad json", own_exception::exception_type::BAD_JSON);
	}
	return matrix;
}

std::istream& operator>>(std::istream& in, Matrix& r)
{
	in >> r.rows;
	in >> r.cols;

	r.matrix.resize(r.rows);

	for (int i = 0; i < r.rows; i++)
	{
		r.matrix[i].resize(r.cols);
		for (int j = 0; j < r.cols; j++)
		{
			in >> r.matrix[i][j];
		}
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, Matrix& r)
{
	for (int i = 0; i < r.rows; i++)
	{
		for (int j = 0; j < r.cols; j++)
		{
			std::cout << r.matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return out;
}
