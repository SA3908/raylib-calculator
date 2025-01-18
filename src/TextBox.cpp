#include "TextBox.h"

const bool TextBox::elementIsOperator(const std::ptrdiff_t index, const std::vector<std::string>& operList) const
{
	if (m_text.empty()) //if m_text is empty, there is no operator to check
		return false;

	for (std::ptrdiff_t opIndex{ 0 }; opIndex < std::ssize(operList); ++opIndex)
	{
		if (m_text[index] == operList[opIndex] || m_text[index] == "(" || m_text[index] == ")")
			return true;
	}
	return false;
}

void TextBox::updateIndex()
{
	if (!m_endIndex || m_text.empty())
		return;

	std::ptrdiff_t prevIndex{ m_index.outIndex };

	m_index.outIndex = std::ssize(m_text) - 1; //moves outIndex to the last element, even if the last element is empty
	if (m_index.outIndex > prevIndex && std::ssize(m_text.back()) != 0) //outIndex moved element therefore inIndex should be reset
	{
		m_index.inIndex = 0;
	}
	else if (m_index.outIndex < prevIndex && std::ssize(m_text.back()) != 0)
	{
		m_index.inIndex = std::ssize(m_text[m_index.outIndex]) - 1;
		m_endIndex = false; //user moved cursor left so they are not at the end of the expression anymore
	}
	else if (m_index.outIndex > prevIndex && std::ssize(m_text.back()) == 0) //user deleted an operand and an element is before the deleted operand
	{
		m_index.outIndex = prevIndex; //go back to the element before the previously deleted element.
		if (m_index.inIndex > 0)
			m_index.inIndex = std::ssize(m_text[m_index.outIndex]) - 1; //make sure we are at the last digit/operator because the outer index is moving left.
	}
}

void TextBox::traverseArrowKey()
{
	if (IsKeyPressed(KEY_RIGHT))
	{

		if (!m_text.empty() && std::ssize(m_text) > m_index.outIndex)
		{
			if (std::ssize(m_text[m_index.outIndex]) - 1 > m_index.inIndex)
			{
				m_index.inIndex += 1;
			}
			else if (m_index.outIndex < std::ssize(m_text) - 1 && m_index.inIndex == std::ssize((m_text[m_index.outIndex])) - 1 && std::ssize(m_text[m_index.outIndex + 1]) != 0)
			{
				m_index.outIndex += 1;
				m_index.inIndex = 0;
			}
			else if (m_index.outIndex < std::ssize(m_text) - 1 && std::ssize(m_text[m_index.outIndex + 1]) == 0) //next element from outIndex is empty and we should skip to the next element that isn't empty
			{
				for (std::ptrdiff_t index{ m_index.outIndex }; index < std::ssize(m_text); ++index)
				{
					if (std::ssize(m_text[index]) != 0)
						m_index.outIndex = index;
				}
			}

		}
		m_endIndex = false;
	}
	if (IsKeyPressed(KEY_LEFT))
	{
		if (!m_text.empty() && m_index.outIndex > -1)
		{
			if (m_index.inIndex > 0)
			{
				m_index.inIndex -= 1;
			}
			else if (m_index.outIndex > 0 && m_index.inIndex == 0 && std::ssize(m_text[m_index.outIndex - 1]) != 0)
			{
				m_index.outIndex -= 1;
				m_index.inIndex = std::ssize(m_text[m_index.outIndex]) - 1;
			}
			else if (m_index.outIndex > 0 && std::ssize(m_text[m_index.outIndex - 1]) == 0)
			{
				for (std::ptrdiff_t index{ m_index.outIndex }; index >= 0; --index)
				{
					if (std::ssize(m_text[index]) != 0)
						m_index.outIndex = index;
				}
			}
			m_endIndex = false;
		}
	}

	if (m_text.empty())
	{
		m_index.outIndex = 0;
		m_index.inIndex = 0;
		m_endIndex = true;
	}

	if (!m_text.empty() && std::ssize(m_text) - 1 == m_index.outIndex && std::ssize(m_text.back()) - 1 == m_index.inIndex)
		m_endIndex = true;
}

