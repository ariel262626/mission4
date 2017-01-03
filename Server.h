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
public:
    Server() { };
    //TODO retutn private
    TexiCenter texiCenter;
    Driver* getDriverFromClient();
    void setCabToDriver(Driver* driver);
    void sendCab(CabBase* cabBase);
    void getNewRide();
    void getNewCab();
    void printCurrentLocation();
    void deleteAllocationMemory();
    void tripToCloseClient();
    Socket* getUdp();
    void setUdp(Socket* udp1);
    ClockTime getClock();
    bool tripListNotEmpty();
    void sendTripToClient();
    Driver* getMyDriver();
    void setMyDriver();
    void moveClient();
    Trip* getCurrentTrip();

    };