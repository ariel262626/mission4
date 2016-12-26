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

using namespace std;

class TexiCenter {
private:
    vector<Driver *> myDriversList;
    vector<Passenger *> myPassengresList;
    vector<CabBase *> myStandartCabList;
    vector<Trip> myTripList;
    Matrix2d myMap;
    Bfs myBfs;
public:
    // constructors
    TexiCenter(vector<Driver *> driversList, vector<Passenger *> passengresList,
               vector<CabBase *> standartCabList, vector<Trip> tripList, Matrix2d map, Bfs bfs);

    TexiCenter();

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
    void addTripToTripLIst(Trip addTrip);

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
    void setTripList(vector<Trip> tripsList);

    /**
     * set map
     * @param map - the map to set
     */
    void setMap(Matrix2d map);

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
    Trip getTripInIndex(int i);
};

#endif //MISSION2_TEXICENTER_H
