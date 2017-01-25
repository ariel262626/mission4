//
// Created by ariel on 30/11/16.
//

#ifndef MISSION2_GAMEFLOW_H
#define MISSION2_GAMEFLOW_H


#include "Socket.h"
#include "TexiCenter.h"
#include "ClockTime.h"
#include "TripMap.h"
#include "ThreadPoolTrips.h"

class GameFlow {

private:
    Socket* myTcp;
    TexiCenter* texiCenter;
    ThreadPoolTrips* myThreadPoolTrips;
public:
    GameFlow (Socket* socket);
    GameFlow();
    void run();

    /**
     * get the driver from client
     * @return driver
     */
    vector <SocketToDriver*> getDriversFromClients(int numberOfDrivers);


    /**
     * send cab to client
     * @param cabBase - the cab
     */
    void sendCab(CabBase* cabBase, int socketDescriptor);

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

    /**
     * print current location
     */
    void printCurrentLocation();

    /**
     * get path
     * @param tripMap
     * @return void*
     */
    static void* path(void* tripMap);

    /**
     * wait for me to end
     * @param numOfThreads-t
     */
    void waitForMe(int numOfThreads);

    /**
     * wait before exit
     */
    void waitForExit();

    /**
     * wait for all to exit
     */
    void waitForAllToEXit();

    /**
     * check if my input is one number
     * @param myInput
     * @return bool
     */
    bool checkIsOneNumber(string myInput);

    };

#endif //MISSION2_GAMEFLOW_H
