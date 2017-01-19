//
// Created by ariel on 29/11/16.
//

#include "TexiCenter.h"
#include "Matrix2d.h"
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

TexiCenter::TexiCenter(vector<Driver*> driversList, vector<Passenger*> passengresList,
                       vector<CabBase*> standartCabList, vector<Trip*> tripList, Matrix2d* map, Bfs bfs, Socket* tcp) {
    myDriversList = driversList;
    myPassengresList = passengresList;
    myStandartCabList = standartCabList;
    myTripList = tripList;
    myMap = map;
    myBfs = bfs;
    myTcp = tcp;
}

TexiCenter::TexiCenter() {}

TexiCenter::~TexiCenter() {
    // delete the all new allocation memory before the object of taxi center is over
    delete myMap;
    for (int i = 0; i < myDriversList.size(); i++) {
        delete getDriverInIndex(i);
    }
    for (int i = 0; i < myStandartCabList.size(); i++) {
        delete getCabInIndex(i);
    }
}

/**
 * get all the drivers at the point of the start point of trip
 * @param myDriversList - the list of drivers
 * @param startPiontOfTrip - start point of trip
 * @return vector of the driver at the point
 */
vector<Driver*> getAllDriversAtThisPoint(vector<Driver*> myDriversList,Point startPiontOfTrip) {
    vector<Driver*> driversAtPoint;
    for (int i = 0; i < myDriversList.size(); i++) {
        if(myDriversList.at(i)->getLocation() == startPiontOfTrip) {
            Driver* driver = myDriversList.at(i);
            driversAtPoint.push_back(driver);
        }
    }
    return driversAtPoint;
}
/**
 * for mission 6. move the drivers with their corresponding trip to the end point of the path's trip
 */
void TexiCenter::startDriving() {
    vector<Node*> pathOfNodeInTrip;
    vector<Driver*> allDriversAtStartPointTrip;
    //flag told me if i already get the trip to driver
    int flag = 0;
    int tripNumber = myTripList.size();
    Driver* freeDriver;
    //run for all trip and find every trip driver
    for(int i = 0; i < tripNumber; i++) {
        Point startPiontOfTrip = myTripList.at(0)->getStartPointOfTrip();
        //initialize
        flag = 0;
        /*find if there is driver at the point of the starting point of the trip
         * if there is this driver will take the trip*/
        for(int j = 0; j < myDriversList.size(); j++) {
            Point driverLocation = myDriversList.at(j)->getLocation();
            if (driverLocation == startPiontOfTrip) {
                allDriversAtStartPointTrip = getAllDriversAtThisPoint(myDriversList, startPiontOfTrip);
                freeDriver = allDriversAtStartPointTrip.at(0);
                for(int k = 0; k < allDriversAtStartPointTrip.size(); k++) {
                    if(allDriversAtStartPointTrip.at(k)->getCountTrips() < freeDriver->getCountTrips()){
                        freeDriver = allDriversAtStartPointTrip.at(k);
                    }
                }
                flag = 1;
                freeDriver->setLocation(myTripList.at(0)->getEndPointOfTrip());
                freeDriver->setCountTrips();

                // here we need to release to trip from heap

                myTripList.erase(myTripList.begin());
                break;
            }
        }
        //if we dont have a driver at the start point of trip
        if(flag != 1) {
            //we get all the point of the trip
            pathOfNodeInTrip = myTripList.at(0)->getPathOfTrip(*myMap);
            //for now start driving is to get the driver to his end point
            myDriversList.at(i)->setLocation(pathOfNodeInTrip.at(0)->getPointOfnode());
            myDriversList.at(i)->setCountTrips();
            //after using/doing a trip we can delete him from the list
            myTripList.erase(myTripList.begin());
        }
    }
}
/**
 * here we will find the closest driver of the passenger location.
 * we will iterate on the list of the driver and check their location.
 * @param passenger
 * @return the close driver
 */
//Driver TexiCenter::findDriver(Passenger passenger) {
//    //save the closest driver to the passenger
//    Driver closestDriver;
//    //initialize (max 10X10)
//    long minDistance = 100;
//    vector<Node*> listOfNodeInTrip;
//    //check all the drivers
//    for(int i = 0; i < myDriversList.size(); i++) {
//        //get the driver location
//        Node driverLocation =  Node(myDriversList[i]->getLocation(), false);
//        //get the passenger location
//        Node passengerLocation = Node(passenger.getStartPoint(), true);
//        Matrix2d* mapCopy = myMap;
//        myBfs = Bfs(driverLocation, passengerLocation, 2, mapCopy);
//        //for each driver we need to calculate his path
//        listOfNodeInTrip = myBfs.runBfs(&driverLocation, &passengerLocation);
//        //check whos path is the shortest
//        if(minDistance > listOfNodeInTrip.size())
//        minDistance = listOfNodeInTrip.size();
//        //update closest driver
//        closestDriver = *(myDriversList[i]);
//        //because he is the closest set him this trip
//        closestDriver.setTrip(myTripList.at(i));
//    }
//    return closestDriver;
//}
/**
 * here we get id drier and find the right driver in the vector
 * @param idDriverToFind: get index id driver
 * @return point-> location of driver
 */
