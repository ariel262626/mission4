//
// Created by ariel on 29/11/16.
//
#include "Point.h"
#include "Node.h"
#include "Bfs.h"
#include "Matrix2d.h"
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
}

Trip::Trip() {}


Trip::~Trip() {
    delete this;
}

//we have the start point and end point so we calculate all the path with bfs here
vector<Node*> Trip::getPathOfTrip(Matrix2d map) {
    vector<Node*> listOfNodeInTrip;
        Node startNode = Node(Point(myXstart, myYstart), false);
        Node endNode = Node(Point(myXend, myYend), true);
        Bfs bfs = Bfs(startNode, endNode, 2, &map);
        //we get all the points of the trip. run the bfs for that
        listOfNodeInTrip = bfs.runBfs(&startNode, &endNode);
        return listOfNodeInTrip;
}

vector<Node> Trip::getPathOfTripClone(Matrix2d map) {
    vector<Node*> listOfNodeInTrip;
    vector<Node> listOfNodeInTripclone;
    Node startNode = Node(Point(myXstart, myYstart), false);
    Node endNode = Node(Point(myXend, myYend), true);
    Bfs bfs = Bfs(startNode, endNode, 2, &map);
    //we get all the points of the trip. run the bfs for that
    listOfNodeInTrip = bfs.runBfs(&startNode, &endNode);
    for (int i = 0; i < listOfNodeInTrip.size(); ++i) {
        listOfNodeInTripclone.push_back(*listOfNodeInTrip.at(i));
    }
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

int Trip::getTime() {
    return myTime;
}

