//
// Created by ariel on 16/11/16.
//
#include <iostream>
#include "Point.h"

using namespace std;

Point::Point(int newX, int newY) {
    x = newX;
    y = newY;
}

void Point::SetX(int xs)
{
    x = xs;
}

void Point::SetY(int ys)
{
    y = ys;
}

int Point::GetX() {
    return x;
}

int Point::GetY() {
    return y;
}


bool Point::operator==(Point &otherPoint) {
    if((x == otherPoint.GetX()) && (y == otherPoint.GetY())) {
        return true;
    }
    return false;
}

ostream &operator<<(ostream& output, const Point& p) {
    output<<"("<<p.x<<","<<p.y<<")";
    return output;
}

Point::Point() {}
