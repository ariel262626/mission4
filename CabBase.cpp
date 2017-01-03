//
// Created by dvir on 12/12/16.
//

#include "CabBase.h"

CabBase::CabBase(int id, int type, char manaufactur, char color, Grid* map, Passenger* passenger) {
    myId = id;
    myType = type;
    myKilometers = 0;
    myManaufactur = manaufactur;
    myColor = color;
    myTariff = 0;
    myMap = map;
    myPassenger = passenger;
}

CabBase::CabBase(){}

int CabBase::amILuxury() {
    return myType;
}

int CabBase::getCabId() {
    return myId;
}

int CabBase::getKilometersOfCab() {
    return myKilometers;
}

void CabBase::updateKilometers(int x) {
    myKilometers = x;
}

double CabBase::getTarrif() {
    return myTariff;
}

void CabBase::setTarrif(double d) {
    myTariff = d;
}

Grid* CabBase::getMap() {
    return myMap;
}


