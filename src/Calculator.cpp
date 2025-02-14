#include "Calculator.h"
#include <cassert>
#include <algorithm>
#include <cmath>


void Calculator::parseExpression()	//convert expression to RPN
{
	using namespace Constants::Precedence;
	std::ptrdiff_t length{ m_expression.ssize() };

	for (std::ptrdiff_t index{ 0 }; index < length; ++index)
	{
		if (m_expression[index][0] >= '0' && m_expression[index][0] <= '9') //check for integer
		{
			m_output.emplace_back(m_expression[index]);
		}

		for (std::ptrdiff_t opIndex{ 0 }; opIndex < std::ssize(m_operList); ++opIndex)
		{
			if (m_expression[index] == m_operList[opIndex])
			{
				while (!m_operators.empty() && m_operators.top() != "(" && (precedency(m_operList[opIndex], m_operators.top()) == higher || (precedency(m_operList[opIndex], m_operators.top()) == equal && m_operList[opIndex] != "^")))
				{
					m_output.push_back(m_operators.top());
					m_operators.pop();
				}
				m_operators.push(m_operList[opIndex]);
			}
		}
		if (m_expression[index] == "(")
		{
			m_operators.push(m_expression[index]);
		}
		if (m_expression[index] == ")")
		{
			while (!m_operators.empty() && m_operators.top() != "(")
			{
				assert(!m_operators.empty());
				m_output.push_back(m_operators.top());
				m_operators.pop();
			}
			assert(m_operators.top() == "(");
			m_operators.pop(); // remove the "("
		}
	}

	while (!m_operators.empty())
	{
		assert(m_operators.top() != "(");
		m_output.push_back(m_operators.top());
		m_operators.pop();

	}
	m_parsed = true;
	calculate();
}

int Calculator::precedency(const std::string& oldOperator, const std::string& newOperator) //check precendency between two operators, if newOperator has higher precedence return true.
{
	int newOpLevel{};
	int oldOpLevel{};

	for (std::ptrdiff_t index{ 0 }; index < std::ssize(m_operList); ++index)
	{
		if (newOperator == m_operList[index])
			newOpLevel = static_cast<int>(index);
		if (oldOperator == m_operList[index])
			oldOpLevel = static_cast<int>(index);
	}
	
	using namespace Constants::Precedence;
	switch (newOpLevel)
	{
	case 0:
		if(oldOpLevel == 0)
			return equal;
		break;
	case 1:
		if (oldOpLevel == 2)
			return equal;
		break;
	case 2:
		if (oldOpLevel == 1)
			return equal;
		break;
	case 3:
		if (oldOpLevel == 4)
			return equal;
		break;
	case 4:
		if (oldOpLevel == 3)
			return equal;
		break;
	}

	if (newOpLevel < oldOpLevel)
		return higher;
	return lower;
}

template <typename T, typename U>
std::enable_if_t<std::is_floating_point<T>::value || std::is_floating_point<U>::value, double>
arithmetic(const std::string& op, std::pair<T, U> num);

template <typename T, typename U>
std::enable_if_t<std::is_integral<T>::value && std::is_integral<U>::value, int>
arithmetic(const std::string& op, std::pair<T, U> num);

bool isDecimal(const std::string& operand);

void Calculator::calculate() //evaluate postfix expression
{
	if (!m_parsed)
		return;

	std::ptrdiff_t length{ std::ssize(m_output) };

	for (std::ptrdiff_t index{ 0 }; index < length; ++index)
	{
		if (m_output[index][0] >= '0' && m_output[index][0] <= '9') //number check
		{
			m_evaluated.emplace_back(m_output[index]);
		}

		for (std::ptrdiff_t opIndex{ 0 }; opIndex < std::ssize(m_operList); ++opIndex)
		{
			if (m_operList[opIndex] == m_output[index])
			{
				assert(!m_evaluated.empty()); //if empty, user input operator before first operand

				if (isDecimal(m_evaluated.back()) && isDecimal(m_evaluated[m_evaluated.ssize() - 2]))
				{
					std::pair<double, double> numPair{ std::stod(m_evaluated.back()), std::stod(m_evaluated[m_evaluated.ssize() - 2]) };
					m_evaluated.pop_back();
					m_evaluated.pop_back();
					m_evaluated.emplace_back(std::to_string(arithmetic(m_operList[opIndex], numPair)));
				}
				else if (!isDecimal(m_evaluated.back()) && isDecimal(m_evaluated[m_evaluated.ssize() - 2]))
				{
					std::pair<int, double> numPair{ std::stoi(m_evaluated.back()), std::stod(m_evaluated[m_evaluated.ssize() - 2]) };
					m_evaluated.pop_back();
					m_evaluated.pop_back();
					m_evaluated.emplace_back(std::to_string(arithmetic(m_operList[opIndex], numPair)));
				}
				else if (isDecimal(m_evaluated.back()) && !isDecimal(m_evaluated[m_evaluated.ssize() - 2]))
				{
					std::pair<double, int> numPair{ std::stod(m_evaluated.back()), std::stoi(m_evaluated[m_evaluated.ssize() - 2]) };
					m_evaluated.pop_back();
					m_evaluated.pop_back();
					m_evaluated.emplace_back(std::to_string(arithmetic(m_operList[opIndex], numPair)));
				}
				else if (!isDecimal(m_evaluated.back()) && !isDecimal(m_evaluated[m_evaluated.ssize() - 2]))
				{
					std::pair<int, int> numPair{ std::stoi(m_evaluated.back()), std::stoi(m_evaluated[m_evaluated.ssize() - 2]) };
					m_evaluated.pop_back();
					m_evaluated.pop_back();
					if (m_operList[opIndex] == "/")
						m_evaluated.emplace_back(std::to_string(arithmetic<double, double>(m_operList[opIndex], numPair))); //force division to always be double for accuracy
					else
						m_evaluated.emplace_back(std::to_string(arithmetic(m_operList[opIndex], numPair)));
				}
			}
		}
	}
	m_calculated = true;
}


