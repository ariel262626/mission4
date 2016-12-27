
#include <iostream>
#include <unistd.h>
#include "Udp.h"
#include <iostream>
//##include <boost>
#include "Point.h"
#include "Node.h"
#include "Grid.h"
#include "Bfs.h"
#include "Matrix2d.h"
#include "Driver.h"
#include "TexiCenter.h"
#include "PharserInfo.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
using namespace std;
using namespace boost::archive;
std::stringstream ss;


int main(int argc, char *argv[]) {
    std::cout << "Hello, from server" << std::endl;

    Socket *udp = new Udp(1, 1226);
    udp->initialize();

    char buffer[1024];

//לעשות close בסוף


    // support more than one client?

    // here we will put the all information
    TexiCenter texiCenter;
    int choose;
    int countDriver = 0;
    int countCabs = 0;
    int numberOfDrivers = 1;
    string stringGrid, stringchoose, stringObst;
    vector<Point> listObstacle;

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
    // request from the user mission to enter. we will expect all the time to another mission,
    // therefor we return on it until the user enter 7 (end of mission).
    while (true) {
        cin >> stringchoose;
        // choose mission to peform
        choose = stoi(stringchoose);
        switch (choose) {
            // insert new driver to the game
            case 1: {
                //get from user how much drivers we need to get
                cin >> numberOfDrivers;

                //here we get the driver from clientDriver
                udp->reciveData(buffer, sizeof(buffer));
                //need serialize
                //for de-serializa we need put buffer to string
                string bufferRecivedDr = buffer;
                //make instence of cab
                Driver* driver2;
                //de serialize
                boost::iostreams::basic_array_source<char> device(bufferRecivedDr.c_str(), bufferRecivedDr.size());
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
                boost::archive::binary_iarchive ia(s2);
                ia >> driver2;

                string insertdriver;
                cin >> insertdriver;
                // send the string of user to class of parser
                PharserInfo pharser = PharserInfo(insertdriver);
                // we will get now new driver
                Driver *driver = pharser.createDriver();
                int driverId = driver->getId();
                // add driver to taxi center
                texiCenter.addDriverToDriverLIst(driver);
                // count how much drivers we have
                countDriver++;


                //find the right texi
                int i = texiCenter.getDriverInIndex(0)->getMyCabId();
                CabBase cabBase = *texiCenter.getCabWithId(i);

                //for serialization create buffer
                char buffer[1024];

                //serialize
                CabBase* cabBase1 = &cabBase;
                std::string serial_str;
                boost::iostreams::back_insert_device<std::string> inserter(serial_str);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
                boost::archive::binary_oarchive oa(s);
                oa << cabBase1;
                s.flush();

                //here we sent back the right texi cab
                udp->sendData(serial_str);

                //sent back the right trip
                Driver driver1 = *(texiCenter.getDriverWithId(driverId));
                Trip trip = driver1.getMyTrip();
                //serialize
                Trip* trip1 = &trip;
                std::string serial_str1;
                boost::iostreams::back_insert_device<std::string> inserter1(serial_str1);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s1(inserter1);
                boost::archive::binary_oarchive oa1(s1);
                oa1 << trip1;
                s.flush();

                //here we sent back the right texi cab
                udp->sendData(serial_str1);

                break;
            }
            case 2: {
                // get new ride from the user
                string insertRide;
                cin >> insertRide;
                // use in the pharser class to handle the data
                PharserInfo pharser = PharserInfo(insertRide);
                Trip trip = pharser.createNewRide();
                // add trip to taxi center
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
                // find location of the driver in the grid
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

            }
            case 9: {

                //here we sent back the 'go' for move one step
                udp->sendData("advance");
            }
        }
        // end the program
        return 0;
    }
}