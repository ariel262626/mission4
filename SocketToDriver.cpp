//
// Created by dvir on 11/01/17.
//

#include "SocketToDriver.h"

SocketToDriver:: SocketToDriver (int descriptorClient, Driver* driver){
    myDescriptorClient = descriptorClient;
    myDriver = driver;
}

int SocketToDriver::getMySocket() {
    return myDescriptorClient;
}

Driver *SocketToDriver::getMyDriver() {
    return myDriver;
}

void SocketToDriver::setMyDescriptor (int descriptorClient) {
    myDescriptorClient = descriptorClient;
}

void SocketToDriver::setMyDriver(Driver* driver) {
    myDriver = driver;
}

