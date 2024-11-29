#include <iostream>
#include <time.h>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *myGM;
Player *myPlayer;
Food *myFood;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    srand(time(NULL));

    myGM = new GameMechs();
    myFood = new Food(myGM);
    myPlayer = new Player(myGM, myFood);

    // Initial food generation on board
    myFood->generateFood(myPlayer->getPlayerPos());
}

void GetInput(void)
{
    // Collect user's input
    myGM->collectAsyncInput();
}

void RunLogic(void)
{
    // Moves the player
    myPlayer->movePlayer();
}

void DrawScreen(void)
{
    // Clear the old board before updating/drawing the board
    MacUILib_clearScreen();

    // Drawing the game
    for(int i = 0; i < myGM->getBoardSizeY(); i++) {
         for(int j = 0; j < myGM->getBoardSizeX(); j++) {
             MacUILib_printf("%c", myGM->getDisplayBoard()[i][j]);
         }
         MacUILib_printf("\n");
    }
    // User's score
    MacUILib_printf("Your Score: %d\n", myGM->getScore());
}

void LoopDelay(void)
{
    // 0.1s delay
    MacUILib_Delay(DELAY_CONST);
}


void CleanUp(void)
{
    // Clear the screen on exit/end
    MacUILib_clearScreen();

    // If the player died, show custom death message before shutdown
    if(myGM->getLoseFlagStatus()) {
        MacUILib_printf("GAME OVER.");
    }
    
    delete myPlayer;
    delete myGM;
    delete myFood;
    
    MacUILib_uninit();
}
