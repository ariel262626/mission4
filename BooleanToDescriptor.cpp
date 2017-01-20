//
// Created by ariel on 17/01/17.
//

#include "BooleanToDescriptor.h"


BooleanToDescriptor:: BooleanToDescriptor (int descriptor){
    myDescriptor = descriptor;
    isMoved = false;
}
void BooleanToDescriptor:: setMyDescriptor(int descriptor){
    myDescriptor = descriptor;
}
int BooleanToDescriptor:: getMyDescriptor(){
    return myDescriptor;
}
void BooleanToDescriptor::setIsMovedToFalse (){
    isMoved = false;
}

void BooleanToDescriptor::setIsMovedToTrue (){
    isMoved = true;
}

bool BooleanToDescriptor::getIsMoved (){
    return isMoved;
}