//
// Created by ariel on 29/11/16.
//

#include "Driver.h"

Driver::Driver(int id, int age, char martialStatus, int experience, int vechileId, CabBase* taxiStandart) {
    myId = id;
    myAge = age;
    myMartialStatus = martialStatus;
    myExperience = experience;
    myVehicleId = vechileId;
    mySatisfication = 0;
    myTaxiStandart = taxiStandart;
    myLocation  = Point (0,0);
    myTrip = NULL;
    countTrip=0;
}
Driver::Driver() {}


void Driver::setLocation(Point p) {
    myLocation = p;
}

Point Driver::getLocation() {
    return myLocation;
}

int Driver::getStatisfication() {
    return mySatisfication;
}

void Driver::setStatisfication(int rate) {
    mySatisfication = rate;
}

void Driver::setTrip(Trip* trip) {
    myTrip = trip;
}

int Driver::getId() {
    return myId;
}

void Driver::moveStep(vector<Node> path, int currentTime) {
    if (currentTime < myTrip->getTime()){
        return;
    }
    //we get the index of out current point in the path of our trip
    int index = getIndexCurrentLocationPoint(path, myLocation);
    // check if i'm luxury
    if(myTaxiStandart->amILuxury() == 2) {
        //if the our next step of the luxury cab is out of the grid we will move only 1
        if(index - 2 >= 0) {
            setLocation(path.at(index - 2).getPointOfnode());
        } else {
            setLocation(path.at(index - 1).getPointOfnode());
        }
    } else {
        //standard cab
        setLocation(path.at(index - 1).getPointOfnode());
         }

    }

// search my location on the nodes vector's bfs
int Driver::getIndexCurrentLocationPoint(vector<Node> path, Point point){
    for(int i = 0; i < path.size(); i++){
        Point pointFromPath = path.at(i).getPointOfnode();
        //find the current point on the path and return the index
        if(point == pointFromPath) {
            return i;
        }
    }
}

void Driver::setCountTrips() {
    countTrip++;
}

int Driver::getCountTrips() {
    return countTrip;
}

int Driver::getMyCabId() {
    return myVehicleId;
}

Trip* Driver::getMyTrip() {
    return myTrip;
}

void Driver:: setCab(CabBase* newCab) {
    myTaxiStandart = newCab;
}

CabBase* Driver:: getCab() {
    return myTaxiStandart;
}