Point TexiCenter::findLocationOfDriver(int idDriverToFind) {
    Point locationOfDriver;
    // iterate on the all vector
    for(int i = 0; i < myDriversList.size(); i++) {
        if(myDriversList.at(i)->getId() == idDriverToFind) {
            // get my location
            locationOfDriver = myDriversList.at(i)->getLocation();
        }
    }
    return locationOfDriver;
}
/**
 * add driver to the vector
 * @param addDriver
 */
void TexiCenter::addDriverToDriverLIst(Driver* addDriver) {
    myDriversList.push_back(addDriver);
}
/**
 * add cab to the vector
 * @param addCab
 */
void TexiCenter::addCabToCabsLIst(CabBase* addCab) {
    myStandartCabList.push_back(addCab);
}
/**
 * here we add trip to the list. notice we add the trip and sort the list so the
 * time clock of the trip will insert in the right place in the list (push and sort)
 * @param addTrip
 */
void TexiCenter::addTripToTripLIst(Trip* addTrip) {
    Trip* temp;
    myTripList.push_back(addTrip);
    // now sort the vector
    if(myTripList.size() > 1) {
    for (int i = 0; i < myTripList.size() - 1; i++) {
        for (int j = 0; j < myTripList.size() - 1; j++) {
            if (myTripList.at(j)->getTime() > myTripList.at(j + 1)->getTime()) {
                temp = myTripList.at(j);
                myTripList.at(j) = myTripList.at(j + 1);
                myTripList.at(j + 1) = temp;
            }
        }
    }
    }
}

void TexiCenter::setDriverList(vector<Driver*> driversList) {
        myDriversList.swap(driversList);
}

void TexiCenter::setPassengerList(vector<Passenger*> passengresList) {
    myPassengresList.swap(passengresList);
}


void TexiCenter::setBaseCabeList(vector<CabBase*> baseCabList) {
    myStandartCabList.swap(baseCabList);
}

void TexiCenter::setTripList(vector<Trip*> tripsList) {
    myTripList.swap(tripsList);
}

void TexiCenter::setMap(Matrix2d* map) {
   // myMap->setHigh(map->getHigh());
   // myMap->setWidth(map->getWidth());
   // myMap->setobstaclePoint(map->getObstaclesList());
    myMap = map;
}

Matrix2d* TexiCenter::getMap() {
    return myMap;
}

Driver* TexiCenter::getDriverInIndex(int i) {
    return myDriversList.at(i);
}

CabBase* TexiCenter::getCabInIndex(int i) {
    return myStandartCabList.at(i);
}

Trip* TexiCenter::getTripInIndex(int i) {
    return myTripList.at(i);
}
//get the next trip that not taken yet
Trip* TexiCenter::getFreeTrip() {
    cout<<"my trip number: ";
    cout<<myTripList.size()<<endl;
    for (int i = 1; i < getMyTripList().size(); i++){
        cout<<"my trip number: 11111";
        if(!getMyTripList().at(i)->getIsTaken()) {
            getMyTripList()[i]->setIsTakenTrue();
            return getMyTripList()[i];
        }
    }
    if (getMyTripList().size() == 1){
        return getMyTripList()[0];
    }
    if(getMyTripList().size() == 0) {
        cout<<"my trip number after was 0: ";
        cout<<myTripList.size()<<endl;
    }
}

CabBase* TexiCenter::getCabWithId(int id) {
    CabBase* cabBase;
    for(int k = 0; k < myStandartCabList.size(); k++) {
        if(myStandartCabList.at(k)->getCabId() == id) {
            cabBase = getCabInIndex(k);
        }
    }
    return cabBase;
}

Driver* TexiCenter::getDriverWithId(int id) {
    Driver* driver;
    for(int k = 0; k < myDriversList.size(); k++) {
        if(myDriversList.at(k)->getId() == id) {
            driver = getDriverInIndex(k);
        }
    }
    return driver;
}

void TexiCenter::eraseTripWithId(int rideId) {
    Trip *trip;
    for(int i = 0; i < myTripList.size(); i++) {
        if(rideId == myTripList.at(i)->getRideId()) {
            int index = getTripWithId(rideId);
            trip = myTripList.at(i);
            delete trip;
            myTripList.erase(myTripList.begin() + index);
        }
    }
}

int TexiCenter::getTripWithId(int id) {
    for(int i = 0; i < myTripList.size(); i++) {
        if(myTripList.at(i)->getRideId() == id) {
            return i;
        }
    }
}

vector<Driver*> TexiCenter:: getMyDriverList (){
    return myDriversList;
}

vector<Trip*> TexiCenter:: getMyTripList (){
        return myTripList;
}

vector<CabBase*> TexiCenter:: getMyCabBaseList (){
    return myStandartCabList;
}

void TexiCenter::setCabToDriver(Driver* driver) {
    //find the right taxi for connect the cab to the driver
    int cabId = driver->getMyCabId();
    CabBase* cabBase = getCabWithId(cabId);
    driver->setCab(cabBase);
}

ClockTime TexiCenter::getMyClockTime() {
    return myClockTime;
}

Socket* TexiCenter::getMyTcp() {
    return myTcp;
}

void TexiCenter::setMyTcp(Socket* tcp) {
    myTcp = tcp;
}

vector<SocketToDriver*> TexiCenter::getMySocketToDriverList() {
    return mySocketToDriverList;
}

void TexiCenter::setMySocketToDriverList(SocketToDriver* socketToDriver) {
    mySocketToDriverList.push_back(socketToDriver);
}
