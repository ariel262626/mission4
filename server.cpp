
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

int main(int argc, char *argv[]) {
    cout << "Hello, from server" << endl;
    // create connection between the server and client
    Socket *udp = new Udp(1, stoi(argv[1]));
    udp->initialize();
    char buffer[1024];

    // here we will put the all information
    TexiCenter texiCenter;
    int choose;
    int countDriver = 0;
    int countCabs = 0;
    int numberOfDrivers = 1;
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
    texiCenter.setMap(*newMap);
    // create clock for the program
    ClockTime clock;
    // request from the user mission to enter. we will expect all the time to another mission,
    // therefor we return on it until the user enter 7 (end of mission).
    while (true) {
        // choose mission to peform
        cin >> choose;
        switch (choose) {
            case 1: {
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
                // send the string of user to class of parser
                // we will get now new driver
                int driverId = driver->getId();
                // add driver to taxi center
                texiCenter.addDriverToDriverLIst(driver);
                // count how much drivers we have
                countDriver++;

                //find the right taxi for connect the cab to the driver
                int cabId = texiCenter.getDriverInIndex(0)->getMyCabId();
                CabBase* cabBase = texiCenter.getCabWithId(cabId);
                texiCenter.getDriverWithId(0)->setCab(*cabBase);

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
                break;
            }
            case 2: {
                // get new ride from the user
                string insertRide;
                cin >> insertRide;
                // use in the pharser class to handle the data
                PharserInfo pharser = PharserInfo(insertRide);
                Trip* trip = pharser.createNewRide();
                // add trip to taxi center - we need to sort the trip list according the time
                texiCenter.addTripToTripLIst(trip);
                break;
            }
            case 3: {
                // get new cab from the user
                string insertVehicle;
                cin >> insertVehicle;
                // use in the pharser class to handle the data
                PharserInfo pharser = PharserInfo(insertVehicle);
                CabBase *vehicle = pharser.createVehicle();
                //count how much cabs we have
                countCabs++;
                // add cab to taxi center
                texiCenter.addCabToCabsLIst(vehicle);
                break;
            }
            case 4: {
                //insert id of driver
                int idMission4;
                Point location;
                cin >> idMission4;
                // find location of the driver in the grid and print it
                location = texiCenter.findLocationOfDriver(idMission4);
                cout << location << endl;
                break;
            }
            case 6: {
                // start driving of all the drivers with their passengers
                texiCenter.startDriving();
                break;
            }
            case 7: {
                // delete the all new allocation memory
                delete newMap;
                for (int i = 0; i < countDriver; i++) {
                    delete texiCenter.getDriverInIndex(i);
                }
                for (int i = 0; i < countCabs; i++) {
                    delete texiCenter.getCabInIndex(i);
                }
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
                delete udp;
                return 0;
            }
            case 9: {
                // for case we we have advance without trip
                if(texiCenter.getMyTripList().empty()) {
                    // update the clock
                    clock.setTime();
                    break;
                }
                // get the first trip from the list. if we will finish the trip, we will erase it from the list
                Trip* trip= texiCenter.getTripInIndex(0);
                // update the trip to driver and send the trip to client only once, when the time is comming.
                // if the time isn't comming-> just update the clock
                if (clock.getTime() == trip->getTime()) {
                    driver->setTrip(*trip);
                    // check if the location of the driver in the same point as start of the trip.
                    // if yes-> we in new trip and therefor send it to client
                    Point startOfTrip = trip->getStartPointOfTrip();
                    Point driverLocation = driver->getLocation();
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
                //we use clone for not delete the path
                // update the clock for each movement
                // make advance only in case the time at least such us the time of the trip
                if(trip->getTime() <= clock.getTime()) {
                    vector<Node> path;
                    Point newPosition;
                    path = trip->getPathOfTripClone(*newMap);
                    // move on or two steps on the grid
                    driver->moveStep(path, clock.getTime());
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
                        // check //
                        Trip *temp = texiCenter.getTripInIndex(0);
                        texiCenter.eraseTripInIndex();
                        delete temp;
                    }
                }
            clock.setTime();
            }
        }
    }
}