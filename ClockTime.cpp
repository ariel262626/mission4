//
// Created by ariel on 29/12/16.
//
#include "ClockTime.h"

ClockTime:: ClockTime(){
    myCurrentTime = 0;
}
void ClockTime::setTime() {
    myCurrentTime++;
}

int ClockTime::getTime() {
    return myCurrentTime;
}


