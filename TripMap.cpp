//
// Created by dvir on 15/01/17.
//

#include "TripMap.h"
#include "Trip.h"

TripMap:: TripMap(Trip* trip, Matrix2d* map) {
  myTrip = trip;
    myMap = map;
}

Trip* TripMap::getTrip() {
    return myTrip;
}

Matrix2d* TripMap::getMap() {
    return myMap;
}