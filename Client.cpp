//
// Created by dvir on 12/10/16.
//
#include <boost/serialization/vector.hpp>
#include "Udp.h"
#include "Driver.h"
#include "PharserInfo.h"
#include "Tcp.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
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

string bufferrToString(char* buffer, int bufflen)
{
    std::string ret(buffer, bufflen);
    return ret;
}

int main(int argc, char *argv[]) {
    //argv[2] = the port of the server
    Socket* tcp = new Tcp(0, stoi(argv[2]));
    //bind the server if fail do fail argv[1] = ip
    tcp->setIp(argv[1]);
    int socketServer = tcp->initialize();
    //for serialization create buffer
    char buffer[1024];

    // get data of driver from the user
    string insertdriver;
    cin >> insertdriver;
    // send the string of user to class of parser
    PharserInfo pharser = PharserInfo(insertdriver);
    // we will get now new driver
    Driver *driver = pharser.createDriver();


    //serialize the driver for send it to server
    string serial_str;
    boost::iostreams::back_insert_device<string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();

    /*server wait to get this data (we need to send here driver) than the server give  the driver the rifght
     * texi and returns this texi*/
    //send the driver to server
    tcp->sendData(serial_str, socketServer);
    //here the client get the texi fron the server
    tcp->reciveData(buffer, sizeof(buffer), socketServer);

    //for de-serializa we need put buffer to string
    string bufferRecivedTexi = bufferrToString(buffer, sizeof(buffer));
    //make instance of cab
    CabBase* cabBase;
    //de serialize
    boost::iostreams::basic_array_source<char> device(bufferRecivedTexi.c_str(),
                                                      bufferRecivedTexi.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> cabBase;
    int integerSend1 = -1;
    int integerSend2 = -1;
    int integerSend3 = -1;
    //serialize the int of '-1' for the flow
    string serial_str1;
    boost::iostreams::back_insert_device<string> inserter1(serial_str1);
    boost::iostreams::stream<boost::iostreams::back_insert_device<string> > s5(inserter1);
    boost::archive::binary_oarchive oa1(s5);
    oa1 << integerSend3;
    s5.flush();
    tcp->sendData(serial_str1, socketServer);

//get trip end the trip and wait for the next trip if there is one
while(true) {



    //client get the trip from the server
    tcp->reciveData(buffer, sizeof(buffer), socketServer);
    //for de-serializa we need put buffer to string
    string bufferRecivedTrip = bufferrToString(buffer, sizeof(buffer));

    //make instance of cab
    Trip *trip;
    //de serialize
    boost::iostreams::basic_array_source<char> device1(bufferRecivedTrip.c_str(),
                                                       bufferRecivedTrip.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device1);
    boost::archive::binary_iarchive ia1(s3);
    ia1 >> trip;

    //if we get "-1" instead of trip shutdown the socket and return
    if (trip != NULL) {
        if (trip->getRideId() == -1) {
            // close socket and delete all the allocate memory
            delete cabBase;
            delete driver;
            delete trip;
            delete tcp;
            return 0;
        }
    }
    // update the trip to driver for each time we get new trip (we get the new trip
    // only in case the driver finish the last trip)
    driver->setTrip(trip);
    if (driver->getMyTrip()->getRideId() == -1){
        return 0;
    }

    //serialize the int of '-1' for the flow
    string serial_str2;
    boost::iostreams::back_insert_device<string> inserter(serial_str2);
    boost::iostreams::stream<boost::iostreams::back_insert_device<string> > s10(inserter);
    boost::archive::binary_oarchive oa(s10);
    oa << integerSend1;
    s10.flush();
    tcp->sendData(serial_str2, socketServer);
    if (trip != NULL) {
//move one step and wait for the next move one step until you end the trip
        while (true) {
            //here the client get the 'go' word from the server and move one step
            tcp->reciveData(buffer, sizeof(buffer), socketServer);
            //for de-serializa we need put buffer to string
            string bufferRecivedAdvance = bufferrToString(buffer, sizeof(buffer));
            //make instance of cab
            Point newLocation;
            //de serialize
            boost::iostreams::basic_array_source<char> device2(bufferRecivedAdvance.c_str(),
                                                               bufferRecivedAdvance.size());
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device2);
            boost::archive::binary_iarchive ia2(s4);
            ia2 >> newLocation;
            Point closePoint = Point(-1, -1);
            //cout << newLocation << endl;
            if (newLocation == closePoint) {
                // close socket and delete all the allocate memory
                delete cabBase;
                delete driver;
                delete trip;
                delete tcp;
                return 0;
            }
            //update the new location to the driver position
            driver->setLocation(newLocation);
            if (driver->getLocation().GetX() == -1){
                return 0;
            }

            string serial_str2;
            boost::iostreams::back_insert_device<string> inserter(serial_str2);
            boost::iostreams::stream<boost::iostreams::back_insert_device<string> > s6(inserter);
            boost::archive::binary_oarchive oa(s6);
            oa << integerSend2;
            s6.flush();
            tcp->sendData(serial_str2, socketServer);

            //we end the trip so we get back to while to wait for the next trip
            Point p1 = driver->getMyTrip()->getEndPointOfTrip();
            Point p2 = driver->getLocation();
            if (p1 == p2) {
                delete trip;
                // back to get new trip or finish the program
                break;
            }
        }
    }
}
}