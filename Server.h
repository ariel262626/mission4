//
// Created by ariel on 03/01/17.
//

#include "Driver.h"
#include "Socket.h"
#include "TexiCenter.h"

#ifndef MISSION4_SERVER_H
#define MISSION4_SERVER_H

#endif //MISSION4_SERVER_H

class Server {
private:
    int numberOfDrivers;
    Socket* udp;
    ClockTime clockTime;
    Driver* myDriver;
    CabBase* myCabBase;

public:
    //constractor
    Server() { };
    //TODO retutn private
    TexiCenter texiCenter;
    /**
     * get the driver from client
     * @return driver
     */
    Driver* getDriverFromClient();

    /**
     * set cab into driver
     * @param driver - the driver
     */
    void setCabToDriver(Driver* driver);

    /**
     * send cab to client
     * @param cabBase - the cab
     */
    void sendCab(CabBase* cabBase);

    /**
     * get trip
     */
    void getNewRide();

    /**
     * get cab
     */
    void getNewCab();

    /**
     * print cuurent location
     */
    void printCurrentLocation();

    /**
     * free allcation memory
     */
    void deleteAllocationMemory();

    /**
     * sent close to client
     */
    void tripToCloseClient();

    /**
     * get udp
     * @return - the socket
     */
    Socket* getUdp();

    /**
     * set udp
     * @param udp1 - to set
     */
    void setUdp(Socket* udp1);

    /**
     * get the clock
     * @return clock
     */
    ClockTime getClock();

    /**
     * check if trip list empty
     * @return true if not empty
     */
    bool tripListNotEmpty();

    /**
     * sent trip to client
     */
    void sendTripToClient();

    /**
     * get mydriver
     * @return mydriver
     */
    Driver* getMyDriver();

    /**
     * set mydriver
     */
    void setMyDriver();

    /**
     * set mycab
     */
    void setMyCabBase();

    /**
     * move driverClient onestep
     */
    void moveClient();

    /**
     * get current trip
     * @return our trip
     */
    Trip* getCurrentTrip();

    /**
     * delete udp
     */
    void deleteUdp();

    /**
     * get my cabBase
     * @return mycabBase
     */
    CabBase* getMyCabBase();
    };