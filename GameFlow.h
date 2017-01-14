//
// Created by ariel on 30/11/16.
//

#ifndef MISSION2_GAMEFLOW_H
#define MISSION2_GAMEFLOW_H


#include "Socket.h"
#include "TexiCenter.h"
#include "ClockTime.h"

class GameFlow {

private:
    Socket* myTcp;
    TexiCenter texiCenter;
    Driver* myDriver;
    CabBase* myCabBase;
public:
    GameFlow (Socket* socket);
    GameFlow();
    void run();

    /**
     * get the driver from client
     * @return driver
     */
    Driver* getDriverFromClient();


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
     * sent close to client
     */
    void tripToCloseClient();


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
   // void setMyCabBase();


    /**
     * get current trip
     * @return our trip
     */
    Trip* getCurrentTrip();

    /**
     * get my cabBase
     * @return mycabBase
     */
    CabBase* getMyCabBase();

    void printCurrentLocation();
};


#endif //MISSION2_GAMEFLOW_H
