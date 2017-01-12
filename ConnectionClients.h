//
// Created by dvir on 12/01/17.
//

#ifndef MISSION4_CONNECTIONCLIENTS_H
#define MISSION4_CONNECTIONCLIENTS_H


#include "TexiCenter.h"

class ConnectionClients {
private:
    int myChoose;
    TexiCenter myTexiCenter;

public:
    ConnectionClients(TexiCenter &texiCenter);
    void  runClients ();
    void setChoose (int choose);
    /**
     * print cuurent location
     */
    void printCurrentLocation();

    /**
     * check if trip list empty
     * @return true if not empty
     */
    bool tripListNotEmpty();

    void sendTripToClient();

    void stepClients();

    void moveClient();

    };


#endif //MISSION4_CONNECTIONCLIENTS_H
