#ifndef TOWERS_H
#define TOWERS_H

#include <string>
#include "GeneralFunctions.h"

class Tower { //base class for the towers
protected:
	string name; //name of the tower
	float baseCost; //base cost of the tower
	float wealthPerSecond; //wealth per second of the tower
	int totalOwned; //total of tower type owned
	Texture2D icon; //icon of the tower 
	Color color; //base color of the towers shop button texture
	Color textColor;  // base color of the towers shop button text
	// ADD UPGRADES LATER

public:
	Tower(std::string name, int baseCost, int wealthPerSecond, const char* iconFileName); //constructor
	
	float GenerateWealth(); //generates wealth for the player
	float GetCost(float* multiplier); //returns the cost of the tower
	bool CanBuyTower(float* wealth, float* multiplier); //checks if the player can buy the tower
	void BuyTower(float* wealth, float* multiplier); //buys the tower
	Color* GetColor(); //returns the color of the tower
	Color* GetTextColor(); //returns the text color of the tower
	Texture2D* GetIcon(); //returns the icon of the tower
	string* GetName(); //returns the name of the tower
	int* GetOwned(); //returns the total owned of the tower as a string
};

class TowerManager { //base class for the tower manager
protected:
	vector<Tower> towers; //vector of tower types
	float costMultiplier; //cost multiplier for the towers
	float passiveIncome; //passive income of the player

	float* wealthPointer; // pointer to the wealth of the player
	float* multiplierPointer; // pointer to the multiplier of the player
	float* deltatime; // pointer to the deltatime of the player
public:
	TowerManager(float* wealthPointer, float* deltatime, float* multiplierPointer); //constructor
	bool CanBuyTower(int* towerIndex); //checks if the player can buy the tower from tower index
	void BuyTower(int* towerIndex); //buys the tower from tower index
	Color* GetTowerColor(int* towerIndex); //returns the color of the tower from tower index
	Color* GetTowerTextColor(int* towerIndex); //returns the text color of the tower from tower index
	void UpdateTowerColor(int* towerIndex, Color newColor); //updates the color of the tower from tower index
	void UpdateTowerTextColor(int* towerIndex, Color newColor); //updates the text color of the tower from tower index
	Texture2D* GetTowerIcon(int* towerIndex); //returns the icon of the tower from tower index
	int GetTowerCount(); //returns the total number of tower types
	string* GetTowerName(int* towerIndex); //returns the name of the tower from tower index
	float GetTowerCost(int* towerIndex); //returns the cost of the tower from tower index as a string
	int* GetTowerOwned(int* towerIndex); //returns the total owned of the tower from tower index as a string
	void CalculatePassiveIncome(); //calculates the passive income of the player
	float* GetPassiveIncome(); //returns the passive income of the player
	float CalculateClickValue(); //calculates the click value of the player
};

#endif // !TOWERS_H