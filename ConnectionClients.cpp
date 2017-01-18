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
#include <boost/serialization/vector.hpp>
#include <iostream>
#include <unistd.h>
#include <string>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "ConnectionClients.h"
#include "BooleanToDescriptor.h"

using namespace std;
int choose = 0;
ClockTime clockTime;
pthread_t treadOfTrip;
vector <BooleanToDescriptor> myBoolList;
pthread_mutex_t first;
bool iFirst = true;
bool firstNine = true;
// in this class we have no ant members-> it's static. all members we will need will be global

ConnectionClients::ConnectionClients() {}

string bufferrrToString(char* buffer, int bufflen)
{
    std::string ret(buffer, bufflen);
    return ret;
}

void* ConnectionClients:: runClients (void* socketToDriver) {
    // casting to instance of SocketToDriver
    SocketToDriver *socketToDriver1 = (SocketToDriver *) socketToDriver;
    while (true) {
        for (int i = 0; i < myBoolList.size(); ++i) {
            if (myBoolList[i].getMyDescriptor() == socketToDriver1->getMyDescriptor()) {
                if (myBoolList[i].getIsMoved() == false) {

                    switch (choose) {
                        case 7:
                            // the allocate memory which placed in taxi center will be deleted when the program finish.
                            // now, call function that send special trip to shut down the program
                            tripToCloseClient(socketToDriver1);
                            return 0;
                        case 9:

                            ///////////////////////////////////////////
                            cout<<"case 9:"<<endl;
                            cout<<"clocke time is:";
                            cout<<clockTime.getTime()<<endl;
                            ////////////////////////////////////////////

                            for (int j = 0; j < myBoolList.size(); ++j) {
                                if (myBoolList[j].getMyDescriptor() == socketToDriver1->getMyDescriptor()) {
                                    myBoolList[j].setIsMovedToTrue();
                                }
                            }
                            cout << "tread number descriptor" << endl;
                            cout << socketToDriver1->getMyDescriptor() << endl;
                            stepClients(socketToDriver1);
                            firstNine = false;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

void ConnectionClients::tripToCloseClient(SocketToDriver* socketToDriver) {
    //create special trip and send ir the client in order to know when shut down the process
    Trip* tripClose = new Trip(-1, 0, 0, 0, 0, 0, 0, 0);
    //send the close trip
    std::string serial_str1;
    boost::iostreams::back_insert_device<std::string> inserter1(serial_str1);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter1);
    boost::archive::binary_oarchive oa1(s1);
    oa1 << tripClose;
    s1.flush();
    //here we sent back the right trip
    socketToDriver->getMyTexiCenter()->getMyTcp()->sendData(serial_str1,
                                                            socketToDriver->getMyDescriptor());    // delete tripClose
    delete tripClose;
}

SocketToDriver* ConnectionClients::findCurrectDriverToTrip(TexiCenter* texiCenter, Trip* trip) {
    vector<Driver*> driverList = texiCenter->getMyDriverList();
    SocketToDriver* socketToDriver;
    vector<Driver*> allDriversAtStartPointTrip;
    Point startPiontOfTrip = trip->getStartPointOfTrip();
    Driver* freeDriver;
    /*find if there is driver at the point of the starting point of the trip
   * if there is this driver will take the trip*/
        for(int j = 0; j < driverList.size(); j++) {
            Point driverLocation = driverList.at(j)->getLocation();
            if (driverLocation == startPiontOfTrip) {
                allDriversAtStartPointTrip = getAllDriversAtThisPoint(driverList, startPiontOfTrip);
                freeDriver = allDriversAtStartPointTrip.at(0);
                for (int k = 0; k < allDriversAtStartPointTrip.size(); k++) {
                    if (allDriversAtStartPointTrip.at(k)->getCountTrips() < freeDriver->getCountTrips()) {
                        freeDriver = allDriversAtStartPointTrip.at(k);
                    }
                }
            }
        }
    socketToDriver = findSocketToDriver(freeDriver, texiCenter);
    return socketToDriver;
}

SocketToDriver* ConnectionClients:: findSocketToDriver(Driver* driver, TexiCenter* texiCenter){
    vector<SocketToDriver*> mySocketToDriverList = texiCenter->getMySocketToDriverList();
    for (int i = 0; i< texiCenter->getMyDriverList().size(); i++){
        if (mySocketToDriverList[i]->getMyDriver()->getId() == driver->getId()){
            return mySocketToDriverList[i];
        }
    }
}

/**
 * get all the drivers at the point of the start point of trip
 * @param myDriversList - the list of drivers
 * @param startPiontOfTrip - start point of trip
 * @return vector of the driver at the point
 */
vector<Driver*> ConnectionClients::getAllDriversAtThisPoint(vector<Driver*> myDriversList,Point startPiontOfTrip) {
    vector<Driver*> driversAtPoint;
    for (int i = 0; i < myDriversList.size(); i++) {
        if(myDriversList.at(i)->getLocation() == startPiontOfTrip) {
            Driver* driver = myDriversList.at(i);
            driversAtPoint.push_back(driver);
        }
    }
    return driversAtPoint;
}

void ConnectionClients::stepClients(SocketToDriver* socketToDriver) {
    // for case we have advance without trip
        cout<<"in step client"<<endl;
        sendTripToClient(socketToDriver);
        cout<<"after sendTripToClient"<<endl;
        if(!firstNine) {
            moveClient(socketToDriver);
            cout << "put next case" << endl;
        }
}

/*
bool ConnectionClients::tripListNotEmpty(SocketToDriver* socketToDriver) {
    if(socketToDriver->getMyTexiCenter()->getMyTripList().empty()) {
        // update the clock
       // socketToDriver->getMyTexiCenter()->getMyClockTime().setTime();
        return false;
    }
    return true;
}*/

void ConnectionClients::sendTripToClient(SocketToDriver* socketToDriver) {
    cout << "in sendTripToClient" << endl;
    Trip* trip;
    pthread_mutex_lock(&first);
    if (socketToDriver->getMyDriver()->getMyTrip() == NULL) {
        trip = socketToDriver->getMyTexiCenter()->getFreeTrip();
    } else {
        trip = socketToDriver->getMyDriver()->getMyTrip();
    }
    //pthread_mutex_unlock(&first);
        if (clockTime.getTime() != trip->getTime()) {
            trip->setIsTakenFalse();
        }
        //after we get trip we finding who is the right sockettodriver for him
    //  SocketToDriver *socketToUpdate =
    //         findCurrectDriverToTrip(socketToDriver->getMyTexiCenter(), trip);
    // update the trip to driver and send the trip to client only once, when the time is comming.
    // if the time isn't comming-> just update the clock
    //flag if i the first driver and get the first trip at the first time
        if ((clockTime.getTime() == trip->getTime()) ||
    ((socketToDriver->getMyTexiCenter()->getMyTripList().at(0)->getTime() == clockTime.getTime()) && (iFirst))) {
            if((iFirst) &&
                    (socketToDriver->getMyTexiCenter()->getMySocketToDriverList().at(0)->getMyDriver()->getId()
                     == socketToDriver->getMyDriver()->getId())) {
                Trip* firstTrip = socketToDriver->getMyTexiCenter()->getMyTripList().at(0);
                socketToDriver->getMyDriver()->setTrip(firstTrip);
                iFirst = false;

            } else {
                if(clockTime.getTime() == trip->getTime()) {
                    socketToDriver->getMyDriver()->setTrip(trip);
                }
            }
            // check if the location of the driver in the same point as start of the trip.
            // if yes-> we in new trip and therefor send it to client
            Point startOfTrip = trip->getStartPointOfTrip();
            Point driverLocation = socketToDriver->getMyDriver()->getLocation();
            if (driverLocation == startOfTrip) {
                // make sure we have trip in te list
                if (!socketToDriver->getMyTexiCenter()->getMyTripList().empty()) {

                    // de-serialize for the flow
                    //for de-serializa we need put buffer to string
                    char buffer[1024];
                    socketToDriver->getMyTexiCenter()->getMyTcp()->reciveData(buffer, sizeof(buffer), socketToDriver->getMyDescriptor());
                    string bufferRecivedAdvance = bufferrrToString(buffer, sizeof(buffer));
                    //make instance of cab
                    int intFlow1;
                    //de serialize
                    boost::iostreams::basic_array_source<char> device2(bufferRecivedAdvance.c_str(),
                                                                       bufferRecivedAdvance.size());
                    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s7(device2);
                    boost::archive::binary_iarchive ia2(s7);
                    ia2 >> intFlow1;


                    //send the next trip by serialization
                    std::string serial_str1;
                    boost::iostreams::back_insert_device<std::string> inserter1(serial_str1);
                    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter1);
                    boost::archive::binary_oarchive oa1(s1);
                    trip = socketToDriver->getMyDriver()->getMyTrip();
                    oa1 << trip;
                    s1.flush();
                    //here we sent back the right trip
                    socketToDriver->getMyTexiCenter()->getMyTcp()->sendData(serial_str1,
                                                                            socketToDriver->getMyDescriptor());
                }
            }
        }
    pthread_mutex_unlock(&first);
}

void ConnectionClients::moveClient(SocketToDriver* socketToDriver) {
    // get the first trip from the list. if we will finish the trip, we will erase it from the list
    Trip *trip = socketToDriver->getMyDriver()->getMyTrip();
    // update the clock for each movement
    // make advance only in case the time at least such us the time of the trip
    if (trip != NULL) {
        if (trip->getTime() <= clockTime.getTime()) {
            vector<Node> path;
            Point newPosition;
            // get the path of the grid. we use clone for not delete the path
            //path = trip->getPathOfTripClone(*socketToDriver->getMyTexiCenter()->getMap());
            if (socketToDriver->getMyDriver()->getMyTrip() != NULL) {
                pthread_join(treadOfTrip, NULL);
                path = trip->getMyPath();
                // move one or two steps on the grid
                socketToDriver->getMyDriver()->moveStep(path, clockTime.getTime());
                // get the new location of the driver
                newPosition = socketToDriver->getMyDriver()->getLocation();

                char buffer[1024];
                // de-serialize for the flow
                socketToDriver->getMyTexiCenter()->getMyTcp()->reciveData(buffer, sizeof(buffer), socketToDriver->getMyDescriptor());
                //for de-serializa we need put buffer to string

                string bufferRecivedAdvance = bufferrrToString(buffer, sizeof(buffer));
                //make instance of cab
                int intFlow1;
                //de serialize
                boost::iostreams::basic_array_source<char> device2(bufferRecivedAdvance.c_str(),
                                                                   bufferRecivedAdvance.size());
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s8(device2);
                boost::archive::binary_iarchive ia2(s8);
                ia2 >> intFlow1;


                //serialize the point and send to client
                std::string serial_str;
                boost::iostreams::back_insert_device<std::string> inserter(serial_str);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
                boost::archive::binary_oarchive oa(s);
                oa << newPosition;
                s.flush();
                //here we sent back the 'go' for move one step
                socketToDriver->getMyTexiCenter()->getMyTcp()->sendData(serial_str, socketToDriver->getMyDescriptor());

                //after we end trip
                if (socketToDriver->getMyDriver()->getMyTrip()->getEndPointOfTrip() == newPosition) {
                    // delete trip
                    Trip *temp = socketToDriver->getMyDriver()->getMyTrip();
                    socketToDriver->getMyTexiCenter()->eraseTripWithId(temp->getRideId());
                    socketToDriver->getMyDriver()->initializeMyTripToNull();
                }
            }
        }
    }
}