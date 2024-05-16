#include "calculator.h"
#include "icalculable.h"
#include "RealNumber.h"
#include "complex.h"
#include "fraction.h"
#include "matrix.h"
#include "exception.h"


int main()
{
	int type, file_mode;
	std::string file_name = "";
	do
	{
		std::cout << "Choose type of calculator: 1 - real numbers, 2 - fractions, 3 - matrices, 4 - complex numbers:\n";
		std::cin >> type;
	} while (type > 4 || type < 1);

	do
	{
		std::cout << "Do you want to read data variables from file? (0 - No, 1 - Yes)";
		std::cin >> file_mode;
	} while (file_mode != 1 && file_mode != 0);

	if (file_mode)
	{
		std::cout << "Enter file's name: "; std::cin >> file_name;
		std::ifstream f(file_name);
	}
	if (!file_mode) cout << "Enter expression: ";  cin.ignore();
	try
	{
		string exp;
		if (!file_mode)
		{
			getline(cin, exp);
		}
		if (type == 1) Calculator<RealNumber>(exp, file_name).calculate();
		if (type == 2) Calculator<Fraction>(exp, file_name).calculate();
		if (type == 3) Calculator<Matrix>(exp, file_name).calculate(); 
		if (type == 4) Calculator<ComplexNumber>(exp, file_name).calculate();
	}
	catch (own_exception exc)
	{
		std::cout << exc.what() << endl;
	}
}