void  Calculator::express(std::array<Button, 23>& button, std::ptrdiff_t index) //GUI butttons
{
	using namespace Constants;

	if (button[index].getText() == "=")
	{
		parseExpression();
	}
	else if (button[index].getText() == mul)
	{
		m_expression.insertIndex("*", m_operList);
	}
	else if (button[index].getText() == Constants::div)
	{
		m_expression.insertIndex("/", m_operList);
	}
	else if (button[index].getText() == backspace)
	{
		if (!m_expression.empty())
			m_expression.deleteIndex();
	}
	else if (button[index].getText() == "CE")
	{
		m_expression.clear();
	}
	else
	{
		if (m_expression.endIndex())
			m_expression.updateIndex();

		m_expression.insertIndex(button[index].getText(), m_operList);
	}
}

void Calculator::express(int key, std::array<Button, 23>& button) //keyboard input
{

	m_expression.traverseArrowKey();

	std::string stringKey{ static_cast<char>(key) };
	for (std::ptrdiff_t index{ 0 }; index < std::ssize(button); ++index)
	{
		if (button[index].getText() == stringKey)
		{
			button[index].colourChange(RED);
			express(button, index);
			break;
		}
		if (button[index].getText() == Constants::div && key == 47) // "/" unicode key
		{
			button[index].colourChange(RED);
			m_expression.insertIndex("/", m_operList);
			break;
		}
		if (button[index].getText() == Constants::mul && key == 42) // "*" unicode key
		{
			button[index].colourChange(RED);
			m_expression.insertIndex("*", m_operList);
			break;
		}
		if (button[index].getText() == Constants::backspace && IsKeyPressed(KEY_BACKSPACE))
		{
			button[index].colourChange(RED);
			if (!m_expression.empty())
				m_expression.deleteIndex();
		}
		if (button[index].getText() == "CE" && IsKeyPressed(KEY_C))
		{
			m_expression.clear();
		}
	}
	if (m_expression.endIndex())
		m_expression.updateIndex();
}

//outer class -------------------------------------

bool isDecimal(const std::string& operand) 
{
	for (std::ptrdiff_t index{ 0 }; index < std::ssize(operand); ++index)
	{
		if (operand[index] == '.')
		{
			return true; //early return because we know the number is a decimal
		}
	}
	return false;
}

template <typename T, typename U>
std::enable_if_t<std::is_floating_point<T>::value || std::is_floating_point<U>::value, double>
arithmetic(const std::string& op, std::pair<T, U> num)
{
	if (op == "+")
		return num.first + num.second;
	else if (op == "-")
		return num.second - num.first;
	else if (op == "*")
		return num.first * num.second;
	else if (op == "/")
		return (num.first == 0 || num.second == 0) ? 0 : num.second / num.first;
	else if (op == "^")
		return pow(num.second, num.first);
	return 0;
}

template <typename T, typename U>
std::enable_if_t<std::is_integral<T>::value && std::is_integral<U>::value, int>
arithmetic(const std::string& op, std::pair<T, U> num)
{
	if (op == "+")
		return num.first + num.second;
	else if (op == "-")
		return num.second - num.first;
	else if (op == "*")
		return num.first * num.second;
	else if (op == "/")
		return (num.first == 0 || num.second == 0) ? 0 : num.second / num.first;
	else if (op == "^")
		return pow(num.second, num.first);
	return 0;
}