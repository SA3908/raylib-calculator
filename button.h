#pragma once
#include <raylib.h>

class Button
{
public:

	Color getColour() const { return m_colour; }
	const std::string& getText() const { return m_text; }
	
	Button(int x, int y, int width, int height, const std::string& text, Color colour = { 47, 55, 71, 255 }, Color textColour = RAYWHITE)
		:m_x{ x }, m_y{ y }, m_width{ width }, m_height{height},  m_text{text}, m_buttonColour{ colour }, m_textColour{textColour}
	{

	}
	bool buttonPressed() const
	{
		return ((GetMouseX() >= m_x && GetMouseX() <= (m_x + m_width) && GetMouseY() >= m_y && GetMouseY() < (m_y + m_height) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ? true : false));
	}
	void colourChange(Color tempColour)
	{
		m_colour = tempColour;
	}
	void colourChange()
	{
		m_colour = m_buttonColour;
	}

	void drawRectButton()
	{
		DrawRectangle(m_x, m_y, m_width, m_height, m_colour);
		DrawRectangleLines(m_x, m_y, m_width, m_height, BLACK);
	}
	void drawTextMiddle(const Font& fontCalculator)
	{
		DrawTextEx(fontCalculator, m_text.data(), Vector2(static_cast<float>((m_x + m_width / 2) - MeasureText(m_text.data(), 30)), static_cast<float>((m_y + m_height / 2) - 15)), 30, 10, m_textColour);
	}
	
private:
	int m_x{};
	int m_y{};
	std::string m_text{};
	int m_width{};
	int m_height{};

	
	const Color m_buttonColour{};
	Color m_colour{m_buttonColour};
	Color m_textColour{};

};

