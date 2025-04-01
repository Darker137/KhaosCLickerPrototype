#include "Egg.h"

OrphicEgg::OrphicEgg(const Vector2* screenScale, float offset) { //constructor
	eggTexture = LoadTexture("resources/OrphicEgg.png"); //load the eggs texture
	eggScale = 4; //set the scale of the egg
	defaultSize = { eggTexture.width * eggScale ,eggTexture.height * eggScale }; // calculate the default size of the egg
	eggSize = defaultSize; //set the size of the egg to default size
	eggRotation = 0; //set the rotation of the egg
	maxSize = { defaultSize.x + defaultSize.x / 16, defaultSize.y + defaultSize.y / 16 }; //calculate the max size of the egg
	location = { (screenScale->x - offset) / 2, screenScale->y / 2 }; //set the location of the egg
	SetDrawLocation(); //set the draw location of the egg
	orbitLocation = { (screenScale->x - offset) / 2, screenScale->y / 2 }; //set the orbit location of the egg
}

void OrphicEgg::Draw() { //draws the object
	DrawTextureEx(eggTexture, drawLocation, eggRotation, eggScale, WHITE);
}

bool OrphicEgg::CheckForEggClick(Vector2* mousePos) { //checks if the object has been clicked
	if (CheckForClick(mousePos, *GetDrawLocation(), eggSize)) {
		// increase the size of the egg
		eggSize.x += defaultSize.x / 32; 
		eggSize.y += defaultSize.y / 32;

		if (eggSize.x > maxSize.x) { //if the egg is larger than the max size
			eggSize = maxSize; //set the egg size to the max size
		}
		SetDrawLocation(); //set the draw location of the egg
		eggScale = eggSize.x / eggTexture.width; //calculate new scale of the egg
		return true; //if clicked return true
	}
	return false; //if not clicked return false
}

void OrphicEgg::ReturnToDefaultSize(float* deltatime) { // gradually returns the object to its default size
	if (eggSize.x > defaultSize.x) { //if the egg size is larger than the default size
		eggSize.x -= defaultSize.x / 8 * *deltatime; //reduce the size of the egg
		eggSize.y -= defaultSize.y / 8 * *deltatime;
		if (eggSize.x < defaultSize.x) {
			eggSize = defaultSize;
		}
		SetDrawLocation(); //set draw location of the egg
		eggScale = eggSize.x / eggTexture.width; //update scale of the egg
	}
}


Vector2* OrphicEgg::GetDrawLocation() //returns the location of the object to draw
{
	return &drawLocation;
}

void OrphicEgg::SetDrawLocation() //sets the drawing location of the object to draw
{
	drawLocation = { location.x - eggSize.x / 2, location.y - eggSize.y / 2 };
}

void OrphicEgg::OrbitLocation(float* deltaTime) { //moves the object in an orbit
	location.x = sin(GetTime() * 1.1) * 10 + orbitLocation.x; //calculate the x location of the egg
	location.y = cos(GetTime() * 1.1) * 10 + orbitLocation.y; //calculate the y location of the egg
	SetDrawLocation(); //set the draw location of the egg
}

void OrphicEgg::Update(float* deltatime) { //updates the object
	OrbitLocation(deltatime); //move the object in an orbit
	ReturnToDefaultSize(deltatime); //return the object to its default size
}