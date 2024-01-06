#include <iostream>

#include <array>

#include <string>

#include <raylib.h>
#include "button.h"
#include "Calculator.h"
//calculator program


int main()
{
	// set up the window
	int width = 1280;
	int height = 800;

	InitWindow(width, height, "Calculator");
	SetTargetFPS(60);
	
	std::string workingDir{GetWorkingDirectory()};
	std::string assets{ workingDir + "/assets/" };
	
	Font fontCalculator = LoadFontEx((assets + "Symbola.ttf").data(), 30, 0, 10378);
	
	
	double timer{};
	double previousTime{};
	
	
	std::array<Button, 24> calcButton
	{ {
		//row 1
		{10, 700, 130, 90,  "+/-"},	//minus/add operator
		{145, 700, 130, 90, "0"},	//number 0
		{280, 700, 130, 90, "."},	//decimal point .
		{415, 700, 130, 90, "="},	//operator =
		//row 2
		{10, 605, 130, 90, "1"},	//number 1
		{145, 605, 130, 90, "2"},	//number 2
		{280, 605, 130, 90, "3"},	//number 3
		{415, 605, 130, 90, "\xc3\xb7"},	//operator / 
		//row 3
		{10, 510, 130, 90, "4"},	//number 4
		{145, 510, 130, 90, "5"},	//number 5
		{280, 510, 130, 90, "6"},	//number 6
		{415, 510, 130, 90, "\xc3\x97"},	//operator *
		//row 4
		{10, 415, 130, 90, "7"},	//number 7
		{145, 415, 130, 90, "8"},	//number 8
		{280, 415, 130, 90, "9"},	//number 9
		{415, 415, 130, 90, "+"},	//operator +
		//row 5
		{10, 320, 130, 90, "\xe2\x88\x9a"},	//sqrt
		{145, 320, 130, 90, "x\xc2\xb2"},//square
		{280, 320, 130, 90, "CE"},	// CE - clear entry
		{415, 320, 130, 90, "-"},	//operator -
		//row 6
		{10, 225, 130, 90, "("},	// bracket (
		{145, 225, 130, 90, ")"},	//bracket )
		{280, 225, 130, 90, "\xc2\xbd"},	// fraction
		{415, 225, 130, 90, "\xe2\x8c\xab"},	// backspace
	} };
	constexpr auto calcButtonSize{ std::ssize(calcButton) };

	//loop
	while (!WindowShouldClose())
	{
		
		timer += GetFrameTime();
		// drawing
		BeginDrawing();
		ClearBackground(RAYWHITE);
		
		if (timer - previousTime >= 0.1) //resets button to original colour.
		{
			for (std::ptrdiff_t index{ 0 }; index < calcButtonSize; ++index)
			{
				calcButton[index].colourChange(BLUE);	
			}
		}

		DrawRectangleLines(6, 8, 590, 785, BLACK);
		
		
		for (std::ptrdiff_t index{ 0 }; index < calcButtonSize; ++index) //draw rectangular blue buttons
		{
			//calcButton[index].drawTextMiddle();
			calcButton[index].drawRectButton();
			calcButton[index].drawTextMiddle(fontCalculator);
		}

		for (std::ptrdiff_t index{ 0 }; index < calcButtonSize; ++index)
		{
			if (calcButton[index].buttonPressed())
			{
				previousTime = timer;
				calcButton[index].colourChange(RED); //TO DO: make buttons do something
				
			}
		}

		EndDrawing();
	}

	// cleanup
	UnloadFont(fontCalculator);
	CloseWindow();


	return 0;
}