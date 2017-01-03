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

public:
    Server() { };
    //TODO retutn private
    Socket* udp;
    TexiCenter texiCenter;
    Driver* getDriver();
    void setCabToDriver(Driver* driver);
    void sendCab(CabBase* cabBase);

    };