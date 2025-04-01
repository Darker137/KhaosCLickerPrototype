#include "GeneralFunctions.h"

void DrawBackingGridCheckers() { //draws the backing grid for testing
	for (int i = 0; i < 1280; i += 32) 
	{
		for (int j = 0; j < 720; j += 32)
		{
			if ((i / 32 + j / 32) % 2 == 0)
			{
				DrawRectangle(i, j, 32, 32, RAYWHITE);
			}
			else
			{
				DrawRectangle(i, j, 32, 32, GRAY);
			}
		}
	}
}

bool CheckForHover(Vector2* mousePos, Vector2 Hitbox, Vector2 size) { //checks if the mouse is hovering over an object
	if (mousePos->x > Hitbox.x && mousePos->x < Hitbox.x + size.x && mousePos->y > Hitbox.y && mousePos->y < Hitbox.y + size.y) {
		return true; //if the mouse is within the hitbox return true
	}
	else {
		return false; //if the mouse is not within the hitbox return false
	}
}

bool CheckForClick(Vector2* mousePos, Vector2 Hitbox, Vector2 size) { //checks if the mouse is within the hitbox of an object
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) //if the left mouse button is pressed
	{
		if (CheckForHover(mousePos, Hitbox, size)) //if the mouse is hovering over the object
		{
			return true; //return true
		}
		else {
			return false; //return false
		}
		return false; //return false
	}
}

string FormatFloat(float number, bool keepDecimal) { //formats a float to a string
	if (keepDecimal) {
		char buffer[32];
		sprintf_s(buffer, "%.6g", number);  // Use shortest representation with up to 6 significant digits
		return std::string(buffer);
	}
	else {
		char buffer[32];
		sprintf_s(buffer, "%.0f", number);  // Use shortest representation with up to 6 significant digits
		return std::string(buffer);
	}
}

string FormatSuffix(float number, bool keepDecimal) { //formats a float to a string with a suffix
	string suffices[5] = { "", "K", "M", "B", "T" }; //array of suffices
	int suffixIndex = 0; //index for the suffix
	float absWealth = abs(number); //absolute value of the number
	while (absWealth >= 1000) { //while the wealth is greater than 1000
		absWealth /= 1000; //divide the wealth by 1000
		suffixIndex++; //increment the suffix index
	}
	if (suffixIndex == 0) { //if the suffix index is 0
		return FormatFloat(number, keepDecimal); //return the wealth as a string
	}
	else { // if the suffix index is not 0
		if (suffixIndex > 4) { // if the suffix index is greater than 4
			suffixIndex = 4; // set the suffix index to 4
		}
		absWealth = floor(absWealth * 100) / 100; // round the wealth to 2 decimal places
		char buffer[20]; // create a buffer
		sprintf_s(buffer, "%.2f", absWealth); // format the wealth to the buffer
		return string(buffer) + suffices[suffixIndex]; // return the wealth as a string with the suffix
	}
}