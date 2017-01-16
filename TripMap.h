//
// Created by dvir on 15/01/17.
//

#ifndef MISSION4_TRIPMAP_H
#define MISSION4_TRIPMAP_H


#include "Trip.h"

class TripMap {
private:
    Trip* myTrip;
    Matrix2d* myMap;
public:
    TripMap(Trip* trip, Matrix2d* map);
    Trip* getTrip();
    Matrix2d* getMap();
};


#endif //MISSION4_TRIPMAP_H
