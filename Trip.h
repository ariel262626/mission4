//
// Created by ariel on 29/11/16.
//

#ifndef MISSION2_TRIP_H
#define MISSION2_TRIP_H

#include <vector>
#include "Point.h"
#include "Node.h"
#include "Matrix2d.h"

using namespace std;

class Trip {
private:
    int myRideId;
    int myXstart;
    int myYstart;
    int myXend;
    int myYend;
    int myMetersPassed;
    int myPassengerNumber;
    double myTariff;
public:
    //constructors
    Trip(int rideId, int xStart, int yStart, int xEnd, int yEnd, int passengerNumber, double tarrif);
    Trip();

    /**
     * get the path of the trip from the bfs
     * @param map - matrix2d
     * @return - vector of the path
     */
    vector<Node*> getPathOfTrip(Matrix2d map);

    /**
     * get the start point of the trip
     * @return - point
     */
    Point getStartPointOfTrip();

    /**
     * get the end point of the trip
     * @return - point
     */
    Point getEndPointOfTrip();

    /**
     * get the ride id
     * @return id
     */
    int getRideId();

    /**
     * get meter passed of the trip
     * @return meter passed
     */
    int getMetersPassed();

    /**
     * set the kilometres passed
     * @param x - to set
     */
    void setMetersPassed(int x);

    /**
     * get how many passengers in this trip
     * @return number of passengers
     */
    int getPassengersNumber();

    /**
     * set how many passengers
     * @param x - number of passengers
     */
    void setPassengersNumber(int x);

};

#endif //MISSION2_TRIP_H
