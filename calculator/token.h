#pragma once

#include <iostream>
using namespace std;

class Token
{
public:
	Token(std::string value);
	Token(char value);
	bool check_if_numeric();
	bool empty();
	int get_precedence_level();
	bool check_if_operator();
	std::string get_value();
	void add_to_value(char k);
	void change_value(string s);
private:
	std::string _value;
};