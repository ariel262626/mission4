//
// Created by ariel on 30/11/16.
//
#include <cstring>
#include "SocketToDriver.h"
#include "GameFlow.h"
#include "PharserInfo.h"
#include "Tcp.h"
#include "ConnectionClients.h"
#include "BooleanToDescriptor.h"
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
#include <vector>
extern pthread_t treadOfTrip;
extern int choose;
extern ClockTime clockTime;
extern vector <BooleanToDescriptor> myBoolList;
extern int countAction;
extern bool isTripReady;
extern bool isPrintAllready;
extern bool isArgumentValid;
bool isThreadPoolOver;
//bool isValid;
vector<pthread_t> treadsOfDrivers;

GameFlow:: GameFlow (Socket* tcp){
    myTcp = tcp;
    texiCenter = new TexiCenter();
    myThreadPoolTrips = new ThreadPoolTrips(5);
}

GameFlow::GameFlow() {}

 void GameFlow:: run() {
     isPrintAllready = false;
     isArgumentValid = true;
     bool switchCaseValid = true;
     // here we will put the all information
     int localChoose;
     texiCenter->setMyTcp(myTcp);
     string stringGrid, stringObst;
     vector<Point> listObstacle;
     Driver *driver;
     Matrix2d *newMap;
    // ConnectionClients connectionClients = ConnectionClients();
     vector<SocketToDriver*> listSocketToDriver;
     do {
         //find high and width -> use in class of pharser for translate the data
         getline(cin, stringGrid);
         PharserInfo pharseGrid = PharserInfo(stringGrid);
         //create map
         newMap = pharseGrid.createGrid();
         // insert obstacle points
         getline(cin, stringObst);
         // insert obstacles,if the number is big from zero, the function request from the user
         // to insert the obstacle points.
         PharserInfo pharseObstacles = PharserInfo(stringObst);
         listObstacle = pharseObstacles.obstaclePoints(newMap);
         // if the input not valid and we need another input, first delete the map from heap.
         if (!isArgumentValid){
             delete newMap;
         }
     } while (!isArgumentValid);
     // insert the list of obstacles to the map (grid)
     newMap->setobstaclePoint(listObstacle);
     // insert the map to taxi center, because the taxi center is in charge of all the programm actualy
     texiCenter->setMap(newMap);
     myThreadPoolTrips->setMap(newMap);
     // request from the user mission to enter. we will expect all the time to another mission,
     // therefor we return on it until the user enter 7 (end of mission).
     while (true) {
         // choose mission to perform
         cin >> localChoose;
         if (!myBoolList.empty()) {
             for (int i = 0; i < texiCenter->getMyDriverList().size(); i++) {
                 myBoolList[i].setIsMovedToFalse();
             }
         }
         switch(localChoose) {
             case 1: {
                 string myInput;
                 //enter dummy of cin
                 cin.ignore();
                 //get from user how much drivers we need to get
                 getline(cin, myInput);
                 //valid check
                 if(!checkIsOneNumber(myInput)) {
                     cout<< "-1" << endl;
                     break;
                 }
                 int numOfDrivers = stoi(myInput);
                 listSocketToDriver = getDriversFromClients(numOfDrivers);
                 for (int i = 0; i < texiCenter->getMyCabBaseList().size(); i++) {
                     driver = texiCenter->getDriverInIndex(i);
                     texiCenter->setCabToDriver(driver);
                     CabBase *cabBase = driver->getCab();
                     sendCab(cabBase, listSocketToDriver[i]->getMyDescriptor());
                     BooleanToDescriptor booleanToDescriptor = BooleanToDescriptor(listSocketToDriver[i]->getMyDescriptor());
                     myBoolList.push_back(booleanToDescriptor);
                 }
                 break;
             }
             case 2: {
                 isTripReady = false;
                 choose = 2;
                 getNewRide();
                 if(!isArgumentValid) {
                     cout<< "-1" << endl;
                     break;
                 }
                 break;
             }
             case 3: {
                 choose = 3;
                 getNewCab();
                 break;
             }
             case 4: {
                 isPrintAllready = false;
                 choose = 4;
                 printCurrentLocation();
                 isPrintAllready = false;
                 break;
             }
             case 7: {
                 isPrintAllready = true;
                 isThreadPoolOver = true;
                 // the allocate memory which placed in taxi center will be deleted when the program finish.
                 // now, call function that send special trip to shut down the program
                 choose = 7;

                 waitForMe(texiCenter->getMyDriverList().size());
                 for (int j = 0; j < texiCenter->getMyDriverList().size(); ++j) {
                     pthread_join(treadsOfDrivers.at(j), NULL);
                 }
                 delete texiCenter;
                 delete myThreadPoolTrips;
                 delete myTcp;
                 return;
             }
             case 9: {
                 choose = 9;
                 waitForMe(texiCenter->getMyDriverList().size());
                 // update the clock
                 clockTime.setTime();
                 break;
             }
             default:
                 cout<< "-1" << endl;
         }
     }
 }
