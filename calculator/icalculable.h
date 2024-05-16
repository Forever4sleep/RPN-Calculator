#pragma once
template<class T> class ICalculable
{
	virtual T operator+(T& right) = 0;
	virtual T operator-(T& right) = 0;
	virtual T operator*(T& right) = 0;
	virtual T operator/(T& right) = 0;
	virtual T operator^(T& right) = 0;
};
