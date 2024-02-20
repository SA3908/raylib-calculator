#pragma once
#include <string>
#include <vector>
#include <array>
#include "button.h"
#include <raylib.h>

//class Button;

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

private:
	float m_x{0};
	float m_y{0};
	int m_width{0};
	int m_height{0};
	std::vector<std::string> m_text{};

	bool m_drawingState{ true };
	bool m_rightAlign{};
	
};

