#include "Egg.h"
#include "Player.h"
#include "UserInterface.h"
#include "Khaos.h"
#include "TitleScreen.h"
#include "Cursor.h"
#include "raylib.h"




//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

	const Vector2 screenScale = { 1280, 720 };

    InitWindow(screenScale.x, screenScale.y, "Khaos Clicker");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

	GameState gameState = Title; // Set the game state to the default title screen

	Vector2 mouseLocation{}; // Create a vector2 for the mouse location
	float deltatime{}; // Create a float for the deltatime

	Cursor* cursor = new Cursor(); // Create a new cursor object

    // Main game loop
	while (!WindowShouldClose() && gameState != Close)    // Detect window close button or ESC key or close game state
    {

		switch (gameState) { // Switch statement for the game state
		case(Title): // Title screen
        {
			TitleScreen* titleScreen = new TitleScreen(&screenScale, &gameState); // Create a new title screen object
			KhaosBG* khaosBG = new KhaosBG(titleScreen->GetCenter(), WHITE); // Create a new background object

			while (gameState == Title && !WindowShouldClose()) { // While the game state is the title screen and the window is not closed

				mouseLocation = GetMousePosition(); // Get the mouse location
				deltatime = GetFrameTime(); // Get the deltatime

				BeginDrawing(); // Begin drawing

				ClearBackground(BLACK); // set the background to black
                
				//DrawBackingGridCheckers(); // Draw the backing grid checkers to help with layout and scaling
				HideCursor(); // Hide the cursor
				khaosBG->Draw(&deltatime); // Draw the background
				titleScreen->Draw(&mouseLocation); // Draw the title screen
				cursor->Draw(&mouseLocation); // Draw the cursor

				EndDrawing(); // End drawing
            }

			delete titleScreen; // Delete the title screen object
			delete khaosBG; // Delete the background object
			break; // Break out of the switch statement
        }
        case(Gameplay):
        {
            Player* player = new Player(&deltatime); // Create a new player object
            UserInterface* userInterface = new UserInterface(&screenScale, player->GetTowerManager()); // Create a new user interface object
            OrphicEgg* egg = new OrphicEgg(&screenScale, userInterface->GetShopButtonSize()->x + userInterface->GetBorderSize().x); // Create a new stone object
			KhaosBG* khaosBG = new KhaosBG({ (screenScale.x - userInterface->GetShopButtonSize()->x - userInterface->GetBorderSize().x) / 2, screenScale.y / 2 }, RED); // Create a new background object

			while (gameState == Gameplay && !WindowShouldClose()) { // While the game state is gameplay and the window is not closed
                // Update
                //----------------------------------------------------------------------------------
                // TODO: Update your variables here
                //---------------------------------------------------------------------------------

				mouseLocation = GetMousePosition(); // Get the mouse location
				deltatime = GetFrameTime(); // Get the deltatime

				egg->Update(&deltatime); // Update the stone object
				player->IsClicked(egg->CheckForEggClick(&mouseLocation)); // Check if the stone object has been clicked
				player->Update(); // Update the player object
				userInterface->ShopButtonChecks(&mouseLocation); // Check the shop buttons
				gameState = userInterface->BackButtonCheck(&mouseLocation); // Check the back button


                // DrawS
                //----------------------------------------------------------------------------------

				BeginDrawing(); // Begin drawing
                
				ClearBackground(BLACK); // Set the background to black

				//DrawBackingGridCheckers(); // Draw the backing grid checkers to help with layout and scaling
				HideCursor(); // Hide the cursor
				khaosBG->Draw(&deltatime); // Draw the background object
				egg->Draw(); // Draw the stone object
				userInterface->Draw(player->GetWealth()); // Draw the user interface
				cursor->Draw(&mouseLocation); // Draw the cursor
				player->DrawClickText(); // Draw the text that appears when clicking the egg


				EndDrawing(); // End drawing
                //----------------------------------------------------------------------------------
            }


			// De-Initialization
            delete player;
            delete egg;
            delete userInterface;
            delete khaosBG;

			break; // Break out of the switch statement
        }
        // De-Initialization
        //--------------------------------------------------------------------------------------
        CloseWindow();        // Close window and OpenGL context
        //--------------------------------------------------------------------------------------

        return 0; 
        }
    }
}


