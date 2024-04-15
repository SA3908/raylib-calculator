#include "TextBox.h"

const bool TextBox::elementIsOperator(const std::ptrdiff_t index, const std::vector<std::string>& operList) const
{
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
			else if (m_index.outIndex < std::ssize(m_text) - 1 && m_index.inIndex == std::ssize((m_text[m_index.outIndex])) - 1)
			{
				m_index.outIndex += 1;
				m_index.inIndex = 0;
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
			else if (m_index.outIndex > 0 && m_index.inIndex == 0)
			{
				m_index.outIndex -= 1;
				m_index.inIndex = std::ssize(m_text[m_index.outIndex]) - 1;
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
	bool isOperator{ false };
	for (std::ptrdiff_t opIndex{ 0 }; opIndex < std::ssize(operList); ++opIndex)
	{
		if (ch == operList[opIndex] || ch == "(" || ch == ")")
			isOperator = true;
	}

	if (!isOperator)
	{
		for (std::ptrdiff_t index{ m_index.outIndex }; index < std::ssize(m_text); ++index)
		{
			if (elementIsOperator(index, operList))
			{
				m_index.outIndex = index + 1; //last element (index) is operator, so, push the number to the back
				break;
			}
		}
		if (std::ssize(m_text) == m_index.outIndex) //create new element
		{
			m_text.push_back(ch);
			if (std::ssize(m_text) != 1)
				++m_index.outIndex;
		}
		else if (std::ssize(m_text[m_index.outIndex]) == 0) //an element exists however, that element is empty.
		{
			m_text[m_index.outIndex] = ch; //override the empty string element with this number
		}
		else if (std::ssize(m_text[m_index.outIndex]) - 1 == m_index.inIndex) //add to existing element
		{
			m_text[m_index.outIndex].push_back(ch.front());
			if (m_endIndex)
				++m_index.inIndex;
		}
		else if (std::ssize(m_text[m_index.outIndex]) == m_index.inIndex) //adds to existing element but m_index.inIndex did not decrease correctly
		{
			m_text[m_index.outIndex].insert(m_index.inIndex, ch);
			m_index.inIndex++;
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
			if (std::ssize(m_text[m_index.outIndex + 1]) == 0) //an element exists however, that element is empty.
			{
				m_text[m_index.outIndex + 1] = ch; //override the empty string element with this operator.
			}
		}
	}
	updateIndex();
}

void TextBox::deleteIndex()
{
	m_text[m_index.outIndex].erase(m_index.inIndex, 1);
	if (m_index.inIndex == 0 && m_index.outIndex > 0)
		m_index.outIndex--;
	else if (m_index.inIndex > 0)
		m_index.inIndex--;
}