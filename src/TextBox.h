#pragma once
#include <string>
#include <vector>
#include <raylib.h>


class TextBox //display, align and manoeuvre through text
{
public:
	TextBox()
	{
	}

	TextBox(float x, float y, int width, int height, bool rightAlign = false)
		:m_x{x}, m_y{y}, m_width {width}, m_height{height}, m_rightAlign{rightAlign}
	{
	}

	std::vector<std::string>& getText() { return m_text; }

	//OVERLOADS
	std::string& operator[] (const std::ptrdiff_t index) { return m_text[index]; }
	const std::string& operator[] (const std::ptrdiff_t index) const { return m_text[index]; }

	const std::string& back() { return m_text.back(); }
	bool empty() const { return m_text.empty(); }
	void clear() { m_text.clear(); }
	std::ptrdiff_t ssize() const { return std::ssize(m_text); }

	void pop_back() { m_text.pop_back(); }
	void push_back(const std::string& text) { m_text.push_back(text); }
	void emplace_back(const std::string& text) { m_text.emplace_back(text); }

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
			for (std::ptrdiff_t index{ 0 }; index < length; ++index)
			{
				DrawTextEx(font, m_text[index].c_str(), Vector2(x += 15, m_y), 30, 0, RAYWHITE);
			}
		}
		if (m_drawingState && m_rightAlign) //draw text right-aligned from m_width
		{
			for (std::ptrdiff_t index{ 0 }; index < length; ++index)
			{
				DrawTextEx(font, m_text[index].c_str(), Vector2{m_width - measuredString, m_y}, 30, 0, RAYWHITE);
			}
		}
	}

private:
	float m_x{0};
	float m_y{0};
	int m_width{0};
	int m_height{0};
	std::vector<std::string> m_text{};

	bool m_drawingState{ true }; //prevention for m_text exceeding m_width
	bool m_rightAlign{};
	
};

