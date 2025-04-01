#ifndef CURSOR_H
#define CURSOR_H

#include "GeneralFunctions.h"

class Cursor {
protected:
	Texture2D cursorTexture; //texture of the cursor
	int cursorScale; //scale of the cursor
public: 
	Cursor(); //constructor
	void Draw(Vector2* cursorLocation); //draws the cursor
};

#endif
