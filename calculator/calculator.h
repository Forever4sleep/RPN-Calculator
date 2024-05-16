#pragma once
#include <map>
#include <string>
#include <stack>
#include <list>
#include <fstream>
#include "exception.h"
#include "icalculable.h"
#include "token.h"
#include <nlohmann/json.hpp>

template<class T> class Calculator
{
public:
	Calculator(std::string expression, std::string file_name)
	{
		if (!file_name.empty())
		{
			try
			{
				_data = nlohmann::json::parse(std::ifstream(file_name));
				_expression = _data["expression"];
			}
			catch (std::exception) {
				throw own_exception("Bad expression in JSON file", own_exception::exception_type::BAD_JSON);
			}
			std::cout << "Expression from file: " << _expression << std::endl;
		}
		else _expression = expression;

		_file_name = file_name;
	}
	Calculator(std::string expression)
	{
		_expression = expression;
	}
	Calculator()
	{
		_expression = "";
	}

	void set_expression(std::string s)
	{
		_expression = s;
	}

	void calculate()
	{
		if (_expression.empty())
		{
			throw own_exception("Bad formula :(", own_exception::exception_type::BAD_POWER);
		}
		pre_process_into_tokens();
		if (!_file_name.empty()) fill_values_from_json();
		else ask_for_values();
		std::cout << calculate_rpn().get_str();
	}

private:
	void pre_process_into_tokens()
	{
		Token current_token("");
		for (int i = 0; i < _expression.size(); i++)
		{
			auto character = _expression[i];
			if (character != ' ' && character != ')' && character != '(' && character != '*' && character != '+' && character != '-' && character != '/' && character != '^')
			{
				current_token.add_to_value(character);
			}
			else
			{
				if (!current_token.empty())
				{
					tokens.push_back(current_token);
					variables.insert_or_assign(current_token.get_value(),
						current_token.check_if_numeric() ? T(std::stof(current_token.get_value())) : T());
				}
				current_token = Token("");
				if (character != ' ') tokens.push_back(character);
			}
		}
		if (!current_token.empty())
		{
			tokens.push_back(current_token);
			variables.insert_or_assign(current_token.get_value(),
				current_token.check_if_numeric() ? T(std::stof(current_token.get_value())) : T());
		}
	}

	void fill_values_from_json()
	{
		for (auto it = variables.begin(); it != variables.end(); it++)
		{
			bool number = false;
			for (auto ch : it->first)
			{
				if (isdigit(ch))
				{
					number = true;
					break;
				}
			}
			if (number) continue;
			T obj;
			if (!_data.contains(it->first)) throw own_exception("Invalid json data", own_exception::exception_type::BAD_JSON);
			variables[it->first] = obj.from_json(it->first, _data);
		}
	}

	void ask_for_values()
	{
		if (variables.empty()) return;

		for (auto it = variables.begin(); it != variables.end(); it++)
		{
			bool number = false;
			for (auto ch : it->first)
			{
				if (isdigit(ch))
				{
					number = true;
					break;
				}
			}
			if (number) continue;
			std::cout << "Enter the value of " + (*it).first + " = ";
			T obj; std::cin >> obj;
			variables[it->first] = obj;
		}
	}
	std::list<Token> RPN()
	{
		std::list<Token> rpn;
		std::list<Token> rpn_stack;
		for (auto token : tokens)
		{
			if (token.check_if_operator())
			{
				if (token.get_value() != "(" && token.get_value() != ")")
				{
					while (!rpn_stack.empty() && rpn_stack.back().get_precedence_level() >= token.get_precedence_level())
					{
						rpn.push_back(rpn_stack.back());
						rpn_stack.pop_back();
					}
				}
				if (token.get_value() == ")")
				{
					while (!rpn_stack.empty() && rpn_stack.back().get_value() != "(")
					{
						rpn.push_back(rpn_stack.back());
						rpn_stack.pop_back();
					}
					if (!rpn_stack.empty() && rpn_stack.back().get_value() == "(")
						rpn_stack.pop_back();
				}
				if (token.get_value() != ")")
					rpn_stack.push_back(token);
			}
			else rpn.push_back(token);
			//std::cout << "Stack is ";
			//for (auto i : rpn_stack) std::cout << i.get_value() << " ";
			//std::cout << "\n";

		}
		while (!rpn_stack.empty())
		{
			rpn.push_back(rpn_stack.back());
			rpn_stack.pop_back();
		}
		//for (auto i : rpn) std::cout << i.get_value();
		return rpn;
	}

	T calculate_rpn()
	{
		std::list<Token> rpn = RPN();
		std::stack<T> maintenance;
		for (auto it = rpn.begin(); it != rpn.end(); it++)
		{
			if (!it->check_if_operator()) maintenance.push(variables[it->get_value()]);
			else
			{
				if (maintenance.empty())
					throw own_exception("Bad formula :(", own_exception::exception_type::BAD_FORMULA);
				T second_operand = maintenance.top();
				maintenance.pop();

				if (maintenance.empty())
					throw own_exception("Bad formula :(", own_exception::exception_type::BAD_FORMULA);

				T first_operand = maintenance.top();
				maintenance.pop();
				if (it->get_value() == "+")
					maintenance.push(first_operand + second_operand);

				if (it->get_value() == "*")
					maintenance.push(first_operand * second_operand);

				if (it->get_value() == "/")
					maintenance.push(first_operand / second_operand);

				if (it->get_value() == "^")
					maintenance.push(first_operand ^ second_operand);

				if (it->get_value() == "-")
					maintenance.push(first_operand - second_operand);

			}
		}
		return maintenance.top();
	}
	std::string _file_name;
	std::string _expression;
	std::map<std::string, T> variables;
	std::list<Token> tokens;
	nlohmann::json _data;
};