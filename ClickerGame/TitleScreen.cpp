#include "TitleScreen.h"

TitleButtons::TitleButtons(const char* defaultFileName, const char* hoverFileName, const char* pressedFileName, Vector2 location) //constructor
{
	buttonDefaultTexture = LoadTexture(defaultFileName); //load the default texture
	buttonHoverTexture = LoadTexture(hoverFileName); //load the hover texture
	buttonPressedTexture = LoadTexture(pressedFileName); //load the pressed texture
	buttonScale = 4; //set the scale of the button
	buttonDimensions = { buttonDefaultTexture.width * buttonScale, buttonDefaultTexture.height * buttonScale }; //calculate dimensions of the button
	buttonLocation = location;  //set the location of the button

}

bool TitleButtons::DrawButton(Vector2* mouseLocation) { //draws the button
	if (CheckForHover(mouseLocation, buttonLocation, buttonDimensions)) { //if the mouse is hovering over the button
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { //if the left mouse button is pressed
			DrawTextureEx(buttonPressedTexture, buttonLocation, 0, buttonScale, WHITE); //draw the pressed texture
			return true; //return true
		}
		else {
			DrawTextureEx(buttonHoverTexture, buttonLocation, 0, buttonScale, WHITE); //draw the hover texture
			return false; //return false
		}
	}
	else { //if the mouse is not hovering over the button
		DrawTextureEx(buttonDefaultTexture, buttonLocation, 0, buttonScale, WHITE); //draw the default texture
		return false; //return false
	}
}

GameState TitleButtons::PressedAction() { return Title; } //default action for the button

//play button class constructor
PlayButton::PlayButton(Vector2 location) : TitleButtons("resources/PlayButtonDefault.png", "resources/PlayButtonHover.png", "resources/PlayButtonPressed.png", location) {}

//override function for when the button is pressed to change the game state
GameState PlayButton::PressedAction() { return Gameplay; }

//close button class constructor 
CloseButton::CloseButton(Vector2 location) : TitleButtons("resources/CloseButtonDefault.png", "resources/CloseButtonHover.png", "resources/CloseButtonPressed.png", location) {}

// override function for when the button is pressed to change the game state
GameState CloseButton::PressedAction() { return Close; }

// Title screen constructor
TitleScreen::TitleScreen(const Vector2* screenScale, GameState* gameState) {
	titleTexture = LoadTexture("resources/Title.png"); //load the title texture
	titleScale = 4; //set the scale of the title
	titleDimensions = { titleTexture.width * titleScale, titleTexture.height * titleScale }; //calculate the dimensions of the title
	titleLocation = { (screenScale->x / 2) - (titleDimensions.x / 2), 32 }; //set the location of the title

	templeTexture = LoadTexture("resources/TitleTemple.png"); //load the temple texture
	templeScale = 4; //set the scale of the temple
	templeDimensions = { templeTexture.width * templeScale, templeTexture.height * templeScale }; //calculate the dimensions of the temple
	templeLocation = { (screenScale->x / 2) - (templeDimensions.x / 2), 32 + titleDimensions.y + 64 }; //set the location of the temple

	buttons.push_back(new PlayButton({ 32, 32 })); //add the play button to the vector
	buttons.push_back(new CloseButton({ 32, 160 })); //add the close button to the vector

	gameStatePtr = gameState; //set the game state pointer
}

void TitleScreen::DrawTitle() { //draws the title
	DrawTextureEx(titleTexture, { titleLocation.x + 4, titleLocation.y + 4 }, 0, titleScale, BLACK); 
	DrawTextureEx(titleTexture, titleLocation, 0, titleScale, WHITE);
}

void TitleScreen::DrawTemple() { //draws the temple and floor
	DrawTextureEx(templeTexture, { templeLocation.x, templeLocation.y}, 0, templeScale, WHITE);
	DrawRectangle(0, templeLocation.y + templeDimensions.y, GetScreenWidth(), GetScreenHeight() - (templeLocation.y + templeDimensions.y), Color{71, 23, 0,255});
}

void TitleScreen::DrawButtons(Vector2* mouseLocation) { //draws the buttons
	for (int i = 0; i < buttons.size(); i++) { //for each button
		if (buttons[i]->DrawButton(mouseLocation)) { //if the button is pressed and draw
			*gameStatePtr = buttons[i]->PressedAction(); //change the game state
			cout << *gameStatePtr << endl; //print the game state
			break; //break out of the loop
		}
	}
}

void TitleScreen::Draw(Vector2* mouseLocation) //draws the title screen
{
	DrawTitle(); //draw the title
	DrawTemple(); //draw the temple
	DrawButtons(mouseLocation); //draw the buttons
}


Vector2 TitleScreen::GetCenter() { //returns the center of the title
	return { titleLocation.x + (titleDimensions.x / 2),titleLocation.y + (titleDimensions.y / 2) };
}
