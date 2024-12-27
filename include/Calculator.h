#pragma once
#include <vector>
#include <array>
#include <string>
#include <stack>

#include "button.h"
#include "Constants.h"
#include "Textbox.h"


class Calculator
{
	friend void debug(Calculator& session);
public:
	bool getCalculatedState() const { return m_calculated; } //return true if m_expression is evaluated and stored in m_evaluated
	TextBox& getExpression() { return m_expression; }
	TextBox& getEvaluated()  { return m_evaluated; }
	Calculator()
	{
	}
	Calculator(const TextBox& expression, const TextBox& evaluated)
		:m_expression{expression}, m_evaluated{evaluated}
	{
	}

	void parseExpression(); //convert infix expression to postfix expression
	int precedency(const std::string& oldOperator, const std::string& newOperator); //return precedence level

	void express(std::array<Button, 23>& button, std::ptrdiff_t index); //add numbers & operators to calculator with on-screen buttons
	void express(int key, std::array<Button, 23>& button);		   //add numbers & operators to calculator with keyboard buttons

	void calculate(); //evaluate postfix expression
	
private:
	std::vector<std::string> m_output{}; //contain RPN output

	TextBox m_expression{}; //user-input
	TextBox m_evaluated{};  //contains evaluated RPN output (answer)

	std::stack<std::string> m_operators{};
	std::vector<std::string> m_operList {"^", "/", "*", "+", "-"};

	bool m_parsed{false};
	bool m_calculated{ false };
};

