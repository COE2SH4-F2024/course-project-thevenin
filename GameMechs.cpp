#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 20;
    boardSizeY = 10;

    displayBoard = new char*[boardSizeY];
    for(int i = 0; i < boardSizeY; i++) {
        displayBoard[i] = new char[boardSizeX];
    }

    // Initialize the board
    for(int i = 0; i < boardSizeY; i++) {
        for(int j = 0; j < boardSizeX; j++) {
            if(i == 0 || i == boardSizeY - 1) {
                displayBoard[i][j] = '#';
            } else {
                if(j == 0 || j == boardSizeX - 1) {
                    displayBoard[i][j] = '#';
                } else {
                    displayBoard[i][j] = ' ';
                }
            }
        }
    }
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;

    displayBoard = new char*[boardSizeY];
    for(int i = 0; i < boardSizeY; i++) {
        displayBoard[i] = new char[boardSizeX];
    }

    // Initialize the board
    for(int i = 0; i < boardSizeY; i++) {
        for(int j = 0; j < boardSizeX; j++) {
            if(i == 0 || i == boardSizeY - 1) {
                displayBoard[i][j] = '#';
            } else {
                if(j == 0 || j == boardSizeX - 1) {
                    displayBoard[i][j] = '#';
                } else {
                    displayBoard[i][j] = ' ';
                }
            }
        }
    }
}

GameMechs::~GameMechs() {
    for(int i = 0; i < boardSizeY; i++) {
        delete[] displayBoard[i];
    }
    delete[] displayBoard;
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}

void GameMechs::collectAsyncInput() {
    // Get user's input
    if(MacUILib_hasChar()) {
        input = MacUILib_getChar();
    }
    // Exit input (ESC)
    if(input == 27) {
        exitFlag = true;
    }
}

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    // Score incrementation for normal food
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    // Set to null char
    input = 0;
}

// More methods should be added here
char** GameMechs::getDisplayBoard() const {
    return displayBoard;
}

void GameMechs::incrementScoreSpecial() {
    // Score incrementation for special food
    score += 10;
}