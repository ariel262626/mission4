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

ConnectionClients::ConnectionClients(TexiCenter &texiCenter) {
    myChoose = 0;
    myTexiCenter = texiCenter;
}

void ConnectionClients:: runClients (){
    while(true) {
    switch(myChoose) {
        case 4:
            printCurrentLocation();
            break;
        case 9:
            stepClients();
            break;
        default:
            break;
    }
    }
}

void ConnectionClients::stepClients() {
    // for case we have advance without trip
    if(tripListNotEmpty()) {
        sendTripToClient();
        moveClient();
    } else {
        break;
    }
}

void ConnectionClients:: setChoose(int choose){
    myChoose = choose;
}

void ConnectionClients::printCurrentLocation() {
    //insert id of driver
    int DriverId;
    Point location;
    cin >> DriverId;
    // find location of the driver in the grid and print it
    location = myTexiCenter.findLocationOfDriver(DriverId);
    cout << location << endl;
}

bool ConnectionClients::tripListNotEmpty() {
    if(myTexiCenter.getMyTripList().empty()) {
        // update the clock
        myTexiCenter.getMyClockTime().setTime();
        return false;
    }
    return true;
}


void ConnectionClients::sendTripToClient() {
    Trip* trip = myTexiCenter.getTripInIndex(0);
    // update the trip to driver and send the trip to client only once, when the time is comming.
    // if the time isn't comming-> just update the clock
    if (myTexiCenter.getMyClockTime().getTime() == trip->getTime()) {
        myTexiCenter.getmyDriver->setTrip(*trip);
        // check if the location of the driver in the same point as start of the trip.
        // if yes-> we in new trip and therefor send it to client
        Point startOfTrip = trip->getStartPointOfTrip();
        Point driverLocation = myDriver->getLocation();
        if (driverLocation == startOfTrip) {
            // make sure we have trip in te list
            if (!myTexiCenter.getMyTripList().empty()) {
                //send the next trip by serialization
                std::string serial_str1;
                boost::iostreams::back_insert_device<std::string> inserter1(serial_str1);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter1);
                boost::archive::binary_oarchive oa1(s1);
                oa1 << trip;
                s1.flush();
                //here we sent back the right trip
                myTexiCenter.getMyTcp()->sendData(serial_str1);
            }
        }
    }
}

void ConnectionClients::moveClient() {
    // get the first trip from the list. if we will finish the trip, we will erase it from the list
    Trip* trip = myTexiCenter.getTripInIndex(0);
    // update the clock for each movement
    // make advance only in case the time at least such us the time of the trip
    if(trip->getTime() <= myTexiCenter.getMyClockTime().getTime()) {
        vector<Node> path;
        Point newPosition;
        // get the path of the grid. we use clone for not delete the path
        path = trip->getPathOfTripClone(*myTexiCenter.getMap());
        // move one or two steps on the grid
        myDriver->moveStep(path, myTexiCenter.getMyClockTime().getTime());
        // get the new location of the driver
        newPosition = myTexiCenter.getDriverInIndex(0)->getLocation();
        //serialize the point and send to client
        std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << newPosition;
        s.flush();
        //here we sent back the 'go' for move one step
        myTexiCenter.getMyTcp()->sendData(serial_str);

        //after we end trip
        if (myTexiCenter.getTripInIndex(0)->getEndPointOfTrip() == newPosition) {
            // delete trip
            Trip *temp = myTexiCenter.getTripInIndex(0);
            myTexiCenter.eraseTripInIndex();
            delete temp;
        }
    }
    // update the time for each insert 9
    myTexiCenter.getMyClockTime().setTime();
}