//
// Created by yanaiela on 12/10/16.
//

#include "Udp.h"
#include "Driver.h"
#include "PharserInfo.h"
#include <unistd.h>
//#include <boost>

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


std::string bufferToString(char* buffer, int bufflen)
{
    std::string ret(buffer, bufflen);

    return ret;
}

int main(int argc, char *argv[]) {
    std::cout << "Hello, from client" << std::endl;
    //argv[1] = the port of the server
    Socket* udp = new Udp(0, 5555);
    //bind the server if fail do fail
    int t = udp->initialize();
    cout<<"in client initialize"<<endl;
    cout<<t<<endl;
    //for serialization create buffer
    char buffer[1024];

    // get data of driver from the user
    string insertdriver;
    cin >> insertdriver;
    // send the string of user to class of parser
    PharserInfo pharser = PharserInfo(insertdriver);
    // we will get now new driver
    Driver *driver = pharser.createDriver();


    //serialize
    string serial_str;
    boost::iostreams::back_insert_device<string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();

    /*server wait to get this data (we need to send here driver) than the server give  the driver the rifght
     * texi and returns this texi*/
    //send the driver to server
    udp->sendData(serial_str);

    //here the client get the texi fron the server
    udp->reciveData(buffer, sizeof(buffer));
    //for de-serializa we need put buffer to string
    string bufferRecivedTexi = bufferToString(buffer, sizeof(buffer));
    //make instence of cab
    CabBase* cabBase;
    //de serialize
    boost::iostreams::basic_array_source<char> device(bufferRecivedTexi.c_str(), bufferRecivedTexi.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> cabBase;
    cout<<"cabebase recived:"<<endl;
    cout<<cabBase->getCabId()<<endl;

    cout<<"wait for trip"<<endl;

    //client get the trip from the server
    udp->reciveData(buffer, sizeof(buffer));
    //for de-serializa we need put buffer to string
    string bufferRecivedTrip = buffer;
    //make instence of cab
    Trip* trip;
    //de serialize
    boost::iostreams::basic_array_source<char> device1((char *) bufferRecivedTrip.c_str(),
                                                       (char *) bufferRecivedTrip.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device1);
    boost::archive::binary_iarchive ia1(s3);
    ia1 >> trip;

    //here the client get the 'go' word from the server and move one step
    udp->reciveData(buffer, sizeof(buffer));
    //for de-serializa we need put buffer to string
    string bufferRecivedAdvance = buffer;
    //make instence of cab
    Point newLocation;
    //de serialize
    boost::iostreams::basic_array_source<char> device2((char *) bufferRecivedAdvance.c_str(),
                                                       (char *) bufferRecivedAdvance.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device2);
    boost::archive::binary_iarchive ia2(s3);
    ia2 >> newLocation;
    driver->setLocation(newLocation);
    // close socket
    udp->~Socket();
    return 0;
}