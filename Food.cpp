#include <stdlib.h>

#include "Food.h"
#include "objPos.h"

Food::Food(GameMechs* thisGMRef) {
    mainGameMechsRef = thisGMRef;
    foodBucket = new objPosArrayList;
    foodPos.pos->x = 0;
    foodPos.pos->y = 0;
    foodPos.symbol = 0;
}

Food::~Food() {
    delete foodBucket;
}

void Food::generateFood(objPosArrayList* blockOff) {
    // Remove the old food items from the board before generating new ones
    for (int i = 0; i < foodBucket->getSize(); ++i) {
        objPos oldFood = foodBucket->getElement(i);
        mainGameMechsRef->getDisplayBoard()[oldFood.pos->y][oldFood.pos->x] = ' ';
    }
    // Clear the foodBucket list
    foodBucket->clear();

    // Get the available empty spaces on board
    int totalValidSpace = (mainGameMechsRef->getBoardSizeX() - 2) * (mainGameMechsRef->getBoardSizeY() - 2);
    int playerSpace = blockOff->getSize();
    int availableSpace = totalValidSpace - playerSpace;

    // If there are more than 5 available spaces, cap at 5
    if(!(availableSpace < 5)) {
        availableSpace = 5;
    }

    int count = 0;

    // Runs maximum of 5 times
    while(count < availableSpace) {
        // Spawn 1 special food
        if(count < 1) {
            foodPos.symbol = '$';
        } 
        // 4 items are normal food
        else {
            foodPos.symbol = '*';
        }

        // Random food spawn coordinate
        int foodRandomX = rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1;
        int foodRandomY = rand() % (mainGameMechsRef->getBoardSizeY() - 2) + 1;

        bool isValid = true;

        // Check if the position is not part of the player
        for (int i = 0; i < blockOff->getSize(); ++i) {
            objPos bodyPart = blockOff->getElement(i);
            if (foodRandomX == bodyPart.pos->x && foodRandomY == bodyPart.pos->y) {
                isValid = false;
                break;
            }
        }

        // If the position is not body and the board space is empty, generate food
        if(isValid && mainGameMechsRef->getDisplayBoard()[foodRandomY][foodRandomX] == ' ') {
            foodPos.pos->x = foodRandomX;
            foodPos.pos->y = foodRandomY;
            foodBucket->insertTail(foodPos);
            mainGameMechsRef->getDisplayBoard()[foodRandomY][foodRandomX] = foodPos.symbol;
            count++;
        }
    }
}

objPosArrayList* Food::getFoodPos() const {
    return foodBucket;
}