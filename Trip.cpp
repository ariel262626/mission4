//
// Created by ariel on 29/11/16.
//
//#include "Point.h"
//#include "Node.h"
#include "Bfs.h"
//#include "Matrix2d.h"
#include "Trip.h"

Trip::Trip(int rideId, int xStart, int yStart, int xEnd, int yEnd, int passengerNumber, double tarrif, int time){
    myRideId = rideId;
    myXstart = xStart;
    myYstart = yStart;
    myXend = xEnd;
    myYend = yEnd;
    myMetersPassed = 0;
    myPassengerNumber = passengerNumber;
    myTariff = tarrif;
    myTime = time;
    isTripTaken = false;
    isPathReady = false;
}

Trip::Trip() { }


//we have the start point and end point so we calculate all the path with bfs here
vector<Node*> Trip::getPathOfTrip(Matrix2d map) {
    vector<Node*> listOfNodeInTrip;
    Node startNode = Node(Point(myXstart, myYstart), false);
    Node endNode = Node(Point(myXend, myYend), true);
    Bfs bfs = Bfs(startNode, endNode, 2, &map);
    //we get all the points of the trip. run the bfs for that
    listOfNodeInTrip = bfs.runBfs(&startNode, &endNode);
    //we get the path to member
    //myPath.swap(*listOfNodeInTrip);
    return listOfNodeInTrip;
}

vector<Node> Trip::getPathOfTripClone(Matrix2d map) {
    pthread_mutex_lock(&bfsFirst);
    vector<Node*> listOfNodeInTrip;
    vector<Node> listOfNodeInTripclone;
    for (int i = 999; i >= 0; i--) {
        for (int j = 0; j < 1000; j++) {
            map.matrix[j][i]->setFlagToFalse();
        }
    }
    Node startNode = Node(Point(myXstart, myYstart), false);
    Node endNode = Node(Point(myXend, myYend), true);
    Bfs bfs = Bfs(startNode, endNode, 2, &map);
    //we get all the points of the trip. run the bfs for that
    listOfNodeInTrip = bfs.runBfs(&startNode, &endNode);
    //if the path is empty
    if(listOfNodeInTrip.empty()) {
        vector<Node> emptyPath;
        myPath = emptyPath;
    }
    for (int i = 0; i < listOfNodeInTrip.size(); ++i) {
        listOfNodeInTripclone.push_back(*listOfNodeInTrip.at(i));
    }
    myPath = listOfNodeInTripclone;
    isPathReady = true;
    pthread_mutex_unlock(&bfsFirst);
    return listOfNodeInTripclone;
}

Point Trip::getStartPointOfTrip() {
    return Point(myXstart, myYstart);
}

Point Trip::getEndPointOfTrip() {
    return Point(myXend, myYend);
}

int Trip::getPassengersNumber() {
    return myPassengerNumber;
}

int Trip::getRideId() {
    return myRideId;
}

int Trip::getMetersPassed() {
    return myMetersPassed;
}

void Trip::setMetersPassed(int x) {
    myMetersPassed = x;
}

void Trip::setPassengersNumber(int x) {
    myPassengerNumber = x;
}

void Trip::setTime() {
    myTime++;
}

void Trip::setRideId(int id) {
    myRideId = id;
}

int Trip::getTime() {
    return myTime;
}

void Trip:: setIsTakenTrue() {
    isTripTaken = true;
}

void Trip:: setIsTakenFalse() {
    isTripTaken = false;
}

bool Trip:: getIsTaken(){
    return isTripTaken;
}

vector<Node> Trip:: getMyPath(){
    return myPath;
}

void Trip::joinTrip(){
    while(!isPathReady) {
        sleep(1);
    }
}