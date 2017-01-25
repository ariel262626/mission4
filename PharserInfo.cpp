//
// Created by dvir on 13/12/16.
//

#include <cstring>
#include "Driver.h"
#include "PharserInfo.h"
bool isArgumentValid;

/**
this class charge to pharse the input of the user and create corresponding objgects.
 */

PharserInfo:: PharserInfo (string input){
    myInput = input;
}

Matrix2d* PharserInfo:: createGrid (){
    bool isGridVaild = true;
    int high, width, index;
    string str1, str2;

    do {
        // if the grid not valid-> get another input
        if (!isGridVaild){
            getline(cin, myInput);
        }
        isGridVaild = true;

        //find the " " in the input of the user
        index = myInput.find(" ");
        //enter each of the strings to str.
        str1 = myInput.substr(0,index);
        str2 = myInput.erase(0,index+1);


        // check if the arguments are not chars..
        for (int i = 0; i < str1.size(); i++){
            if(!isdigit(str1[i])){
                isGridVaild = false;
                cout<< "-1" << endl;
                break;
            }
        }
        // check if the arguments are not chars..
        for (int i = 0; i < str2.size(); i++){
            if(!isdigit(str2[i])){
                // print -1 only is we didnt print it in last loop yet
                if (isGridVaild){
                    cout<< "-1" << endl;
                }
                // change the boolean
                isGridVaild = false;
                break;
            }
        }
        // now we sure we have only digits
        //split the coordinates for the program and pharse them to int
        if (isGridVaild) {
            width = stoi(str1);
            high = stoi(str2);
        }
    } while (high <= 0 || width <= 0 || !isGridVaild);

    //now erase str1, str2
    str1 = str1.erase(0,index);
    str2 = str2.erase(0,index);
    // create new grid and return it to the main
    vector <Point> obsList;
    Matrix2d* map = new Matrix2d(high, width, obsList);
    return map;
}

Driver* PharserInfo::createDriver () {
    Driver* driver;
    if(!checkIfDriverValid(myInput)) {
        driver->setId(-1);
        isArgumentValid = false;
        return driver;
    }
    // get from the user: id, age status, experience and cabId of the driver
    // use in methods to translate the data
    int driverId = getOneElementInt();
    int driverAge = getOneElementInt();
    char driverStatus = getOneElementchar();
    int driverExperience = getOneElementInt();
    int driverVehicleId = getOneElementInt();

    // create new driver and return it to the main
    CabBase cab = CabBase();
    driver = new Driver(driverId, driverAge, driverStatus, driverExperience, driverVehicleId, &cab);
    return driver;
}

Trip* PharserInfo::createNewRide (){
    Trip* trip;
// get from the user: ridr id, start point, end point, number of passengers and tarrif
// of the cab to create ride
    if(!checkIfTripValid(myInput)) {
        trip->setRideId(-1);
        isArgumentValid = false;
        return trip;
    }
    int rideId = getOneElementInt();
    int startX = getOneElementInt();
    int startY = getOneElementInt();
    int endX = getOneElementInt();
    int endY = getOneElementInt();
    int numPassenger = getOneElementInt();
    double tariff = getOneElementDouble();
    int time = getOneElementInt();
    // create trip with the data of we got from the user
    trip = new Trip(rideId, startX, startY, endX, endY, numPassenger, tariff, time);
    return trip;
}

CabBase* PharserInfo::createVehicle (){
    CabBase* cabBase;
    if(!checkIfCabBaseValid(myInput)) {
        cabBase->setCabID(-1);
        isArgumentValid = false;
        return cabBase;
    }
    // pharser the data by the functions
    int vehicleId = getOneElementInt();
    int cabType = getOneElementInt();
    char manufacturer = getOneElementchar();
    char color = getOneElementchar();
    //create new cab
    CabBase *vehicle = new CabBase(vehicleId, cabType, manufacturer, color, NULL);
    return vehicle;
}

bool PharserInfo::checkStringIfDigit(string myInput) {
    for (int i = 0; i < myInput.size(); i++) {
        if (!isdigit(myInput[i])) {
            isArgumentValid = false;
            cout << "-1" << endl;
        }
    }
}

vector <Point> PharserInfo:: obstaclePoints (){
    vector <Point> listObstacle;

    // if the input not a number..
    // check if the arguments are not chars..
    for (int i = 0; i < myInput.size(); i++){
        if(!isdigit(myInput[i])){
            isArgumentValid = false;
            cout<< "-1" << endl;
            return listObstacle;
        }
    }
    // take the string of the user and pharse it to integer
    int numOfObstaclePoints = stoi(myInput);
    // check if number of obstacles is not less from zero
    if (numOfObstaclePoints < 0) {
        isArgumentValid = false;
        cout<< "-1" << endl;
        return listObstacle;
    }
    // if 0 -> we won't expect from the user to insert obstacle points
    if (numOfObstaclePoints == 0){
        return listObstacle;
    }

    listObstacle = getMyListObstacles (numOfObstaclePoints);
    return listObstacle;
}

