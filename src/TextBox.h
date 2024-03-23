#pragma once
#include <string>
#include <vector>
#include <raylib.h>

struct IndexPair //iterate through an element of an element within an array
{
	std::ptrdiff_t inIndex{}; //index within outIndex (for string arrays/vectors)
	std::ptrdiff_t outIndex{};
};

class TextBox //display, align and manoeuvre through text
{
public:
	TextBox()
	{
	}

	TextBox(float x, float y, int width, int height, bool rightAlign = false)
		:m_x{ x }, m_y{ y }, m_width{ width }, m_height{ height }, m_rightAlign{ rightAlign }
	{
	}

	std::vector<std::string>& getText() { return m_text; }
	const bool endIndex() const { return m_endIndex; }

	//OVERLOADS
	std::string& operator[] (const std::ptrdiff_t index) { return m_text[index]; }
	const std::string& operator[] (const std::ptrdiff_t index) const { return m_text[index]; }

	const std::string& back() const { return m_text.back(); }
	std::string& back() { return m_text.back(); }
	constexpr bool empty() const { return m_text.empty(); }
	void clear() { m_text.clear(); }
	constexpr std::ptrdiff_t ssize() const { return std::ssize(m_text); }

	void pop_back() { m_text.pop_back(); }
	void push_back(const std::string& text) { m_text.push_back(text); }
	void emplace_back(const std::string& text) { m_text.emplace_back(text); }



	void updateIndex()
	{
		std::ptrdiff_t prevIndex{ m_index.outIndex };
		if (!m_endIndex || m_text.empty())
			return;
		m_index.outIndex = std::ssize(m_text) - 1;
		//m_index.inIndex = 0;
		if (m_index.outIndex != prevIndex) //outIndex moved element therefore inIndex should be reset
			m_index.inIndex = 0;
	}

	void traverseArrowKey() //if arrow keys are pressed move the " | " left/right. 
	{
		if (IsKeyPressed(KEY_RIGHT))
		{

			if (!m_text.empty() && std::ssize(m_text) > m_index.outIndex)
			{
				if (std::ssize(m_text[m_index.outIndex]) - 1 > m_index.inIndex)
				{
					m_index.inIndex += 1;
				}
				else if (m_index.outIndex < std::ssize(m_text) && m_index.inIndex == std::ssize((m_text[m_index.outIndex])))
				{
					m_index.outIndex += 1;
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

	void drawText(Font& font)
	{
		if (m_text.empty())
			return;

		std::ptrdiff_t length{ std::ssize(m_text) };
		float measuredString{};
		float x{ m_x };
		for (std::ptrdiff_t index{ 0 }; index < length; ++index)
		{
			measuredString += MeasureTextEx(font, m_text[index].c_str(), 30, 0).x;
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
	void insertIndex(const std::string& ch, const std::vector<std::string>& operList)
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
				++m_index.outIndex;
			}
			else if (std::ssize(m_text[m_index.outIndex]) - 1 == m_index.inIndex) //add to existing element
			{
				m_text[m_index.outIndex].push_back(ch.front());
				if (m_endIndex)
					++m_index.inIndex;
			}
			else
				m_text[m_index.outIndex][m_index.inIndex] = ch.front();
		}
		else if (isOperator)
		{
			if (std::ssize(m_text) - 1 == m_index.outIndex) //create new element with operator
			{
				m_text.push_back(ch);
			}
		}
	}
	void deleteIndex() //remove character at m_index
	{

	}
	
private:
	char drawPipe() { return m_text[m_index.outIndex][m_index.inIndex]; }
	const bool elementIsOperator (const std::ptrdiff_t index, const std::vector<std::string>& operList) const;


	float m_x{ 0 };
	float m_y{ 0 };
	int m_width{ 0 };
	int m_height{ 0 };

	std::vector<std::string> m_text{};
	IndexPair m_index{0, 0}; //this index allows modification of m_text and holds cursor position
	bool m_endIndex{ true }; //for index to keep up with last index of m_text

	bool m_drawingState{ true }; //prevention for m_text exceeding m_width
	bool m_rightAlign{};
};

// do not allow m_index to be in an element that contains any operator
// insert index - make sure operators are in standalone elements, seperate numbers from operators. if index is on an element that already contains a number,
//then add numbers to that element otherwise if it is an operator, insert it to next index that does not contain operators.