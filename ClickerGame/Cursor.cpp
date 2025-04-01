#include "Cursor.h"

Cursor::Cursor() {
	cursorTexture = LoadTexture("resources/Cursor.png");
	cursorScale = 2;
}

void Cursor::Draw(Vector2* cursorLocation)
{
	DrawTextureEx(cursorTexture, *cursorLocation, 0, cursorScale, WHITE);
}