//valid Inputs
bool GameFlow::checkIsOneNumber(string myInput) {
    int numDrivers;
    if(myInput.length() > 1) {
        return false;
    }
    if(!isdigit(myInput[0])) {
        return false;
    } else {
        numDrivers = stoi(myInput);
    }
    if(numDrivers < 0) {
        return false;
    }
    return true;
}


//case 4
void GameFlow::printCurrentLocation() {
    //insert id of driver
    int DriverId;
    Point location;
    cin >> DriverId;
    // find location of the driver in the grid and print it
    location = texiCenter->findLocationOfDriver(DriverId);
    cout << location << endl;
    isPrintAllready = true;
}

void GameFlow::waitForMe(int numOfThreads) {
    while(countAction != numOfThreads) {

    }
    countAction = 0;
}

/**
* this function convert char* to string for the serialize
* @param buffer
* @param bufflen: lenth of the buffer
* @return the string buffer
*/
string bufferToString(char* buffer, int bufflen) {
    std::string ret(buffer, bufflen);
    return ret;
}

void GameFlow::getNewCab() {
    // get new cab from the user
    string insertVehicle;
    //cin >> insertVehicle;
    cin.ignore();
    getline(cin, insertVehicle);
    // use in the pharser class to handle the data
    PharserInfo pharser = PharserInfo(insertVehicle);
    CabBase* vehicle = pharser.createVehicle();
    if(vehicle->getCabId() == -1) {
        delete vehicle;
        return;
    }
    // add cab to taxi center
    texiCenter->addCabToCabsLIst(vehicle);
}

void GameFlow::getNewRide() {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    // get new ride from the user
    string insertRide;
    cin.ignore();
    getline(cin, insertRide);
    // use in the pharser class to handle the data
    PharserInfo pharser = PharserInfo(insertRide);
        Trip* trip = pharser.createNewRide();
    if(trip->getRideId() == -1) {
        delete trip;
        return;
    }
    // add trip to taxi center - we need to sort the trip list according the time
    TripMap* tripMap = new TripMap(trip, texiCenter->getMap());
    texiCenter->addTripToTripLIst(trip);
    myThreadPoolTrips->add_task(trip);
    //pthread_create(&treadOfTrip, &attr, path, tripMap);
    //pthread_join(treadOfTrip, NULL);
    //path is not valid
    trip->joinTrip();
    if(trip->getMyPath().empty()) {
        int TripToRemoveId = trip->getRideId();
        texiCenter->eraseTripWithId(TripToRemoveId);
    }
    delete tripMap;
    isTripReady = true;
}
/*
void* GameFlow::path(void* tripMap) {
    TripMap* tripMap1 = (TripMap*)tripMap;
    tripMap1->getTrip()->getPathOfTripClone(*tripMap1->getMap());
}*/

vector <SocketToDriver*> GameFlow::getDriversFromClients(int numberOfDrivers) {
    Driver *driver;
    char buffer[1024];
    //int numberOfDrivers;
    //will count my actions of thread
    countAction = 0;
    int const amountsTreadsofClients = numberOfDrivers;
    int socketDescriptor = myTcp->initialize();
    for (int i = 0; i < numberOfDrivers; i++) {
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        pthread_t p;
        treadsOfDrivers.push_back(p);
        int socketDescriptorClient = myTcp->accpetFromClient();
        //here we get the driver from clientDriver
        myTcp->reciveData(buffer, sizeof(buffer), socketDescriptorClient);
        //for de-serializa we need put buffer to string.
        string bufferRecivedDr = bufferToString(buffer, sizeof(buffer));
        //de serialize
        boost::iostreams::basic_array_source<char> device(bufferRecivedDr.c_str(),
                                                          bufferRecivedDr.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        ia >> driver;
        // add driver to taxi center
        texiCenter->addDriverToDriverLIst(driver);
        //we use socketToDriver for the conection between driver to discriptorckient
        SocketToDriver* socketToDriver = new SocketToDriver (socketDescriptorClient, driver, texiCenter);
        texiCenter->setMySocketToDriverList(socketToDriver);

        // here we open new tread for each driver (client)
        pthread_create(&treadsOfDrivers.at(i), &attr, ConnectionClients:: runClients, socketToDriver);

    }
    //set my driver to the driver we got
    //setMyDriver();
    return texiCenter->getMySocketToDriverList();
}

void GameFlow::sendCab(CabBase* cabBase, int socketDescriptor) {
    // now send the vechile to the client
    //serialize
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << cabBase;
    s.flush();
    //here we sent back the right texi cab
    myTcp->sendData(serial_str, socketDescriptor);
}