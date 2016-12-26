//
// Created by ariel on 29/11/16.
//
#include <iostream>
#include <vector>
#include "Driver.h"
#include "Passenger.h"
#include "TexiCenter.h"

#ifndef MISSION2_INFOTAXI_H
#define MISSION2_INFOTAXI_H


class InfoTaxi {
private:
    vector<Driver> driversList;
    vector<Passenger> passengresList;
    vector<StandartCab> standartCabList;
    Grid* myMap;
public:
    //constructor
    InfoTaxi(vector<Driver> driversList, vector<Passenger> passengresList,
             vector<StandartCab> standartCabList, Grid* map);

    TexiCenter getinfo();
};


#endif //MISSION2_INFOTAXI_H