void TextBox::drawText(Font& font)
{
	if (m_text.empty())
	{
		m_endIndex = true;
		return;
	}

	std::ptrdiff_t length{ std::ssize(m_text) };
	float measuredString{}; //width of m_text 
	float x{ m_x }; //temporary value modified by the drawing loops
	for (std::ptrdiff_t index{ 0 }; index < length; ++index)
	{
		measuredString += MeasureTextEx(font, m_text[index].c_str(), font.baseSize, 0).x;
	}
	if (length * 20 >= m_width) //ensure text width does not exceed calculator bounds
		m_drawingState = false;
	else
		m_drawingState = true;

	if (m_drawingState && !m_rightAlign)  //draw text left-aligned from m_x
	{
		for (std::ptrdiff_t outIndex{ 0 }; outIndex < length; ++outIndex)
		{
			for (std::ptrdiff_t inIndex{ 0 }; inIndex < std::ssize(m_text[outIndex]); ++inIndex)
			{
				if (m_text[outIndex][inIndex] == '-')
					x += 2;
				if (outIndex >= 2 && inIndex == 0)
				{
					if (m_text[outIndex - 1] == "+") //to add more spacing to the digit after a "+" 
						x += 5;
				}
				if (inIndex >= 1)
				{
					if (m_text[outIndex][inIndex - 1] == '.') //reduce spacing when there is a decimal point before a number
						x -= 8;
				}
				DrawTextEx(font, std::string(1, m_text[outIndex][inIndex]).c_str(), Vector2(x += 15, m_y), 30, 2, RAYWHITE);
				if (outIndex == m_index.outIndex && inIndex == m_index.inIndex) //draw "|"
				{
					DrawTextEx(font, "|", Vector2(x + 15, m_y), 30, 0, RED);
				}
			}
		}
	}
	else if (!m_drawingState && !m_rightAlign) //draw text left aligned from m_x up to a certain point, use arrow keys to traverse. 
	{
		float excessText{ measuredString - m_width };
		for (std::ptrdiff_t index{ 0 }; index < length; ++index)
		{

		}
	}
	else if (m_drawingState && m_rightAlign) //draw text right-aligned from m_width
	{
		for (std::ptrdiff_t index{ 0 }; index < length; ++index)
		{
			DrawTextEx(font, m_text[index].c_str(), Vector2{ m_width - measuredString, m_y }, 30, 0, RAYWHITE);
		}
	}


}

void TextBox::insertIndex(const std::string& ch, const std::vector<std::string>& operList)
{
	if (m_index.outIndex == 0 && m_index.inIndex == 0 && m_text.empty())
		m_endIndex = true;
	bool isOperator{ false };
	for (std::ptrdiff_t opIndex{ 0 }; opIndex < std::ssize(operList); ++opIndex)
	{
		if (ch == operList[opIndex] || ch == "(" || ch == ")")
			isOperator = true;
	}

	if (!isOperator) //if ch is not an operator
	{
		bool currentElementOperator{ false };
		if (elementIsOperator(m_index.outIndex, operList))
		{
			m_index.outIndex += 1; //The element (at m_index.outIndex) is an operator which must be kept by itself, so push the number to the back of the expression
			currentElementOperator = true;
		}

		if (std::ssize(m_text) == m_index.outIndex) //create new element
		{
			m_text.push_back(ch);
			if (std::ssize(m_text) != 1)
				++m_index.outIndex;
		}
		else if (std::ssize(m_text[m_index.outIndex]) == 0) // the current string element is empty
		{
			m_text[m_index.outIndex] = ch; //override the empty string element with this number
		}
		else
		{
			if (m_endIndex)
			{
				m_text[m_index.outIndex].push_back(ch.front());
				m_index.inIndex++;
			}
			else
			{
				if (std::ssize(m_text[m_index.outIndex]) - 1 >= m_index.inIndex && !currentElementOperator)
				{
					m_text[m_index.outIndex].insert(m_index.inIndex + 1, ch);
					m_index.inIndex++;
				}
			}
		}
	}
	else if (isOperator)
	{
		if (std::ssize(m_text) - 1 == m_index.outIndex) //create new element with operator
		{
			m_text.push_back(ch);
		}
		else if (!m_text.empty() && !m_text[m_index.outIndex].empty())
		{
			if (std::ssize(m_text[m_index.outIndex + 1]) == 0) //an empty string element exists after the current element.
			{
				m_text[m_index.outIndex + 1] = ch; //override the empty string element with this operator.
				m_index.outIndex++;
				m_index.inIndex = 0;
			}
		}
		else if (std::ssize(m_text) == m_index.outIndex && (ch == "(" || ch == ")")) //to allow only brackets to be placed at the start of m_text
		{
			m_text.push_back(ch);
			++m_index.outIndex;
		}
		else if (std::ssize(m_text[m_index.outIndex]) == 0 && (ch == "(" || ch == ")")) // the current string element is empty
		{
			m_text[m_index.outIndex] = ch; //override the empty string element with brackets
		}
	}
	updateIndex();
}

void TextBox::deleteIndex() 
{
	m_text[m_index.outIndex].erase(m_index.inIndex, 1); 
	if (m_index.inIndex == 0 && m_index.outIndex > 0) //if the current element is empty and there is an element before it
	{
		m_index.outIndex--; //move to the previous element
		m_index.inIndex = std::ssize(m_text[m_index.outIndex]) - 1; //move to the last character in the previous element
	}
	else if (m_index.inIndex > 0) //if the current element is not empty
	{
		m_index.inIndex--; //move to the previous character in the current element
	}
}