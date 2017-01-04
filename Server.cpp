
#include <iostream>
#include "Udp.h"
#include "Point.h"
#include "Node.h"
#include "Grid.h"
#include "Bfs.h"
#include "Matrix2d.h"
#include "Driver.h"
#include "TexiCenter.h"
#include "PharserInfo.h"
#include "ClockTime.h"
#include "Server.h"
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
using namespace std;

/**
 * this function convert char* to string for the serialize
 * @param buffer
 * @param bufflen: lenth of the buffer
 * @return the string buffer
 */



string bufferToString(char* buffer, int bufflen)
{
    std::string ret(buffer, bufflen);
    return ret;
}

CabBase* Server::getMyCabBase() {
    return myCabBase;
}

void Server::deleteUdp() {
    Matrix2d* mp = texiCenter.getMap();
    delete mp;
    delete udp;
}

Trip* Server::getCurrentTrip() {
    return texiCenter.getTripInIndex(0);
}


void Server::setMyDriver() {
    myDriver = texiCenter.getDriverInIndex(0);
}

void Server::setMyCabBase()  {
    myCabBase = texiCenter.getCabInIndex(0);
}

Driver* Server::getMyDriver() {
    return texiCenter.getDriverInIndex(0);
}

void Server::moveClient() {
    // get the first trip from the list. if we will finish the trip, we will erase it from the list
    Trip* trip = texiCenter.getTripInIndex(0);
    // update the clock for each movement
    // make advance only in case the time at least such us the time of the trip
    if(trip->getTime() <= clockTime.getTime()) {
        vector<Node> path;
        Point newPosition;
        // get the path of the grid. we use clone for not delete the path
        path = trip->getPathOfTripClone(*texiCenter.getMap());
        // move one or two steps on the grid
        myDriver->moveStep(path, clockTime.getTime());
        // get the new location of the driver
        newPosition = texiCenter.getDriverInIndex(0)->getLocation();
        //serialize the point and send to client
        std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << newPosition;
        s.flush();
        //here we sent back the 'go' for move one step
        udp->sendData(serial_str);

        //after we end trip
        if (texiCenter.getTripInIndex(0)->getEndPointOfTrip() == newPosition) {
            // delete trip
            Trip *temp = texiCenter.getTripInIndex(0);
            texiCenter.eraseTripInIndex();
            delete temp;
        }
    }
    // update the time for each insert 9
    clockTime.setTime();
}

bool Server::tripListNotEmpty() {
    if(texiCenter.getMyTripList().empty()) {
        // update the clock
        clockTime.setTime();
        return false;
    }
    return true;
}

void Server::sendTripToClient() {
    Trip* trip = texiCenter.getTripInIndex(0);
    // update the trip to driver and send the trip to client only once, when the time is comming.
    // if the time isn't comming-> just update the clock
    if (clockTime.getTime() == trip->getTime()) {
        myDriver->setTrip(*trip);
        // check if the location of the driver in the same point as start of the trip.
        // if yes-> we in new trip and therefor send it to client
        Point startOfTrip = trip->getStartPointOfTrip();
        Point driverLocation = myDriver->getLocation();
        if (driverLocation == startOfTrip) {
            // make sure we have trip in te list
            if (!texiCenter.getMyTripList().empty()) {
                //send the next trip by serialization
                std::string serial_str1;
                boost::iostreams::back_insert_device<std::string> inserter1(serial_str1);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter1);
                boost::archive::binary_oarchive oa1(s1);
                oa1 << trip;
                s1.flush();
                //here we sent back the right trip
                udp->sendData(serial_str1);
            }
        }
    }
}

Socket* Server::getUdp() {
    return udp;
}

void Server::setUdp(Socket* newUdp) {
    udp = newUdp;
}

void Server::tripToCloseClient() {
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
    udp->sendData(serial_str1);
    // delete allocated memory and close the socket
    delete tripClose;
}

