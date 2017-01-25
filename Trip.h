//
// Created by ariel on 29/11/16.
//

#ifndef MISSION2_TRIP_H
#define MISSION2_TRIP_H

#include <vector>
//#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
//#include "Point.h"
#include "Node.h"
#include "Matrix2d.h"



using namespace std;
using namespace boost::archive;
/**
 * in this class we create trip object that the driver get each time
 */
class Trip {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & myRideId;
        ar & myXstart;
        ar & myYstart;
        ar & myXend;
        ar & myYend;
        ar & myMetersPassed;
        ar & myPassengerNumber;
        ar & myTariff;
        ar & myTime;
       // ar & myPath;
    }
private:
    int myRideId;
    int myXstart;
    int myYstart;
    int myXend;
    int myYend;
    int myMetersPassed;
    int myPassengerNumber;
    double myTariff;
    int myTime;
    vector<Node> myPath;
    bool isTripTaken;
    bool isPathReady;
    pthread_mutex_t bfsFirst;


public:
    //constructors
    Trip(int rideId, int xStart, int yStart, int xEnd, int yEnd, int passengerNumber, double tarrif, int time);
    Trip();
    ~Trip(){ };

    /**
     * get the path of the trip from the bfs
     * @param map - matrix2d
     * @return - vector of the path
     */
    vector<Node*> getPathOfTrip(Matrix2d map);
    vector<Node> getPathOfTripClone(Matrix2d map);

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

    /**
     * set time of the trip
     */
    void setTime();

    /**
    * set rideId of the trip
    */
    void setRideId(int id);

    /**
     * get time of the trip
     * @return
     */
    int getTime();

    /**
    * set bool is taken trip true
    */
    void setIsTakenTrue ();

    /**
    * set bool is taken trip false
    */
    void setIsTakenFalse ();

    /**
     * get if this trip taken
     * @return bool
     */
    bool getIsTaken();

    /**
     * get my path of the trip (the vector of the path)
     * @return vector with nodes from stsrt to end point
     */
    vector<Node> getMyPath();

    /**
     * my join - wait till path is calculated
     */
    void joinTrip();
    };

#endif //MISSION2_TRIP_H
