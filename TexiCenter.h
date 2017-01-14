//
// Created by ariel on 29/11/16.
//

#ifndef MISSION2_TEXICENTER_H
#define MISSION2_TEXICENTER_H

#include <iostream>
#include <vector>
#include "Driver.h"
#include "Passenger.h"
#include "Trip.h"
#include "Bfs.h"
#include "Matrix2d.h"
#include "Socket.h"
#include "ClockTime.h"
#include "SocketToDriver.h"

using namespace std;
/**
 * in this class we have the all data we insert as input. we hold the all listd of
 * the objects and use them
 */
class TexiCenter {
private:
    vector<Driver *> myDriversList;
    vector<Passenger *> myPassengresList;
    vector<CabBase *> myStandartCabList;
    vector<Trip*> myTripList;
    Matrix2d* myMap;
    Bfs myBfs;
    Socket* myTcp;
    ClockTime myClockTime;
    vector<SocketToDriver*> mySocketToDriverList;

public:
    // constructors
    TexiCenter(vector<Driver *> driversList, vector<Passenger *> passengresList,
               vector<CabBase *> standartCabList, vector<Trip*> tripList, Matrix2d* map, Bfs bfs, Socket* tcp);

    TexiCenter();
    ~TexiCenter();

    ClockTime getMyClockTime();

    /**
     * get all drivers to the end point
     */
    void startDriving();

    /**
     * find the closest driver to the passenger that want texi
     * @param passenger - passenger that want texi
     * @return the closest driver.
     */
    Driver findDriver(Passenger passenger);

    /**
     * find the location of the driver according to his id
     * @param idDriverToFind  - the driver id
     * @return the location point
     */
    Point findLocationOfDriver(int idDriverToFind);

    /**
     * add driver to driver list
     * @param addDriver - the driver to add
     */
    void addDriverToDriverLIst(Driver* addDriver);

    /**
     * add cab to cab list
     * @param addCab - the cab to add
     */
    void addCabToCabsLIst(CabBase* addCab);

    /**
     * add trip to trip list
     * @param addTrip - the trip to add
     */
    void addTripToTripLIst(Trip* addTrip);

    /**
     * set the driver list to this list
     * @param driversList - the vector of drivers
     */
    void setDriverList(vector<Driver *> driversList);

    /**
     * set passenger list to the recived list
     * @param passengresList - the recived list
     */
    void setPassengerList(vector<Passenger *> passengresList);

    /**
     * set cab list to the recived list
     * @param baseCabList - the recived list
     */
    void setBaseCabeList(vector<CabBase *> baseCabList);

    /**
     * set trip list to the recived list
     * @param tripsList - the recived list
     */
    void setTripList(vector<Trip*> tripsList);

    /**
     * set map
     * @param map - the map to set
     */
    void setMap(Matrix2d* map);

    /**
     * get driver from the list with according to the index
     * @param i - the index we look for
     * @return pointer to the driver
     */
    Driver* getDriverInIndex(int i);

    /**
     * get cab according index in the list
     * @param i - index
     * @return  the cab
     */
    CabBase* getCabInIndex(int i);

    /**
     * get trip according to index
     * @param i - index
     * @return  trip
     */
    Trip* getTripInIndex(int i);

    /**
    * get cab with this id
    * @param i - index
    * @return  cabebase
    */
    CabBase* getCabWithId(int i);

    /**
    * get driver with this id
    * @param i - index
    * @return  trip
    */
    Driver* getDriverWithId(int id);

    /**
    * erase trip in index
    * @param i - index
    */
    void eraseTripInIndex();

    /**
    * get my list of drivers
    * @return  list
    */
    vector<Driver*>  getMyDriverList();
    /**
     * get my trip list
     * @return  list trip
     */
    vector<Trip*> getMyTripList ();

    /**
    * get my cab list
    * @return  list cab
    */
    vector<CabBase*> getMyCabBaseList ();

    Matrix2d* getMap();

    void sendCab(CabBase* cabBase);

    /**
     * set cab into driver
     * @param driver - the driver
     */
    void setCabToDriver(Driver* driver);

    Socket* getMyTcp();

    void setMySocketToDriverList(SocketToDriver* socketToDriver);

    vector<SocketToDriver*> getMySocketToDriverList();

   // Driver* getmyDriverAccordingSocketNum(int descriptorClient);
    };

#endif //MISSION2_TEXICENTER_H
