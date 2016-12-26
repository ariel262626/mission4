//
// Created by ariel on 29/11/16.
//

#include "Passenger.h"

Passenger::Passenger(Point startPoint, Point endPoint) : myStartPoint(startPoint), myEndPoint(endPoint) {
    myStartPoint = startPoint;
    myEndPoint = endPoint;
}

int Passenger::setRateSatistification(int rate) {
    return rate;
}

Passenger::Passenger() {}

Point Passenger::getEndPoint() {
    return myEndPoint;
}

Point Passenger::getStartPoint() {
    return myStartPoint;
}
