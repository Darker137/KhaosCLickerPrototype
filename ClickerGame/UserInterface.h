#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "GeneralFunctions.h"
#include "Player.h"
#include "TitleScreen.h"


class UserInterface { //base class for the user interface
protected:
	TowerManager* towerManager; //tower manager for the player
	const Vector2* screenScale; //scale of the screen
	Texture2D shopBorder; //border of the shop
	int shopBorderLength; //size of the border

	Texture2D shopButtonBackground; //background of the shop button
	Vector2 shopButtonSize; //size of the shop button
	Vector2 shopMenuLocation; //location of the shop menu
	int shopButtonTextSize; //size of the shop button text
	Vector2 shopButtonTextLocation; //location of the shop button text
	Vector2 shopSize; //size of the shop

	Texture2D wealthIncomeBackground; //background of the wealth and income
	Vector2 wealthIncomeBackgroundSize; //size of the wealth and income background
	Vector2 wealthIncomeLocation; //location of the wealth and income
	int wealthTextSize; //size of the wealth text
	Vector2 wealthTextLocation; //location of the wealth text
	int incomeTextSize; //size of the income text
	Vector2 incomeTextLocation; //location of the income text
	const char* suffices[5]; //suffices for the wealth text

	Texture2D backButtonTexture; //texture of the back button
	int backButtonScale; //scale of the back button
	Vector2 backButtonSize; //size of the back button
	Vector2 backButtonLocation; //location of the back button
	Color backButtonColor; //color of the back button

public:
	UserInterface(const Vector2* screenScaleReference, TowerManager* towerManager); //constructor

	void DrawButton(int* index); //draws the shop button
	void DrawShopDetails(int* index); //draws the details of the shop
	void DrawShopBorder(); //draws the border of the shop
	void DrawShop(); //draws the shop
	string GetWealthText(float* wealthPointer); //returns the wealth text
	void DrawWealthIncome(float* wealthPointer);
	void DrawBackButton(); //draws the back button
	void Draw(float* wealthPointer); //draws the user interface
	void ShopButtonChecks(Vector2* mousePos); //checks the shop buttons
	GameState BackButtonCheck(Vector2* mousePos); //checks the back button
	Vector2* GetShopButtonSize(); //returns the size of the shop button
	Vector2 GetBorderSize(); //returns the size of the border
};

#endif