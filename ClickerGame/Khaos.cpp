#include "Khaos.h"

KhaosBG::KhaosBG(Vector2 inputLocation, Color color) { //constructor
	khaosBG = LoadTexture("resources/KhaosBG.png"); //load the khaosBG texture
	khaosBGColor = color; //set the color
	khaosBGScale = 4; //set the scale
	khaosBGSourceRec = { 0.0f, 0.0f, (float)khaosBG.width, (float)khaosBG.height }; //set the source rectangle
	khaosBGOrigin = { (float)khaosBG.width * khaosBGScale / 2, (float)khaosBG.height * khaosBGScale / 2 }; //set the origin
	khaosBGRotation = 0; //set the rotation
	khaosBGRotationSpeed = 5; //set the rotation speed
	khaosBGPosition = inputLocation; //set the position
	khaosBGDestRec = { khaosBGPosition.x, khaosBGPosition.y, (float)khaosBG.width * khaosBGScale, (float)khaosBG.height * khaosBGScale }; //set the destination rectangle
}

void KhaosBG::RotateAndScale(float* deltatime) { //rotates and scales the object
	khaosBGRotation += khaosBGRotationSpeed * *deltatime; //rotate the object
	khaosBGScale = sin(GetTime() * 1.1) * 0.1 + 4; //scale the object
	khaosBGDestRec = { khaosBGPosition.x, khaosBGPosition.y, (float)khaosBG.width * khaosBGScale, (float)khaosBG.height * khaosBGScale }; //update the destination rectangle
	khaosBGOrigin = { (float)khaosBG.width * khaosBGScale / 2, (float)khaosBG.height * khaosBGScale / 2 }; //update the origin
}


void KhaosBG::Draw(float* deltatime) { //draws the object
	RotateAndScale(deltatime);  // rotate and scale the object
	DrawTexturePro(khaosBG, khaosBGSourceRec, khaosBGDestRec, khaosBGOrigin, khaosBGRotation, khaosBGColor); //draw the object
}
