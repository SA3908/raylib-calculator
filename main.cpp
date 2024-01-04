#include <iostream>

#include <array>

#include <string>

#include <raylib.h>
#include "button.h"
//calculator program


int main()
{
	// set up the window
	int width = 1280;
	int height = 800;

	InitWindow(width, height, "Calculator");
	SetTargetFPS(60);

	

	constexpr Color rectColour{BLUE}; //colour for button
	double timer{};
	double previousTime{};

	
	std::array<Button, 12> calcButton
	{ {
		//row 1
		{13, 685, 140, 100},	//minus/add operator
		{170, 685, 140, 100},	//number 0
		{330, 685, 140, 100},	//decimal point .
		{490, 685, 140, 100},	//operator =
		//row 2
		{13, 570, 140, 100},	//number 1
		{170, 570, 140, 100},	//number 2
		{330, 570, 140, 100},	//number 3
		{490, 570, 140, 100},	//operator / 
		//row 3
		{13, 455, 140, 100},	//number 4
		{170, 455, 140, 100},	//number 5
		{330, 455, 140, 100},	//number 6
		{490, 455, 140, 100}	//operator /

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

		DrawRectangleLines(width / 200, height / 100, width / 2, height - 15, BLACK);
		
		//row 1
		DrawRectangle(13, 685, 140, 100, calcButton[0].getColour());
		DrawRectangle(170, 685, 140, 100, calcButton[1].getColour());
		DrawRectangle(330, 685, 140, 100, calcButton[2].getColour());
		DrawRectangle(490, 685, 140, 100, calcButton[3].getColour());
		//row 2
		DrawRectangle(13, 570, 140, 100, calcButton[4].getColour());
		DrawRectangle(170, 570, 140, 100, calcButton[5].getColour());
		DrawRectangle(330, 570, 140, 100, calcButton[6].getColour());
		DrawRectangle(490, 570, 140, 100, calcButton[7].getColour());
		//row 3
		DrawRectangle(13, 455, 140, 100, calcButton[8].getColour());
		DrawRectangle(170, 455, 140, 100, calcButton[9].getColour());
		DrawRectangle(330, 455, 140, 100, calcButton[10].getColour());
		DrawRectangle(490, 455, 140, 100, calcButton[11].getColour());

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
	CloseWindow();


	return 0;
}