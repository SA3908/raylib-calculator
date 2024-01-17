#pragma once
#include <vector>
#include <array>
#include <string>
#include "button.h"
#include "Constants.h"
#include <stack>




class Calculator
{
	friend void debug(Calculator& session);
public:
	auto getExpression() const { return m_expression; }
	Calculator()
	{
		
	}
	void express(std::array<Button, 24>& x, std::ptrdiff_t index)
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

	void drawExpression(Font font, Color colour = BLACK) const
	{
		float x{ 100 };
		float y{ 120 };
		for (std::ptrdiff_t index{ 0 }; index < std::ssize(m_expression); ++index)
		{
			DrawTextEx(font, m_expression[index].data(), Vector2{ x += 20, y }, 30, 2, colour);
			//DrawText(m_expression[index].data(),  x += 20, y, 30, colour);
		}
	}
	void parseExpression();
	bool precedency(const std::string& oldOperator, const std::string& newOperator);
	void displayOutput() const;
	void calculate();
	
private:
	std::vector<std::string> m_expression{}; //user-input
	std::vector<std::string> m_output{}; //contain RPN output
	std::vector<std::string> m_evaluated{}; //contains evaluated RPN output (answer)

	
	std::stack<std::string> m_operators{};
	std::vector<std::string> m_operList {"^", "/", "*", "+", "-"};

	bool m_parsed{false};
};

