#ifndef EGG_H
#define EGG_H

#include "GeneralFunctions.h"

class OrphicEgg{
protected:
	Texture2D eggTexture; //texture of the object
	float eggScale; //scale of the object
	Vector2 defaultSize;
	Vector2 eggSize; //size of the object
	float eggRotation; //rotation of the object
	Vector2 maxSize;
	Vector2 location; //location of the object
	Vector2 drawLocation; //location of the object to draw
	Vector2 orbitLocation; //location of the point to orbit
public:
	OrphicEgg(const Vector2* screenScale, float offset); //constructor

	void Draw(); //draws the object

	bool CheckForEggClick(Vector2* mousePos); //checks if the object has been clicked
	void ReturnToDefaultSize(float* deltatime); // gradually returns the object to its default size

	Vector2* GetDrawLocation(); //returns the location of the object to draw
	void SetDrawLocation(); //sets the location of the object to draw

	void OrbitLocation(float* deltatime); //moves the object in an orbit

	void Update(float* deltatime); //updates the object
};



#endif