void Server::deleteAllocationMemory() {
    // delete the all new allocation memory
    //delete texiCenter.getMap();
    for (int i = 0; i < 1; i++) {
        Driver* deleteDriver = texiCenter.getDriverInIndex(i);
        delete deleteDriver;
    }
    for (int i = 0; i < texiCenter.getMyCabBaseList().size(); i++) {
        CabBase* deleteCabBase = texiCenter.getCabInIndex(i);
        delete deleteCabBase;
    }
}

void Server::printCurrentLocation() {
    //insert id of driver
    int DriverId;
    Point location;
    cin >> DriverId;
    // find location of the driver in the grid and print it
    location = texiCenter.findLocationOfDriver(DriverId);
    cout << location << endl;
}

void Server::getNewCab() {
    // get new cab from the user
    string insertVehicle;
    cin >> insertVehicle;
    // use in the pharser class to handle the data
    PharserInfo pharser = PharserInfo(insertVehicle);
    CabBase* vehicle = pharser.createVehicle();
    // add cab to taxi center
    texiCenter.addCabToCabsLIst(vehicle);
}

void Server::getNewRide() {
    // get new ride from the user
    string insertRide;
    cin >> insertRide;
    // use in the pharser class to handle the data
    PharserInfo pharser = PharserInfo(insertRide);
    Trip* trip = pharser.createNewRide();
    // add trip to taxi center - we need to sort the trip list according the time
    texiCenter.addTripToTripLIst(trip);
}

void Server::sendCab(CabBase* cabBase) {
    // now send the vechile to the client
    //serialize
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << cabBase;
    s.flush();
    //here we sent back the right texi cab
    udp->sendData(serial_str);
}

void Server::setCabToDriver(Driver* driver) {
    //find the right taxi for connect the cab to the driver
    int cabId = texiCenter.getDriverInIndex(0)->getMyCabId();
    CabBase* cabBase = texiCenter.getCabWithId(cabId);
    texiCenter.getDriverWithId(0)->setCab(cabBase);
}

Driver* Server::getDriverFromClient() {
    Driver *driver;
    char buffer[1024];
    //get from user how much drivers we need to get
    cin >> numberOfDrivers;
    //here we get the driver from clientDriver
    udp->reciveData(buffer, sizeof(buffer));
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
    //set my driver to the driver we got
    setMyDriver();
    return driver;
}

ClockTime Server::getClock() {
    return clockTime;
}

int main(int argc, char *argv[]) {
    cout << "Hello, from server" << endl;
    Server server;
    // create connection between the server and client
    Socket* udp = new Udp(1, stoi(argv[1]));
    server.setUdp(udp);
    server.getUdp()->initialize();


    // here we will put the all information
    //TexiCenter texiCenter;
    int choose;
    int countDriver = 0;
    int countCabs = 0;
    string stringGrid, stringObst;
    vector<Point> listObstacle;
    Driver *driver;

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
    server.texiCenter.setMap(newMap);
    // create clock for the program
    ClockTime clock;
    // request from the user mission to enter. we will expect all the time to another mission,
    // therefor we return on it until the user enter 7 (end of mission).
    while (true) {
        // choose mission to peform
        cin >> choose;
        switch (choose) {
            case 1: {
                driver = server.getDriverFromClient();
                countDriver++;
                server.setCabToDriver(driver);
                CabBase* cabBase = driver->getCab();
                server.sendCab(cabBase);
                break;
            }
            case 2: {
                server.getNewRide();
                break;
            }
            case 3: {
                server.getNewCab();
                server.setMyCabBase();
                //server.getMyCabBase()->setMap(newMap);
                //count how much cabs we have
                countCabs++;
                break;
            }
            case 4: {
                server.printCurrentLocation();
                break;
            }
            case 7: {
                server.deleteAllocationMemory();
                // call function that send special trip to shut down the program
                server.tripToCloseClient();
                server.deleteUdp();
                return 0;
            }
            case 9: {
                // for case we have advance without trip
                if(server.tripListNotEmpty()) {
                    server.sendTripToClient();
                    server.moveClient();
                } else {
                    break;
                }
            }
        }
    }
}