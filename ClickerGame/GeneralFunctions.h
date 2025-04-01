#ifndef GENERALFUNCTIONS_H
#define GENERALFUNCTIONS_H

#include "raygui.h"                 // Required for GUI controls
#include "raylib.h"                 //Main Raylib core library
#include "raymath.h"                //Raylib Math functions library
#include "rlgl.h"                   //RayLib OpenGL library
#include <iostream>                 //Required for cout and cin
#include <vector>                   //Required for vectors	
#include <string>                   //Required for strings
#include <iomanip>

using namespace std;

enum GameState { //enum for the game states
	Title,
	Gameplay,
	Close
};


void DrawBackingGridCheckers(); //draws the backing grid for the game

bool CheckForHover(Vector2* mousePos, Vector2 Hitbox, Vector2 size); //checks if the mouse is hovering over an object

bool CheckForClick(Vector2* mousePos, Vector2 Hitbox, Vector2 size); //checks if the mouse is within the hitbox of an object

string FormatFloat(float number, bool keepDecimal); //formats a float to a string

string FormatSuffix(float number, bool keepDecimal); //formats a float to a string with a suffix

#endif