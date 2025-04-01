#include "UserInterface.h"

// constructor for the user interface class
UserInterface::UserInterface(const Vector2* screenScaleReference, TowerManager* towerManager) : screenScale(screenScaleReference), towerManager(towerManager){

	shopButtonBackground = LoadTexture("resources/ShopButton.png"); // load the shop button background texture
	shopButtonSize = { (float)shopButtonBackground.width * 4, (float)shopButtonBackground.height * 4 }; // calculate the size of the shop button
	shopButtonTextSize = (shopButtonSize.y - 28) / 2; // calculate the size of the shop button text
	shopMenuLocation = { screenScale->x - shopButtonSize.x, 0 }; // calculate the location of the shop menu
	shopButtonTextLocation = { shopMenuLocation.x + 108, shopMenuLocation.y + 12 }; // calculate the location of the shop button text

	shopBorder = LoadTexture("resources/ShopBorder.png"); // load the shop border texture
	shopBorderLength = ceil(screenScaleReference->y / ((float)shopBorder.height * 4)); // calculate the size of the border
	shopSize = { screenScaleReference->x - shopMenuLocation.x, screenScaleReference->y }; // calculate the size of the shop

	wealthIncomeBackground = LoadTexture("resources/WealthIncomeBackground.png"); // load the wealth and income background texture
	wealthIncomeBackgroundSize = { (float)wealthIncomeBackground.width * 4, (float)wealthIncomeBackground.height * 4 }; // calculate the size of the wealth and income background
	wealthIncomeLocation = { ((screenScaleReference->x - shopButtonSize.x - (shopBorder.width * 4)) / 2) - (wealthIncomeBackground.width * 4 / 2), 0 }; // calculate the location of the wealth and income
	wealthTextSize = ((wealthIncomeBackgroundSize.y / 2)) - 16; // calculate the size of the wealth text
	wealthTextLocation = { wealthIncomeLocation.x + (wealthIncomeBackgroundSize.x / 2) , wealthIncomeLocation.y + 16 }; // calculate the location of the wealth text
	incomeTextSize = wealthTextSize * 0.8; // calculate the size of the income text
	incomeTextLocation = { wealthIncomeLocation.x + (wealthIncomeBackgroundSize.x / 2) , wealthIncomeLocation.y + 8 + wealthTextSize + 12 }; // calculate the location of the income text
	// set the suffices for the wealth text
	suffices[0] = " "; 
	suffices[1] = "K";
	suffices[2] = "M";
	suffices[3] = "B";
	suffices[4] = "T";
	
	backButtonTexture = LoadTexture("resources/BackButton.png"); // load the back button texture
	backButtonScale = 4; // set the scale of the back button
	backButtonSize = { (float)backButtonTexture.width * backButtonScale, (float)backButtonTexture.height * backButtonScale }; // calculate the size of the back button
	backButtonLocation = { 0, 0 }; // set the location of the back button
	backButtonColor = WHITE; // set the color of the back button
}

void UserInterface::DrawButton(int* index) { //draws the shop button
	DrawTextureEx(shopButtonBackground, {shopMenuLocation.x, shopMenuLocation.y + shopButtonSize.y * *index}, 0, 4, *towerManager->GetTowerColor(index)); // draw the background of the button
	DrawTextureEx(*towerManager->GetTowerIcon(index), { shopMenuLocation.x, shopMenuLocation.y + shopButtonSize.y * *index }, 0, 2, *towerManager->GetTowerColor(index)); // draw the icon of the button
}

void UserInterface::DrawShopDetails(int* index) { //draws the details of the shops
	// draw the text of the button
	DrawText(towerManager->GetTowerName(index)->c_str(), shopButtonTextLocation.x, shopButtonTextLocation.y + shopButtonSize.y * *index, shopButtonTextSize, *towerManager->GetTowerTextColor(index)); 
	// draw the cost and owned text of the button
	DrawText(("Cost: " + FormatSuffix(towerManager->GetTowerCost(index), false)).c_str(), shopButtonTextLocation.x, shopButtonTextLocation.y + shopButtonSize.y * *index + +4 + shopButtonTextSize, shopButtonTextSize, *towerManager->GetTowerTextColor(index));
	// draw the owned text of the button
	DrawText(("Owned: " + FormatSuffix(*towerManager->GetTowerOwned(index), false)).c_str(), shopButtonTextLocation.x + ((shopButtonSize.x - 112) / 2), shopButtonTextLocation.y + shopButtonSize.y * *index + 4 + shopButtonTextSize, shopButtonTextSize, *towerManager->GetTowerTextColor(index));
}

void UserInterface::DrawShopBorder() { //draws the border of the shop
	for (int i = 0; i < shopBorderLength; i++) { //for border length
		DrawTextureEx(shopBorder, { shopMenuLocation.x - shopBorder.width * 4, (float)i * shopBorder.height * 4 }, 0, 4, WHITE); //draw the border
	}
}

