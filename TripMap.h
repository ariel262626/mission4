//
// Created by dvir on 15/01/17.
//

#ifndef MISSION4_TRIPMAP_H
#define MISSION4_TRIPMAP_H


#include "Trip.h"

/**
 * this class have trip and map together
 */
class TripMap {

private:
    Trip* myTrip;
    Matrix2d* myMap;

public:
    /**
     * constructor
     * @param trip
     * @param map
     */
    TripMap(Trip* trip, Matrix2d* map);
    ~TripMap(){ }

    /**
     * get my trip
     * @return trip
     */
    Trip* getTrip();

    /**
     * get my map
     * @return my map
     */
    Matrix2d* getMap();
};


#endif //MISSION4_TRIPMAP_H
