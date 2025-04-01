#include "player.h"

Player::Player(float* deltatime) : deltatime(deltatime) { //constructor
	wealth = 0; //set the wealth to 0
	clickValue = 1; //set the click value to 1
	totalClicks = 0; //set the total clicks to 0
	multiplier = 1; //set the multiplier to 1
	towerManager = new TowerManager(&wealth, deltatime, &multiplier); //create a new tower manager
}

float* Player::GetWealth() { //returns the wealth of the player
	return &wealth;
}

float* Player::GetPassiveIncome() { //returns the passive income of the player
	return towerManager->GetPassiveIncome();
}

void Player::UpdateWealth() { //updates the wealth of the player
	wealth += *towerManager->GetPassiveIncome() * *deltatime * multiplier;
}

float Player::GetClickValue() { //updates the click value of the player
	return towerManager->CalculateClickValue();
}

void Player::UpdateMultiplier(float* newMultiplier) { //updates the multiplier of the player
	multiplier = *newMultiplier;
}

void Player::Update() { //updates the player
	UpdateWealth(); //update the wealth
}

void Player::CreateClickText() { //creates a click text
	ClickText clickText; //create a new click text
	clickText.text = FormatSuffix(clickValue * multiplier, true); //set the text of the click text
	clickText.location = { (float)GetMouseX() + (rand() % 20) - 10, (float)GetMouseY() }; //set the location of the click text
	clickText.color = WHITE; //set the color of the click text
	clickTexts.push_back(clickText); //add the click text to the vector
}

void Player::IsClicked(bool clicked) { //checks if the player has clicked
	if (clicked) { //if the player has clicked
		clickValue = GetClickValue() * multiplier; //update the click value
		wealth += clickValue; //add the click value to the wealth
		totalClicks++; //increment the total clicks
		CreateClickText(); //create a click text
	}
}

void Player::DrawClickText() { //draws, updates and removes the click text
	for (int i = 0; i < clickTexts.size(); i++) {  //for each click text
		DrawText(clickTexts[i].text.c_str(), clickTexts[i].location.x, clickTexts[i].location.y, 32, clickTexts[i].color); //draw the click text
		clickTexts[i].location.y -= 1; //move the click text up
		clickTexts[i].color.a -= 3; //reduce the alpha / opacity of the click text
		if (clickTexts[i].color.a <= 0) { //if the click text is no longer visible
			clickTexts.erase(clickTexts.begin() + i); //remove the click text
		}
	}
}

TowerManager* Player::GetTowerManager() { //returns the tower manager of the player
	return towerManager;
}