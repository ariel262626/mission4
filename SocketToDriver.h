//
// Created by dvir on 11/01/17.
//

#ifndef MISSION4_SOCKETTODRIVER_H
#define MISSION4_SOCKETTODRIVER_H


#include "Socket.h"
#include "Driver.h"

class SocketToDriver {
private:
    int myDescriptorClient;
    Driver* myDriver;

public:
    SocketToDriver (int myDescriptorClient, Driver* driver);
    int getMySocket();
    Driver *getMyDriver();
    void setMyDescriptor (int descriptorClient);
    void setMyDriver(Driver *myDriver);
};


#endif //MISSION4_SOCKETTODRIVER_H
