#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

class Food {
    private:
        objPosArrayList* foodBucket;
        objPos foodPos;

    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPosArrayList* blockOff);
        objPosArrayList* getFoodPos() const;
        GameMechs* mainGameMechsRef;
};
#endif