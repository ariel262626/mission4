//
// Created by ariel on 29/11/16.
//

#ifndef MISSION2_PASSENGER_H
#define MISSION2_PASSENGER_H


#include "Point.h"

/**
 * class passenger.
 */
class Passenger {
private:
    Point myStartPoint;
    Point myEndPoint;
public:
    // constractors
    Passenger(Point startPoint, Point endPoint);
    Passenger();

    /**
     * @param rate: how much the passenger is satisfied of the driver
     * @return rate
     */
    int setRateSatistification(int rate);
    /**
     * @return the end point which the passenger need to arrive
     */
    Point getEndPoint();
    /**
     * @return start node of the ride's passenger
     */
    Point getStartPoint();
};


#endif //MISSION2_PASSENGER_H
