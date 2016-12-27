//
// Created by ariel on 16/11/16.
//

#ifndef MISSION1_POINT_H
#define MISSION1_POINT_H
#include <iostream>
#include <boost/serialization/access.hpp>

/*
 * class of point-build from 2 integer and have method get and set
 * and overloading for == and print this object.
 */
class Point {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & x;
        ar & y;
    }
private:
    int x, y;

public:
    //constractur
    Point(int newX, int newY);

    Point();

    //deconstractur
    ~Point(){};
    //methods
    /**
     * get x
     * @return  this x
     */
    int GetX();

    /**
     * get y
     * @return this y
     */
    int GetY();

    /**
     * set x
     * @param x - to set
     */
    void SetX(int x);

    /**
     * set y
     * @param Y - to set
     */
    void SetY(int Y);

    /*
     * overloading for == of points
     */
    bool operator==(Point &otherPoint);

    /*
     * overloading for print of point.
     */
    friend std::ostream &operator<<(std::ostream& output, const Point& p);
};

#endif //MISSION1_POINT_H
