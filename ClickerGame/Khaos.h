#ifndef KHAOS_H
#define KHAOS_H

#include "GeneralFunctions.h"

class KhaosBG { //base class for the khaos background object
protected:
	Texture2D khaosBG; //texture of the object
	Color khaosBGColor; //color of the object
	float khaosBGScale; //scale of the object
	Rectangle khaosBGSourceRec; //source rectangle of the object
	Vector2 khaosBGOrigin; //origin of the object
	float khaosBGRotation; //rotation of the object
	float khaosBGRotationSpeed; //rotation speed of the object
	Vector2 khaosBGPosition; //position of the object
	Rectangle khaosBGDestRec; //destination rectangle of the object
public:
	KhaosBG(Vector2 inputLocation, Color colour); //constructor
	void RotateAndScale(float* deltatime); //rotates and scales the object
	void Draw(float* deltatime); //draws the object
};


#endif