//
// Created by dvir on 11/01/17.
//

#ifndef MISSION4_SOCKETTODRIVER_H
#define MISSION4_SOCKETTODRIVER_H


#include "Socket.h"
#include "Driver.h"
#include "TexiCenter.h"

class SocketToDriver {
private:
    int myDescriptorClient;
    Driver* myDriver;
    TexiCenter* myTexiCenter;

public:
    SocketToDriver (int myDescriptorClient, Driver* driver, TexiCenter* texiCenter);
    int getMySocket();
    Driver *getMyDriver();
    void setMyDescriptor (int descriptorClient);
    void setMyDriver(Driver *myDriver);
    TexiCenter* getMyTexiCenter();
    void setMyTexiCenter(TexiCenter* texiCenter);

};


#endif //MISSION4_SOCKETTODRIVER_H
