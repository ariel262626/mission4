//
// Created by ariel on 29/11/16.
//
#include <iostream>
#include "StandartCab.h"
#include "Trip.h"

#ifndef MISSION2_DRIVER_H
#define MISSION2_DRIVER_H
using namespace std;

class Driver {
private:
    int myId;
    int myAge;
    string myMartialStatus;
    int myExperience;
    int myVehicleId;
    int mySatisfication;
    CabBase myTaxiStandart;
    Point myLocation;
    Trip myTrip;
    int countTrip;
public:
    //constructor
    Driver(int id, int age, char mariralStatus, int experience, int vechileId,
           CabBase taxiStandart, Trip trip);
    Driver();
/**
 * this metod get path and move the cab one step (standart cab), or two step (luxury cab) on the grid
 * @param path: the path trajectory of bfs
 */
    void moveStep(vector<Node*> path);
    /**
     * this method get the point of location which the drive is on the grid. and find the index of this point
     * on the trajectory of bfs.
     * @param path: the path trajectory of bfs
     * @param point: point
     * @return index of point in the trajectory
     */
    int getIndexCurrentLocationPoint(vector<Node*> path, Point point);
    /**
     * set location of the driver in the grid
     * @param p: point
     */
    void setLocation(Point p);
    /**
     * get my location in the grid
     * @return point
     */
    Point getLocation();
    /**
     * get satisfication of the driver
     * @return satisfiction
     */
    int getStatisfication();
    /**
     * determine the satisfication from the driver
     * @param rate
     */
    void setStatisfication(int rate);
    /**
     * set the trip to driver
     * @param trip
     */
    void setTrip(Trip trip);
    /**
     * the id of the driver
     * @return id of the driver
     */
    int getId();
    /**
     * set how many trip
     */
    void setCountTrips();
    /**
     * get how many trip he did
     * @return trip
     */
    int getCountTrips();
};


#endif //MISSION2_DRIVER_H
