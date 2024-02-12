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
	auto getCalculatedState() const { return m_calculated; }
	auto getExpression() const { return m_expression; }
	Calculator()
	{
	}

	void parseExpression(); //convert infix expression to postfix expression
	int precedency(const std::string& oldOperator, const std::string& newOperator); //precedence level

	void drawExpression(Font font, Color colour = BLACK) const;
	void drawEvaluated(Font font, Color colour = BLACK) const;

	void express(std::array<Button, 24>& x, std::ptrdiff_t index); //add numbers & operators to calculator with on-screen buttons
	void express(int key, std::array<Button, 24>& button);		   //add numbers & operators to calculator with keyboard buttons

	void calculate(); //evaluate postfix expression
	
private:
	std::vector<std::string> m_expression{}; //user-input
	std::vector<std::string> m_output{}; //contain RPN output
	std::vector<std::string> m_evaluated{}; //contains evaluated RPN output (answer)

	
	std::stack<std::string> m_operators{};
	std::vector<std::string> m_operList {"^", "/", "*", "+", "-"};

	bool m_parsed{false};
	bool m_calculated{ false };
};

