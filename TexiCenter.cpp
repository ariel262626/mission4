//
// Created by ariel on 29/11/16.
//

#include "TexiCenter.h"
#include "Matrix2d.h"

TexiCenter::TexiCenter(vector<Driver*> driversList, vector<Passenger*> passengresList,
                       vector<CabBase*> standartCabList, vector<Trip> tripList, Matrix2d map, Bfs bfs) {
    myDriversList = driversList;
    myPassengresList = passengresList;
    myStandartCabList = standartCabList;
    myTripList = tripList;
    myMap = map;
    myBfs = bfs;
}

TexiCenter::TexiCenter() {}

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

void TexiCenter::startDriving() {
    vector<Node*> pathOfNodeInTrip;
    vector<Driver*> allDriversAtStartPointTrip;
    //flag told me if i already get the trip to driver
    int flag = 0;
    int tripNumber = myTripList.size();
    Driver* freeDriver;
    //run for all trip and find every trip driver
    for(int i = 0; i < tripNumber; i++) {
        Point startPiontOfTrip = myTripList.at(0).getStartPointOfTrip();
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
                freeDriver->setLocation(myTripList.at(0).getEndPointOfTrip());
                freeDriver->setCountTrips();
                myTripList.erase(myTripList.begin());
                break;
            }
        }
        //if we dont have a driver at the start point of trip
        if(flag != 1) {
            //we get all the point of the trip
            pathOfNodeInTrip = myTripList.at(0).getPathOfTrip(myMap);
            //for now start driving is to get the driver to his end point
            myDriversList.at(i)->setLocation(pathOfNodeInTrip.at(0)->getPointOfnode());
            myDriversList.at(i)->setCountTrips();
            //after using/doing a trip we can delete him from the list
            myTripList.erase(myTripList.begin());
        }
    }
}

Driver TexiCenter::findDriver(Passenger passenger) {
    //save the closest driver to the passenger
    Driver closestDriver;
    //initialize (max 10X10)
    long minDistance = 100;
    vector<Node*> listOfNodeInTrip;
    //check all the drivers
    for(int i = 0; i < myDriversList.size(); i++) {
        //get the driver location
        Node driverLocation =  Node(myDriversList[i]->getLocation(), false);
        //get the passenger location
        Node passengerLocation = Node(passenger.getStartPoint(), true);
        Matrix2d mapCopy = myMap;
        myBfs = Bfs(driverLocation, passengerLocation, 2, &mapCopy);
        //for each driver we need to calculate his path
        listOfNodeInTrip = myBfs.runBfs(&driverLocation, &passengerLocation);
        //check whos path is the shortest
        if(minDistance > listOfNodeInTrip.size())
        minDistance = listOfNodeInTrip.size();
        //update closest driver
        closestDriver = *(myDriversList[i]);
        //because he is the closest set him this trip
        closestDriver.setTrip(myTripList.at(i));
    }
    return closestDriver;
}

Point TexiCenter::findLocationOfDriver(int idDriverToFind) {
    Point locationOfDriver;
    for(int i = 0; i < myDriversList.size(); i++) {
        if(myDriversList.at(i)->getId() == idDriverToFind) {
            locationOfDriver = myDriversList.at(i)->getLocation();
        }
    }
    return locationOfDriver;
}

void TexiCenter::addDriverToDriverLIst(Driver* addDriver) {
    myDriversList.push_back(addDriver);
}

void TexiCenter::addCabToCabsLIst(CabBase* addCab) {
    myStandartCabList.push_back(addCab);
}

void TexiCenter::addTripToTripLIst(Trip addTrip) {
    myTripList.push_back(addTrip);
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

void TexiCenter::setTripList(vector<Trip> tripsList) {
    myTripList.swap(tripsList);
}

void TexiCenter::setMap(Matrix2d map) {

    myMap.setHigh(map.getHigh());
    myMap.setWidth(map.getWidth());
    myMap.setobstaclePoint(map.getObstaclesList());
    myMap = map;
}

Driver* TexiCenter::getDriverInIndex(int i) {
    return myDriversList.at(i);
}

CabBase* TexiCenter::getCabInIndex(int i) {
    return myStandartCabList.at(i);
}

Trip TexiCenter::getTripInIndex(int i) {
    return myTripList.at(i);
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