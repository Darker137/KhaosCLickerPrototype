#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "GeneralFunctions.h"

class TitleButtons { //base class for the title buttons
protected:
	Texture2D buttonDefaultTexture; //texture of the button
	Texture2D buttonHoverTexture; //texture of the button when hovered over
	Texture2D buttonPressedTexture; //texture of the button when pressed
	float buttonScale; //scale of the button
	Vector2 buttonDimensions; //dimensions of the button
	Vector2 buttonLocation; //location of the button
public:
	TitleButtons(const char* defaultFileName, const char* hoverFileName, const char* pressedFileName, Vector2 location); //constructor
	virtual GameState PressedAction(); //Override this function to add functionality to the button
	bool DrawButton(Vector2* mouseLocation); //draws the button
};

class PlayButton : public TitleButtons { //class for the play button
public:
	PlayButton(Vector2 location); //constructor
	GameState PressedAction() override; //override function for when the button is pressed
};

class CloseButton : public TitleButtons { //class for the close button
public:
	CloseButton(Vector2 location); //constructor
	GameState PressedAction() override; //override function for when the button is pressed
};

class TitleScreen { //base class for the title screen
protected:
	Texture2D titleTexture; //texture of the title
	float titleScale; //scale of the title
	Vector2 titleDimensions; //dimensions of the title
	Vector2 titleLocation; //location of the title

	Texture2D templeTexture; //texture of the temple
	float templeScale; //scale of the temple
	Vector2 templeDimensions; //dimensions of the temple
	Vector2 templeLocation; //location of the temple

	vector<TitleButtons*> buttons; //vector of buttons
	GameState* gameStatePtr; //pointer to the game state

public:
	TitleScreen(const Vector2* screenScale, GameState* gameState); //constructor
	void DrawTitle(); //draws the title
	void DrawTemple(); //draws the temple
	void DrawButtons(Vector2* mouseLocation); //draws the buttons
	void Draw(Vector2* mouseLocation); //draws the title screen
	Vector2 GetCenter(); //returns the center of the title
};



#endif