vector <Point> PharserInfo:: getMyListObstacles (int numOfObstaclePoints){
    isArgumentValid = true;
    int index1,index2;
    string str1, str2, p;
    vector <Point> listObstacle;
    // iterate on number of obstacle and request the user to enter the obstacles
    for (int i = 0; i < numOfObstaclePoints; i++) {
        cin.ignore();
        getline(cin , p);// >> p;
        // if the point not valid-> end the function
        if (!checkIfObstaclesValid (p)){
            cout<< "-1" << endl;
            // update our boolean element
            isArgumentValid = false;
            return listObstacle;
        }
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
}

bool PharserInfo::checkIfDriverValid(string myInput) {
    int driverId = getOneElementInt();
    if((driverId < 0) || (!isArgumentValid)) {
        return false;
    }
    int driverAge = getOneElementInt();
    if((driverAge < 0)|| (!isArgumentValid)) {
        return false;
    }
    char driverStatus = getOneElementchar();
    if((driverStatus != 'S')&&(driverStatus != 'M')&&(driverStatus != 'D')&&(driverStatus != 'W')) {
        return false;
    }
    int driverExperience = getOneElementInt();
    if((driverExperience < 0)||(!isArgumentValid)) {
        return false;
    }
    int driverVehicleId = getOneElementInt();
    if((driverVehicleId < 0)||(!isArgumentValid)) {
        return false;
    }
    //to many arguments
    if(myInput.length() > 0) {
        return false;
    }
}

bool PharserInfo::checkIfCabBaseValid(string myInput) {
    int vehicleId = getOneElementInt();
    if((vehicleId < 0)||(!isArgumentValid)) {
        return false;
    }
    int cabType = getOneElementInt();
    if((cabType < 0)||(cabType != 1)&&(cabType != 2)||(!isArgumentValid)) {
        return false;
    }
    char manufacturer = getOneElementchar();
    if((manufacturer != 'H')&&(manufacturer != 'S')&&(manufacturer != 'T')&&(manufacturer != 'F')) {
        return false;
    }
    char color = getOneElementchar();
    if((color != 'R')&&(color != 'B')&&(color != 'G')&&(color != 'P')&&(color != 'W')) {
        return false;
    }
    //to many arguments
    if(myInput.length() > 0) {
        return false;
    }
}

bool PharserInfo::checkIfTripValid(string myInput) {
    int rideId = getOneElementInt();
    if((rideId < 0)||(!isArgumentValid)) {
        return false;
    }
    int startX = getOneElementInt();
    if((startX < 0)||(!isArgumentValid)) {
        return false;
    }
    int startY = getOneElementInt();
    if((startY < 0)||(!isArgumentValid)) {
        return false;
    }
    int endX = getOneElementInt();
    if((endX  < 0)||(!isArgumentValid)) {
        return false;
    }
    int endY = getOneElementInt();
    if((endY  < 0)||(!isArgumentValid)) {
        return false;
    }
    int numPassenger = getOneElementInt();
    if((numPassenger  < 0)||(!isArgumentValid)) {
        return false;
    }
    double tariff = getOneElementDouble();
    if(tariff  < 0) {
        return false;
    }
    int time = getOneElementInt();
    if((time  < 0)||(!isArgumentValid)) {
        return false;
    }
    //to many arguments
    if(myInput.length() > 0) {
        return false;
    }
}

bool PharserInfo:: checkIfObstaclesValid(string point){
    int middleIndex = point.find(",");
    if (middleIndex <= 0){
        return false;
    }
    string str1 = point.substr(0, middleIndex);
    string str2 = point.erase(0, middleIndex + 1);

    //check if the string in point is a number
    for (int i = 0; i < str1.size(); i++){
        if(!isdigit(str1[i])){
            return false;
        }
    }
    // check if the arguments are not chars..
    for (int i = 0; i < str2.size(); i++){
        if(!isdigit(str2[i])){
            return false;
        }
    }
    int index1 = stoi(str1);
    int index2 = stoi(str2);
    if (index1 < 0 || index2 < 0){
        return false;
    }
    return true;

}

int PharserInfo:: getOneElementInt() {
    int index;
    string str1;
    index = myInput.find(",");
    str1 = myInput.substr(0, index);
    if(!checkStringIfDigit(str1)) {
        isArgumentValid = false;
        return 0;
    }
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