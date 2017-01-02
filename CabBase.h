//
// Created by dvir on 12/12/16.
//

#ifndef MISSION2_CABBASE_H
#define MISSION2_CABBASE_H

#include <boost/serialization/access.hpp>
#include "Passenger.h"
#include "Grid.h"

class CabBase {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & myId;
        ar & myType;
        ar & myManaufactur;
        ar & myColor;
        ar & myTariff;
        ar & myMap;
        ar & myPassenger;
        ar & myKilometers;
    }
protected:
    int myId;
    int myType;
    char myManaufactur;
    char myColor;
    double myTariff;
    Grid* myMap;
    Passenger* myPassenger;
    int myKilometers;
public:
    //constructor
    CabBase(int id, int type, char manaufactur, char color, Grid* map,
            Passenger* passenger);
     CabBase();
    ~CabBase(){};

    ~CabBase();

    /**
     * get the cab id
     * @return id
     */
     int getCabId();

    /**
     * get how much kilometers the cab has passed
     * @return - kilometers
     */
     int getKilometersOfCab();

    /**
     * update the kilometers
     * @param x - according to x
     */
     void updateKilometers(int x);

    /**
     * get tarrif of the cab
     * @return - tarrif
     */
     double getTarrif();

    /**
     * set tarrif
     * @param d - the new tarrif
     */
    void setTarrif(double d);

    /**
     * if the cab luxury return 2 else return 1
     * @return 2 or 1
     */
    int amILuxury();

    /**
     * get the map(ways-gps) of the cab
     * @return Grid*
     */
    Grid* getMap();
    };

#endif //MISSION2_CABBASE_H
