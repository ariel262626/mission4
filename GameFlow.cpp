//
// Created by ariel on 30/11/16.
//

#include <vector>
#include "GameFlow.h"
#include "PharserInfo.h"
#include "Tcp.h"
#include "ConnectionClients.h"
#include "SocketToDriver.h"
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

GameFlow:: GameFlow (Socket* tcp){
    myTcp = tcp;
}

GameFlow::GameFlow() {}

 void GameFlow:: run() {

    // here we will put the all information
    extern int choose;
    //int countDriver = 0;
    //int countCabs = 0;
    string stringGrid, stringObst;
    vector<Point> listObstacle;
    Driver *driver;
     ConnectionClients connectionClients = ConnectionClients ();

    //find high and width -> use in class of pharser for translate the data
    getline(cin, stringGrid);
    PharserInfo pharseGrid = PharserInfo(stringGrid);
    //create map
    Matrix2d *newMap = pharseGrid.createGrid();
    // insert obstacle points
    cin >> stringObst;
    // insert obstacles,if the number is big from zero, the function request from the user
    // to insert the obstacle points.
    PharserInfo pharseObstacles = PharserInfo(stringObst);
    listObstacle = pharseObstacles.obstaclePoints();
    // insert the list of obstacles to the map (grid)
    newMap->setobstaclePoint(listObstacle);
    // insert the map to taxi center, because the taxi center is in charge of all the programm actualy
    texiCenter.setMap(newMap);
    // request from the user mission to enter. we will expect all the time to another mission,
    // therefor we return on it until the user enter 7 (end of mission).
    while (true) {
        // choose mission to perform
        cin >> choose;
        switch (choose) {
            case 1: {
                driver = getDriverFromClient();
                texiCenter.setCabToDriver(driver);
                CabBase* cabBase = driver->getCab();
                sendCab(cabBase);
                break;
            }
            case 2: {
                getNewRide();
                break;
            }
            case 3: {
                getNewCab();
                //setMyCabBase();
                //count how much cabs we have
                //countCabs++;
                break;
            }
            case 4: {
                printCurrentLocation();
                break;
            }
            case 7: {
                // the allocate memory which placed in taxi center will be deleted when the program finish.
                // now, call function that send special trip to shut down the program
                tripToCloseClient();
                delete myTcp;
                return;
            }
            case 9: {

            }
        }
    }
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

CabBase* GameFlow::getMyCabBase() {
    return myCabBase;
}


Trip* GameFlow::getCurrentTrip() {
    return texiCenter.getTripInIndex(0);
}


void GameFlow::setMyDriver() {
    myDriver = texiCenter.getDriverInIndex(0);
}

//neddddddddd ????????????????????????????????????????????????????????????????????????????????
/*void GameFlow::setMyCabBase()  {
    myCabBase = texiCenter.getCabInIndex(0);
}*/

Driver* GameFlow::getMyDriver() {
    return texiCenter.getDriverInIndex(0);
}

void GameFlow::tripToCloseClient() {
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
     myTcp->sendData(serial_str1);
    // delete tripClose
    delete tripClose;
}




void GameFlow::getNewCab() {
    // get new cab from the user
    string insertVehicle;
    cin >> insertVehicle;
    // use in the pharser class to handle the data
    PharserInfo pharser = PharserInfo(insertVehicle);
    CabBase* vehicle = pharser.createVehicle();
    // add cab to taxi center
    texiCenter.addCabToCabsLIst(vehicle);
}

void GameFlow::getNewRide() {
    // get new ride from the user
    string insertRide;
    cin >> insertRide;
    // use in the pharser class to handle the data
    PharserInfo pharser = PharserInfo(insertRide);
    Trip* trip = pharser.createNewRide();
    // add trip to taxi center - we need to sort the trip list according the time
    texiCenter.addTripToTripLIst(trip);
}

Driver* GameFlow::getDriverFromClient() {

    Driver *driver;
    char buffer[1024];
    int numberOfDrivers;
    //get from user how much drivers we need to get
    cin >> numberOfDrivers;
    int const amountsTreadsofClients = numberOfDrivers;
    pthread_t treadsOfDrivers[amountsTreadsofClients];
    int socketDescriptor = myTcp->initialize(numberOfDrivers);
    for (int i = 0; i < numberOfDrivers; i++) {
        int socketDescriptorClient = myTcp->accpetFromClient();
        //here we get the driver from clientDriver
        myTcp->reciveData(buffer, sizeof(buffer));
        //for de-serializa we need put buffer to string
        string bufferRecivedDr = bufferToString(buffer, sizeof(buffer));
        //de serialize
        boost::iostreams::basic_array_source<char> device(bufferRecivedDr.c_str(),
                                                          bufferRecivedDr.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        ia >> driver;
        // add driver to taxi center
        texiCenter.addDriverToDriverLIst(driver);
        //we use socketToDriver for the conection between driver to discriptorckient
        SocketToDriver* socketToDriver = new SocketToDriver (socketDescriptorClient, driver, &texiCenter);
        texiCenter.setMySocketToDriverList(socketToDriver);

        // here we open new tread for each driver (client)

        pthread_create(&treadsOfDrivers[i],NULL,ConnectionClients:: runClients,socketToDriver);

    }
    //set my driver to the driver we got
    setMyDriver();
    return driver;
}

void GameFlow::sendCab(CabBase* cabBase) {
    // now send the vechile to the client
    //serialize
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << cabBase;
    s.flush();
    //here we sent back the right texi cab
    myTcp->sendData(serial_str);
}

void GameFlow::printCurrentLocation() {
    //insert id of driver
    int DriverId;
    Point location;
    cin >> DriverId;
    // find location of the driver in the grid and print it
    location = texiCenter.findLocationOfDriver(DriverId);
    cout << location << endl;
}


