//
// Created by dvir on 21/11/16.
//

#ifndef UNTITLED_MATRIX2D_H
#define UNTITLED_MATRIX2D_H

#include <boost/serialization/access.hpp>
#include "Grid.h"
#include <iostream>

/*
 * class of 2D matrix- build the specific matrix of 2d and heiress from grid
 * we always keep her update.
 */
class Matrix2d : public Grid {

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & myWidth;
        ar & myHigh;
        ar & myObstaclePoint;

    }
private:
    int myWidth;
    int myHigh;
    vector<Point> myObstaclePoint;
public:
    Node matrix[1000][1000];

    //constracturs.
    Matrix2d(int high, int width, vector<Point> obstaclePoint);
    Matrix2d(){};
    ~Matrix2d();

    /**
     * get the trajectory and print the path according bfs. iterate it from the end
     * until to the start.
     * @param traj1: vector of trajectory bfs
     */
    void printReal(vector<Node*> traj1);

/**
 * this method get one node and find her neibours.  push them into
 * the vetor and return the vector
 * @param currentNode: get node
 * @return vector of his neibours
 */
    vector<Node*> getNiebours(Node currentNode);

    /**
     * after the changes, the matrix should be updated.
     * so we get the node and update his place in the matrix.
     * @param n: pointer to node
     */
    void setNodeInMatrix(Node *n);

    /**
     * @return vector of obstacle list
     */
    vector<Point> getObstaclesList();
/**
 * @return the high of the grid
 */
    int getHigh();

    /**
     * @return the width of the grid
     */
    int getWidth();

    /**
     *
     * @param high: set the high of the grid
     */
    void setHigh(int high);

    /**
     * @param width: set width of the grid
     */
    void setWidth(int width);

    /**
     * @param obstacleList: set the obstacle list in the grid
     */
    void setobstaclePoint(vector<Point> obstacleList);
};
#endif //UNTITLED_MATRIX2D_H
