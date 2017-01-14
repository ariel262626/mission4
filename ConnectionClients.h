//
// Created by dvir on 12/01/17.
//

#ifndef MISSION4_CONNECTIONCLIENTS_H
#define MISSION4_CONNECTIONCLIENTS_H


#include "TexiCenter.h"

class ConnectionClients {
private:
    //int myChoose;
    //TexiCenter myTexiCenter;

public:
    ConnectionClients();
    static void* runClients (void* socketToDriver);

    /**
     * check if trip list empty
     * @return true if not empty
     */
    static bool tripListNotEmpty(SocketToDriver* socketToDriver);

    static void sendTripToClient(SocketToDriver* socketToDriver);

    static void stepClients(SocketToDriver* socketToDriver);

    static void moveClient(SocketToDriver* socketToDriver);

    };


#endif //MISSION4_CONNECTIONCLIENTS_H
