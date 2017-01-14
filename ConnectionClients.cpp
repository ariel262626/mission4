//
// Created by dvir on 12/01/17.
//

#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "ConnectionClients.h"

using namespace std;
int choose = 0;

// in this class we have no ant members-> it's static. all members we will need will be global

ConnectionClients::ConnectionClients() {}
    //myChoose = 0;
    //myTexiCenter = texiCenter;
//}

void* ConnectionClients:: runClients (void * socketToDriver){
    // casting to instance of SocketToDriver
    SocketToDriver* socketToDriver1 = (SocketToDriver*) socketToDriver;
    while(tripListNotEmpty(socketToDriver1)) {
    switch(choose) {
        case 7:
            // here we will finish the thread

        case 9:
            stepClients(socketToDriver1);
            choose = 0;
            break;
        default:
            break;
    }
    }
}

void ConnectionClients::stepClients(SocketToDriver* socketToDriver) {
    // for case we have advance without trip
        sendTripToClient(socketToDriver);
        moveClient(socketToDriver);
}


bool ConnectionClients::tripListNotEmpty(SocketToDriver* socketToDriver) {
    if(socketToDriver->getMyTexiCenter()->getMyTripList().empty()) {
        // update the clock
        socketToDriver->getMyTexiCenter()->getMyClockTime().setTime();
        return false;
    }
    return true;
}


void ConnectionClients::sendTripToClient(SocketToDriver* socketToDriver) {
    Trip* trip = socketToDriver->getMyTexiCenter()->getTripInIndex(0);
    // update the trip to driver and send the trip to client only once, when the time is comming.
    // if the time isn't comming-> just update the clock
    if (socketToDriver->getMyTexiCenter()->getMyClockTime().getTime() == trip->getTime()) {
        socketToDriver->getMyDriver()->setTrip(*trip);
        // check if the location of the driver in the same point as start of the trip.
        // if yes-> we in new trip and therefor send it to client
        Point startOfTrip = trip->getStartPointOfTrip();
        Point driverLocation = socketToDriver->getMyDriver()->getLocation();
        if (driverLocation == startOfTrip) {
            // make sure we have trip in te list
            if (!socketToDriver->getMyTexiCenter()->getMyTripList().empty()) {
                //send the next trip by serialization
                std::string serial_str1;
                boost::iostreams::back_insert_device<std::string> inserter1(serial_str1);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter1);
                boost::archive::binary_oarchive oa1(s1);
                oa1 << trip;
                s1.flush();
                //here we sent back the right trip
                socketToDriver->getMyTexiCenter()->getMyTcp()->sendData(serial_str1);
            }
        }
    }
}

void ConnectionClients::moveClient(SocketToDriver* socketToDriver) {
    // get the first trip from the list. if we will finish the trip, we will erase it from the list
    Trip* trip = socketToDriver->getMyTexiCenter()->getTripInIndex(0);
    // update the clock for each movement
    // make advance only in case the time at least such us the time of the trip
    if(trip->getTime() <= socketToDriver->getMyTexiCenter()->getMyClockTime().getTime()) {
        vector<Node> path;
        Point newPosition;
        // get the path of the grid. we use clone for not delete the path
        path = trip->getPathOfTripClone(*socketToDriver->getMyTexiCenter()->getMap());
        // move one or two steps on the grid
        socketToDriver->getMyDriver()->moveStep(path, socketToDriver->getMyTexiCenter()->getMyClockTime().getTime());
        // get the new location of the driver
        newPosition = socketToDriver->getMyTexiCenter()->getDriverInIndex(0)->getLocation();
        //serialize the point and send to client
        std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << newPosition;
        s.flush();
        //here we sent back the 'go' for move one step
        socketToDriver->getMyTexiCenter()->getMyTcp()->sendData(serial_str);

        //after we end trip
        if (socketToDriver->getMyTexiCenter()->getTripInIndex(0)->getEndPointOfTrip() == newPosition) {
            // delete trip
            Trip *temp = socketToDriver->getMyTexiCenter()->getTripInIndex(0);
            socketToDriver->getMyTexiCenter()->eraseTripInIndex();
            delete temp;
        }
    }
    // update the time for each insert 9
    socketToDriver->getMyTexiCenter()->getMyClockTime().setTime();
}