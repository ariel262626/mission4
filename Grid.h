//
// Created by dvir on 20/11/16.
//

#ifndef UNTITLED_GRID_H
#define UNTITLED_GRID_H
#include "Node.h"
#include <iostream>
#include <vector>

using namespace std;

/*
 * abstract class- the matrix will Heiresses from the grid
 * and implements all the methods.
*/
class Grid {
public:
    //constructor
    Grid () {};
    //destructor
    ~Grid () {};
    /**
     * this method print the path of the cab to destention node
     * @param traj1 the path of bfs
     */
    virtual void printReal(vector <Node*> traj1) = 0;
    /**
     * find the valid niebours of current node and return them in vector
     * @param current_node
     * @return vector niebours of current node
     */
    virtual vector<Node*> getNiebours(Node current_node) {};
    /**
     * set node in the matrix
     * @param n pointer to node
     */
    virtual void setNodeInMatrix(Node *n) {};
/**
 * get high of the grid
 * @return high
 */
    virtual int getHigh(){};
    /**
     * get width of the grid
     * @return width
     */
    virtual int getWidth(){};
    /**
     * set high of the grid
     * @param high
     */
    virtual void setHigh(int high){};
    /**
     * set width of the grid
     * @param width
     */
    virtual void setWidth(int width){};
    /**
     * set the obstacle list of the grid
     * @param obstacleList
     */
    virtual void setobstaclePoint(vector<Point> obstacleList){};
    /**
     * get the obstacle list
     * @return vector obstacles
     */
    virtual vector<Point> getObstaclesList(){};

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {}
};
#endif //UNTITLED_GRID_H
