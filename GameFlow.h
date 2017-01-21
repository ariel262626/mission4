//
// Created by ariel on 30/11/16.
//

#ifndef MISSION2_GAMEFLOW_H
#define MISSION2_GAMEFLOW_H


#include "Socket.h"
#include "TexiCenter.h"
#include "ClockTime.h"
#include "TripMap.h"

class GameFlow {

private:
    Socket* myTcp;
    TexiCenter* texiCenter;
public:
    /**
     * constructor
     * @param socket
     */
    GameFlow (Socket* socket);

    /**
     * default constructor
     */
    GameFlow();

    /**
     * function which in charge to run the flow of the game. it's handle with
     * any order that come from the console
     */
    void run();

    /**
     * get the driver from client
     * @return driver
     */
    vector <SocketToDriver*> getDriversFromClients();


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
     * print my location
     */
    void printCurrentLocation();

    /**
     * static function. each trip we get from user, we open thread for this, and
     * calculate the trip (with the bfs)
     * @param tripMap
     * @return the path that calculated by bfs
     */
    static void* path(void* tripMap);

    /**
     *
     * @param numOfThreads of drivers
     */
    void waitForMe(int numOfThreads);
};


#endif //MISSION2_GAMEFLOW_H
