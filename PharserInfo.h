//
// Created by dvir on 13/12/16.
//

#ifndef MISSION2_PHARSERINFO_H
#define MISSION2_PHARSERINFO_H

#include "Driver.h"
#include "Grid.h"
#include "Matrix2d.h"

/**
 * pharse the input to object
 */
class PharserInfo{
private:
    string myInput;
public:
    /**
     * @param input from the user
     * constructor
     */
    PharserInfo (string input);
    /**
     * this method take the input of the user and create new driver according to
     * his input
     * @return pointer to new driver
     */
    Driver* createDriver ();
    /**
     * this method take the input of the user and create new trip according to
     * his input
     * @return new trip
     */
    Trip* createNewRide ();
    /**
     * this method take the input of the user and create new cab according to
     * his input
     * @return vehicle
     */
    CabBase* createVehicle ();
    /**
     * this method take the input of the user and create new vector of obstacle
     * points according to his input
     * @return list of obstacle points
     */
    vector <Point> obstaclePoints ();
    /**
     * this method take the input of the user and create new grid according to
     * his input
     * @return pointer to grid
     */
    Matrix2d* createGrid ();
    /**
     * this method take the input which already from the shape of (int, something),
     * {because we erase the all data we already pharser} and return the integer
     * that place before the comma. then this method also erase the data (include the comma)
     * that we pharse.
     * @return one int
     */
    int getOneElementInt ();
    /**
     * this method take the input which already from the shape of (char, something),
     * {because we erase the all data we already pharser} and return the char
     * that place before the comma. then this method also erase the data (include the comma)
     * that we pharse.
     * @return one char
     */
    char getOneElementchar ();
    /**
     * this method take the input which already from the shape of (double, something),
     * {because we erase the all data we already pharser} and return the double
     * that place before the comma. then this method also erase the data (include the comma)
     * that we pharse.
     * @return one double
     */
    double getOneElementDouble ();
    /**
     * this method erase the comma from the input
     * @param index: the place of the comma in thr input
     */
    void eraseComma (int index);

    vector <Point> getMyListObstacles (int numOfObstaclePoints);

    bool checkIfObstaclesValid();

    bool checkIfObstaclesValid(string point);

    bool checkIfTripValid(string myInput);

    bool checkIfCabBaseValid(string myInput);

    bool checkIfDriverValid(string myInput);

    bool checkStringIfDigit(string myInput);
    };
#endif //MISSION2_PHARSERINFO_H
