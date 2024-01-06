#pragma once



class Button
{
public:
	
	Color getColour() const { return m_colour; }
	
	
	Button(int x, int y, int width, int height, const std::string& text, Color colour = BLUE)
		:m_x{ x }, m_y{ y }, m_width{ width }, m_height{height}, m_colour{colour}, m_text{text}
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
	void drawRectButton()
	{
		DrawRectangle( m_x, m_y, m_width, m_height, m_colour);
	}
	void drawTextMiddle(const Font& fontCalculator)
	{
		DrawTextEx(fontCalculator, m_text.data(), Vector2(static_cast<float>((m_x + m_width / 2) - MeasureText(m_text.data(), 30)), static_cast<float>((m_y + m_height / 2) - 15)), 30, 10, BLACK);
	}
	
private:
	int m_x{};
	int m_y{};
	std::string m_text{};
	int m_width{};
	int m_height{};
	Color m_colour{};
	
	
};

