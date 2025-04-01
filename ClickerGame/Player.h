#ifndef PLAYER_H
#define PLAYER_H

#include "GeneralFunctions.h"
#include "Towers.h"
struct ClickText { //struct for the click text
	string text;
	Vector2 location;
	Color color;
};

class Player { //base class for the player
protected:
	float wealth; //total wealth of the player

	int totalClicks; //total clicks the player has made
	float clickValue; //value of each click
 
	float multiplier; //multiplier for the click value

	TowerManager* towerManager; //tower manager for the player

	float* deltatime; //deltatime for the player

	vector<ClickText> clickTexts; //vector of click texts
	
public:
	Player(float* deltatime); //constructor

	float* GetWealth(); //returns the wealth of the player
	float* GetPassiveIncome(); //returns the passive income of the player
	void UpdateWealth(); //updates the wealth of the player
	float GetClickValue(); //updates the click value of the player
	void UpdateMultiplier(float* newMultiplier); //updates the multiplier of the player
	void Update(); //updates the player

	void CreateClickText(); //creates a click text
	void IsClicked(bool clicked); //checks if the player has clicked
	void DrawClickText(); //draws the click text

	TowerManager* GetTowerManager(); //returns the tower manager of the player


};


#endif