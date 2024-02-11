#include <iostream>
#include "button.h"	//raylib included in button.h
#include "Calculator.h"
//calculator program


int main()
{
	// set up the window
	int width = 900;
	int height = 785;

	InitWindow(width, height, "Calculator");
	SetTargetFPS(60);
	
	std::string workingDir{GetWorkingDirectory()};
	std::string assets{ workingDir + "/assets/" };
	
	Font fontCalculator = LoadFontEx((assets + "Symbola.ttf").data(), 30, 0, 10378);
	Color operatorColour{ 247, 184, 1, 255 };
	
	double timer{};
	double previousTime{};
	
	
	std::array<Button, 24> calcButton
	{ {
		//row 1
		{10, 700, 130, 90,  "+/-"},	//minus/add operator
		{145, 700, 130, 90, "0"},	//number 0
		{280, 700, 130, 90, "."},	//decimal point .
		{415, 700, 130, 90, "=", Color{100, 190, 35, 225}, BLACK},	//operator =
		//row 2
		{10, 605, 130, 90, "1"},	//number 1
		{145, 605, 130, 90, "2"},	//number 2
		{280, 605, 130, 90, "3"},	//number 3
		{415, 605, 130, 90, Constants::div, operatorColour, BLACK},	//operator / 
		//row 3
		{10, 510, 130, 90, "4"},	//number 4
		{145, 510, 130, 90, "5"},	//number 5
		{280, 510, 130, 90, "6"},	//number 6
		{415, 510, 130, 90,  Constants::mul, operatorColour, BLACK},	//operator *
		//row 4
		{10, 415, 130, 90, "7"},	//number 7
		{145, 415, 130, 90, "8"},	//number 8
		{280, 415, 130, 90, "9"},	//number 9
		{415, 415, 130, 90, "+", operatorColour, BLACK},	//operator +
		//row 5
		{10, 320, 130, 90, Constants::sqrt},	//sqrt
		{145, 320, 130, 90, "^"},	//square
		{280, 320, 130, 90, Constants::fraction},	// fraction
		{415, 320, 130, 90, "-", operatorColour, BLACK},	//operator -
		//row 6
		{10, 225, 130, 90, "("},	// bracket (
		{145, 225, 130, 90, ")"},	//bracket )
		{280, 225, 130, 90, "CE", Color{255, 16, 40, 255}, BLACK},	// CE - clear entry
		{415, 225, 130, 90, Constants::backspace, Color{255, 16, 40, 255}, BLACK},	// backspace
	} };
	constexpr auto calcButtonSize{ std::ssize(calcButton) };
	Calculator session{};

	//loop
	while (!WindowShouldClose())
	{
		
		timer += GetFrameTime();
		// drawing
		BeginDrawing();
		ClearBackground(Color{ 41, 46, 55, 255 });
		
		if (timer - previousTime >= 0.1) //resets button to original colour.
		{
			for (std::ptrdiff_t index{ 0 }; index < calcButtonSize; ++index)
			{
				calcButton[index].colourChange();	
			}
		}

		DrawRectangleLines(4, 8, 542, 785, BLACK); //black outline for calculator
		
		for (std::ptrdiff_t index{ 0 }; index < calcButtonSize; ++index) //draw rectangular buttons then check if the buttons are pressed
		{
			
			calcButton[index].drawRectButton();
			calcButton[index].drawTextMiddle(fontCalculator);
			session.drawExpression(fontCalculator, RAYWHITE);
			if (calcButton[index].buttonPressed())
			{
				previousTime = timer;
				calcButton[index].colourChange(RED);
				session.express(calcButton, index);

			}
		}
		while (GetKeyPressed() > 0) //check if keyboard button is pressed
		{
			previousTime = timer;
			int key{ GetCharPressed() };
			session.express(key, calcButton);
		}
		EndDrawing();
	}

	// cleanup
	UnloadFont(fontCalculator);
	CloseWindow();

	debug(session);

	return 0;
}
void debug(Calculator& session)
{
	for (std::ptrdiff_t index{ 0 }; index < std::ssize(session.m_output); ++index)
	{
		std::cout << session.m_output[index] << " ";
		
	}
	std::cout << '\n' << "Size of m_evaluated: " << std::ssize(session.m_evaluated);

	if (session.m_parsed)
		std::cout << '\n' << "The answer is: " << session.m_evaluated.back();
}