#include <iostream>
#include "Point.h"
#include "Node.h"
#include "Grid.h"
#include "Bfs.h"
#include "Matrix2d.h"
#include "Driver.h"
#include "TexiCenter.h"
#include "PharserInfo.h"

using namespace std;

int main(int argc, char** argv) {
    // here we will put the all information
    TexiCenter texiCenter;
    int choose;
    int countDriver = 0;
    int countCabs = 0;
    string stringGrid, stringchoose, stringObst;
    vector <Point> listObstacle;

    //find high and width -> use in class of pharser for translate the data
    getline(cin, stringGrid);
    PharserInfo pharseGrid = PharserInfo(stringGrid);
    //create map
    Matrix2d* newMap = pharseGrid.createGrid();
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
    while(true) {
        cin >> stringchoose;
        // choose mission to peform
        choose = stoi(stringchoose);
        switch (choose) {
            // insert new driver to the game
            case 1: {
                string insertdriver;
                cin >> insertdriver;
                // send the string of user to class of parser
                PharserInfo pharser = PharserInfo(insertdriver);
                // we will get now new driver
                Driver *driver = pharser.createDriver();
                // count how much drivers we have
                countDriver++;
                // add driver to taxi center
                texiCenter.addDriverToDriverLIst(driver);
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
                for(int i = 0; i < countDriver; i++) {
                    delete texiCenter.getDriverInIndex(i);
                }
                for(int i = 0; i < countCabs; i++) {
                    delete texiCenter.getCabInIndex(i);
                }
                // end the program
                return 0;
            }
        }
    }
}
