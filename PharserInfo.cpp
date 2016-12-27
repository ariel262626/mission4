//
// Created by dvir on 13/12/16.
//

#include <cstring>
#include "Driver.h"
#include "PharserInfo.h"

/**
this class charge to pharse the input of the user and create corresponding objgects.
 */

PharserInfo:: PharserInfo (string input){
    myInput = input;
}

Matrix2d* PharserInfo:: createGrid (){
    //find the " " in the input of the user
    int index = myInput.find(" ");
    //enter each of the strings to str.
    string str1 = myInput.substr(0,index);
    string str2 = myInput.erase(0,index+1);

    //split the coordinates for the program and pharse them to int
    int width=stoi(str1);
    int high=stoi(str2);
    //now erase str1, str2
    str1 = str1.erase(0,index);
    str2 = str2.erase(0,index);
    // create new grid and return it to the main
    vector <Point> obsList;
    Matrix2d* map = new Matrix2d(high, width, obsList);
    return map;
}

Driver* PharserInfo:: createDriver (){
// get from the user: id, age status, experience and cabId of the driver
    // use in methods to translate the data
    int driverId = getOneElementInt();
    int driverAge = getOneElementInt();
    char driverStatus = getOneElementchar();
    int driverExperience = getOneElementInt();
    int driverVehicleId = getOneElementInt();

    // create new driver and return it to the main
    CabBase cab = CabBase();
    Trip trip = Trip();
    Driver *driver = new Driver(driverId, driverAge, driverStatus, driverExperience, driverVehicleId, cab,
                                trip);
    return driver;
}

Trip PharserInfo:: createNewRide (){
// get from the user: ridr id, start point, end point, number of passengers and tarrif
// of the cab to create ride

    int rideId = getOneElementInt();
    int startX = getOneElementInt();
    int startY = getOneElementInt();
    int endX = getOneElementInt();
    int endY = getOneElementInt();
    int numPassenger = getOneElementInt();
    double tariff = getOneElementDouble();
    int time;
    // create trip with the data of we got from the user
    Trip trip = Trip(rideId, startX, startY, endX, endY, numPassenger, tariff, time);
    return trip;
}

CabBase* PharserInfo:: createVehicle (){

    // pharser the data by the functions
    int vehicleId = getOneElementInt();
    int cabType = getOneElementInt();
    char manufacturer = getOneElementchar();
    char color = getOneElementchar();

    //create new cab
    CabBase *vehicle = new CabBase(vehicleId, cabType, manufacturer, color, NULL, NULL);
    return vehicle;
}

vector <Point> PharserInfo:: obstaclePoints (){
    int index1,index2;
    string str1, str2, p;
    vector <Point> listObstacle;
    // take the string of the user and pharse it to integer
    int numOfObstaclePoints = stoi(myInput);
    // if 0 -> we won't expect from the user to insert obstacle points
    if (numOfObstaclePoints == 0){
        return listObstacle;
    }
    // iterate on number of obstacle and request the user to enter the obstacles
    for (int i = 0; i < numOfObstaclePoints; i++) {
        cin >> p;
        // pharse the data
        int middleIndex = p.find(",");
        str1 = p.substr(0, middleIndex);
        str2 = p.erase(0, middleIndex + 1);
        //split the coordinates for the program
        index1 = stoi(str1);
        index2 = stoi(str2);
        Point obstacle = Point(index1, index2);
        // enter the points into the vector
        listObstacle.push_back(obstacle);
    }
    return listObstacle;
}


int PharserInfo:: getOneElementInt (){
    int index;
    string str1;
    index = myInput.find(",");
    str1 = myInput.substr(0, index);
    int elm = stoi(str1);
    // delete from start to ','
    eraseComma(index);
    return elm;
}

char PharserInfo:: getOneElementchar (){
    int index;
    string str1;
    index = myInput.find(",");
    str1 = myInput.substr(0, index);
    char elm = str1[0];
    // delete from start to ','
    eraseComma(index);
    return elm;
}

double PharserInfo:: getOneElementDouble () {
    int index;
    string str1;
    index = myInput.find(",");
    str1 = myInput.substr(0, index);
    double elm = stod(str1);
    // delete from start to ','
    eraseComma(index);
    return elm;
}

void PharserInfo:: eraseComma (int index){
    // check if we have another input (input , another input)
    if (myInput[index] == ',') {
        myInput = myInput.erase(0, index + 1);
        // if not -> it's end of line and we haven't any comma
    } else {
        myInput = myInput.erase(0, index);
    }
}