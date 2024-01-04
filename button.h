#pragma once
#include <raylib.h>


class Button
{
public:
	
	Color getColour() const { return m_colour; }
	
	
	Button(int x, int y, int width, int height, Color colour = BLUE)
		:m_x{ x }, m_y{ y }, m_width{ width }, m_height{height}, m_colour{colour}
	{

	}
	bool buttonPressed() const
	{
		if (GetMouseX() >= m_x && GetMouseX() <= (m_x + m_width) && GetMouseY() >= m_y && GetMouseY() < (m_y + m_height) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return true;
		}
		else
			return false;
	}
	void colourChange(Color colourChoice)
	{
		m_colour = colourChoice;
	}
	
private:
	int m_x{};
	int m_y{};
	int m_width{};
	int m_height{};
	Color m_colour{};
	
};

