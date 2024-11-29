#include "Player.h"

Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    foodRef = thisFoodRef;
    myDir = STOP;

    playerPosList = new objPosArrayList();
    objPos startPos;

    // Initial position and symbol for player
    startPos.pos->x = mainGameMechsRef->getBoardSizeX() / 2;
    startPos.pos->y = mainGameMechsRef->getBoardSizeY() / 2;
    startPos.symbol = '@';
    playerPosList->insertHead(startPos);

    mainGameMechsRef->getDisplayBoard()[startPos.pos->y][startPos.pos->x] = startPos.symbol;
}


Player::~Player()
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    // Return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();
    switch(input) {                      
        case 'w':
            if(!(myDir == UP || myDir == DOWN)) {
                myDir = UP;
            }
            break;
        case 'a':
            if(!(myDir == RIGHT || myDir == LEFT)) {
                myDir = LEFT;
            }
            break;
        case 's':
            if(!(myDir == UP || myDir == DOWN)) {
                myDir = DOWN;
            }
            break;
        case 'd':
            if(!(myDir == RIGHT || myDir == LEFT)) {
                myDir = RIGHT;
            }
            break;
        default:
            break;
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    updatePlayerDir();
    objPos head = playerPosList->getHeadElement();

    switch(myDir) {
        case UP:
            head.pos->y--;
            break;
        case LEFT:
            head.pos->x--;
            break;
        case DOWN:
            head.pos->y++;
            break;
        case RIGHT:
            head.pos->x++;
            break;
        default:
            break;
    }

    // Wraparound logic
    if(head.pos->x == 0) {
        head.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
    } else if(head.pos->x == mainGameMechsRef->getBoardSizeX() - 1) {
        head.pos->x = 1;
    } else if(head.pos->y == 0) {
        head.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
    } else if(head.pos->y == mainGameMechsRef->getBoardSizeY() - 1) {
        head.pos->y = 1;
    }

    if(checkSelfCollision()) {
        // End the game
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }

    // Create a new head object to insert
    objPos newHead;
    newHead.pos->x = head.pos->x;
    newHead.pos->y = head.pos->y;
    newHead.symbol = '@';

    playerPosList->insertHead(newHead);

    // Remove the tail if food isn't consumed
    if (!checkFoodConsumption()) {
        // Remove the tail
        objPos tail = playerPosList->getTailElement();
        mainGameMechsRef->getDisplayBoard()[tail.pos->y][tail.pos->x] = ' ';
        playerPosList->removeTail();
    }

    mainGameMechsRef->getDisplayBoard()[newHead.pos->y][newHead.pos->x] = newHead.symbol;
}

bool Player::checkFoodConsumption() {

    // Get the symbol of where the head is
    char checkPos = mainGameMechsRef->getDisplayBoard()[playerPosList->getHeadElement().pos->y][playerPosList->getHeadElement().pos->x];

    // Check if the symbol is a food character
    if (checkPos == '$' || checkPos == '*') {
        // Regenerate the food if consumed
        foodRef->generateFood(playerPosList);
        // Special food
        if(checkPos == '$') {
            mainGameMechsRef->incrementScoreSpecial();
            // Return false to NOT increase the body size
            return false;
        // Normal food
        } else {
            mainGameMechsRef->incrementScore();
            // Return true to increase the body size
            return true;
        }
    }
    // If no food is consumed, return false to NOT increase the body size
    return false;
}

bool Player::checkSelfCollision() {
    // Check if snake/player collides with itself
    for(int i = 1; i < playerPosList->getSize(); i++) {
        objPos body = playerPosList->getElement(i);
        if(playerPosList->getHeadElement().pos->x == body.pos->x && playerPosList->getHeadElement().pos->y == body.pos->y) {
            return true;
        }
    }
    return false;
}