void UserInterface::DrawShop() { //draws the shop
	DrawRectangle(shopMenuLocation.x, shopMenuLocation.y, shopSize.x, shopSize.y, Color{ 71, 23, 0,255 }); // draw the shop background
	for (int i = 0; i < towerManager->GetTowerCount(); i++) { //for each tower type
		DrawButton(&i); //draw the button 
		DrawShopDetails(&i); //draw the details
	}
	DrawShopBorder(); //draw the border
}

string UserInterface::GetWealthText(float* wealthPointer) { //returns the wealth text
	int suffixIndex = 0; // set the suffix index
	double absWealth = abs(*wealthPointer); // get the absolute value of the wealth
	while (absWealth >= 1000) { // while the wealth is greater than 1000
		absWealth /= 1000; // divide the wealth by 1000
		suffixIndex++; // increment the suffix index
	}
	if (suffixIndex == 0) { // if the suffix index is 0
		return to_string((int)absWealth); // return the wealth as an integer
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

void UserInterface::DrawWealthIncome(float* wealthPointer) { //draws the wealth and income
	string wealthText = "Ambrosia: " + FormatSuffix(*wealthPointer, false); // get the wealth text
	string incomeText = FormatSuffix(*towerManager->GetPassiveIncome(), true) + " /s"; // get the income text

	int wealthTextWidth = MeasureText(wealthText.c_str(), wealthTextSize); // get the width of the wealth text
	int incomeTextWidth = MeasureText(incomeText.c_str(), incomeTextSize); // get the width of the income text

	DrawTextureEx(wealthIncomeBackground, wealthIncomeLocation, 0, 4, WHITE); // draw the background of the wealth and income
	DrawText(wealthText.c_str(), wealthTextLocation.x - wealthTextWidth / 2, wealthTextLocation.y, wealthTextSize, WHITE); // draw the wealth text
	DrawText(incomeText.c_str(), incomeTextLocation.x - incomeTextWidth / 2, incomeTextLocation.y, incomeTextSize, WHITE); // draw the income text

}

void UserInterface::DrawBackButton() { //draws the back button
	DrawTextureEx(backButtonTexture, backButtonLocation, 0, backButtonScale, backButtonColor); // draw the back button
}


void UserInterface::Draw(float* wealthPointer) { //draws the user interface
	DrawShop(); // draw the shop
	DrawWealthIncome(wealthPointer); // draw the wealth and income
	DrawBackButton(); // draw the back button
}


void UserInterface::ShopButtonChecks(Vector2* mousePos) { //checks the shop buttons
	for (int i = 0; i < towerManager->GetTowerCount(); i++) { //for each tower type
		if (towerManager->CanBuyTower(&i)) { //if the player can buy the tower
			if (CheckForHover(mousePos, { shopMenuLocation.x, shopMenuLocation.y + shopButtonSize.y * i }, shopButtonSize)) { //if the mouse is hovering over the button
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { //if the left mouse button is pressed
					towerManager->BuyTower(&i); //buy the tower
					towerManager->UpdateTowerColor(&i, WHITE); //update the color of the tower
					towerManager->UpdateTowerTextColor(&i, WHITE); //update the text color of the tower
					towerManager->CalculatePassiveIncome(); //calculate the passive income
				}
				else { //if the left mouse button is not pressed
					towerManager->UpdateTowerColor(&i, LIGHTGRAY); //update the color of the tower
					towerManager->UpdateTowerTextColor(&i, LIGHTGRAY); //update the text color of the tower
				}
			}
			else { //if the mouse is not hovering over the button
				towerManager->UpdateTowerColor(&i, WHITE); //update the color of the tower
				towerManager->UpdateTowerTextColor(&i, WHITE); //update the text color of the tower
			}
		}
		else { //if the player cannot buy the tower
			towerManager->UpdateTowerColor(&i, GRAY); //update the color of the tower
			towerManager->UpdateTowerTextColor(&i, GRAY); //update the text color of the tower
		}
	}
}

GameState UserInterface::BackButtonCheck(Vector2* mousePos) { //checks the back button
	if (CheckForHover(mousePos, backButtonLocation, backButtonSize)) { //if the mouse is hovering over the back button
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { //if the left mouse button is pressed
			backButtonColor = DARKGRAY; //set the color of the back button
			return Title; //return game state title screen
		}
		else { //if the left mouse button is not pressed
			backButtonColor = LIGHTGRAY; //set the color of the back button
			return Gameplay; //return game state gameplay
		}
	}
	else {
		backButtonColor = WHITE; //set the color of the back button
		return Gameplay; //return game state gameplay
	}
}

Vector2* UserInterface::GetShopButtonSize() { //returns the size of the shop button
	return &shopButtonSize; 
}

Vector2 UserInterface::GetBorderSize() { //returns the size of the border
	return { (float)shopBorder.width * 4, (float)shopBorder.height * 4 };
}