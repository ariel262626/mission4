//
// Created by ariel on 29/11/16.
//

#include "InfoTaxi.h"
#include "TexiCenter.h"

InfoTaxi::InfoTaxi(vector<Driver> driversList, vector<Passenger> passengresList,
                   vector<StandartCab> standartCabList, Grid* map) :
        driversList(driversList),passengresList(passengresList),standartCabList(standartCabList){
    myMap = map;
}

TexiCenter InfoTaxi::getinfo() {
}
