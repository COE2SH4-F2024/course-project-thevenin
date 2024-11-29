#include "objPosArrayList.h"
#include <stdexcept>
using namespace std;

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize >= ARRAY_MAX_CAP) {
        throw std::out_of_range("Out of range.");
    }
    for(int i = listSize; i > 0; i--) {
        aList[i] = aList[i-1];
    }
    aList[0] = thisPos;
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize >= ARRAY_MAX_CAP) {
        throw std::out_of_range("Out of range.");
    }
    aList[listSize] = thisPos;
    listSize++;
}

void objPosArrayList::removeHead()
{
    if(listSize == 0) {
        throw std::out_of_range("Out of range.");
    }
    for(int i = 0; i < listSize - 1; i++) {
        aList[i] = aList[i+1];
    }
    listSize--;
}

void objPosArrayList::removeTail()
{
    if(listSize > 0) {
        listSize--;
    }
}

objPos objPosArrayList::getHeadElement() const
{
    if (listSize == 0) {
        throw std::out_of_range("List is empty.");
    }
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    if (listSize == 0) {
        throw std::out_of_range("List is empty.");
    }
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    if(index < 0) {
        index = 0;
    } else if(index >= ARRAY_MAX_CAP) {
        index = ARRAY_MAX_CAP - 1;
    }

    return aList[index];
}