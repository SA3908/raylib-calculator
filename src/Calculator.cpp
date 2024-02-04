#include "Calculator.h"
#include <cassert>
#include <algorithm>





void Calculator::parseExpression()	//convert expression to RPN
{
	std::ptrdiff_t length{ std::ssize(m_expression) };



	for (std::ptrdiff_t index{ 0 }; index < length; ++index)
	{
		bool numberPresent{};
		for (std::ptrdiff_t numIndex{ index }; numIndex < length; ++numIndex)
		{
			bool isOperator{ false };
			for (std::ptrdiff_t opIndex{ 0 }; opIndex < std::ssize(m_operList); ++opIndex)
			{
				if (m_expression[numIndex] == m_operList[opIndex] || m_expression[numIndex] == "(" || m_expression[numIndex] == ")")
				{
					isOperator = true;
					break;
				}

			}
			if (isOperator)
			{

				break;
			}

			if (!numberPresent) //create new element with the number
			{
				m_output.emplace_back(m_expression[numIndex]);
				numberPresent = true;
			}
			else if (numberPresent) //add more numbers to current element
			{
				m_output.back() += m_expression[numIndex];
			}
			index = numIndex;

		}

		for (std::ptrdiff_t opIndex{ 0 }; opIndex < std::ssize(m_operList); ++opIndex)	//brackets at start of m_expression error
		{
			if (m_expression[index] == m_operList[opIndex])
			{
				while (!m_operators.empty() && m_operators.top() != "(" && (precedency(m_operList[opIndex], m_operators.top()) == true))
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

bool Calculator::precedency(const std::string& oldOperator, const std::string& newOperator) //check precendency between two operators, if newOperator has higher precedence return true.
{
	int newOpLevel{};
	int oldOpLevel{};

	for (std::ptrdiff_t index{ 0 }; index < std::ssize(m_operList); ++index)
	{
		if (newOperator == m_operList[index])
		{
			newOpLevel = static_cast<int>(index);
		}
		if (oldOperator == m_operList[index])
		{
			oldOpLevel = static_cast<int>(index);
		}
	}

	switch (newOpLevel) //to return true if equal precedence
	{
	case 0:
		return true;
		break;
	case 1:
		if (oldOpLevel == 2)
			return true;
		break;
	case 2:
		if (oldOpLevel == 1)
			return true;
		break;
	case 3:
		if (oldOpLevel == 4)
			return true;
		break;
	case 4:
		if (oldOpLevel == 3)
			return true;
		break;
	}

	if (newOpLevel < oldOpLevel)
		return true;
	return false;
}

int arithmetic(const std::string& op, const std::string& operand1, const std::string& operand2);

void Calculator::calculate() //evaluate postfix expression
{
	if (!m_parsed)
		return;

	std::ptrdiff_t length{ std::ssize(m_output) };
	std::string firstOperand{};
	std::string secondOperand{};

	for (std::ptrdiff_t index{ 0 }; index < length; ++index)
	{
		if (m_output[index][0] >= '0' && m_output[index][0] <= '9') //number check
		{
			m_evaluated.emplace_back(m_output[index]);
		}


		for (std::ptrdiff_t opIndex{ 0 }; opIndex < std::ssize(m_operList); ++opIndex)
		{
			if (m_operList[opIndex] == m_output[index] && opIndex != 0)
			{
				assert(!m_evaluated.empty()); //if empty, user input operator before first operand


				firstOperand.append(m_evaluated.back());
				m_evaluated.pop_back();
				secondOperand.append(m_evaluated.back());
				m_evaluated.pop_back();


				m_evaluated.push_back(std::to_string(arithmetic(m_operList[opIndex], firstOperand, secondOperand)));


				firstOperand.clear();
				secondOperand.clear();
			}
		}
	}
}

void Calculator::displayOutput() const //display answer
{

}

void  Calculator::express(std::array<Button, 24>& x, std::ptrdiff_t index)
{
	using namespace Constants;

	if (x[index].getText() == "=")
	{
		parseExpression();
	}
	else if (x[index].getText() == mul)
	{
		m_expression.push_back("*");
	}
	else if (x[index].getText() == Constants::div)
	{
		m_expression.push_back("/");
	}
	else if (x[index].getText() == backspace)
	{
		if (!m_expression.empty())
			m_expression.pop_back();
	}
	else if (x[index].getText() == "CE")
	{
		m_expression.clear();
	}
	else
		m_expression.push_back(x[index].getText());
}

void Calculator::express(int key, std::array<Button, 24>& button) //keyboard input
{
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
			m_expression.push_back(stringKey);
			break;
		}
		if (button[index].getText() == Constants::mul && key == 42) // "*" unicode key
		{
			button[index].colourChange(RED);
			m_expression.push_back(stringKey);
			break;
		}
		if (button[index].getText() == Constants::backspace && IsKeyPressed(KEY_BACKSPACE))
		{
			button[index].colourChange(RED);
			if (!m_expression.empty())
				m_expression.pop_back();
		}
		if (button[index].getText() == "CE" && IsKeyPressed(KEY_C))
		{
			m_expression.clear();
		}
	}
}

//outer class -------------------------------------
template <typename T>
T add(T x, T y)
{
	return x + y;
}

template <typename T>
T subtract(T x, T y)
{
	return x - y;
}

template <typename T>
T divide(T x, T y)
{
	return x / y;
}

template <typename T>
T multiply(T x, T y)
{
	return x * y;
}


int arithmetic(const std::string& op, const std::string& operand1, const std::string& operand2)
{
	int num1{ std::stoi(operand1) }; //use variation of std::stol for float/doubles
	int num2{ std::stoi(operand2) };

	if (op == "+")
		return add(num1, num2);
	else if (op == "-")
		return subtract(num2, num1);
	else if (op == "*")
		return multiply(num1, num2);
	else if (op == "/")
		return divide(num2, num1);


	return 0;
}