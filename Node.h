//
// Created by dvir on 19/11/16.
//

#ifndef MISSION1_NODE_H
#define MISSION1_NODE_H
#include "Point.h"
#include <iostream>

/*class of node- node build from current point and pointer to the father
 * and boolean falg.
 */
class Node {

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & currentPoint;
        ar & myFather;
        ar & flag;
        ar & isObstacle;
    }
private:
    Point currentPoint;
    // we need to know about every point who is call her, in order to we could
    // after that know the right trajectory of bfs
    Node* myFather;
    // to know if we already passed the node in the matrix
    bool flag;
    // to know if we could pass intro this points. maybe it's obstacle
    bool isObstacle;

public:
    //constrcturs
    Node(Point myNode, bool myFlag);
    Node();
    //deconstrctur
    ~Node(){};
/**
 * @return boolean, to know if this node is obstacle in the grid
 */
    bool getIsObstacle();

    /**
     * set boolean element, to determine if this node is obstacle
     */
    void setIsObstacle();

    /*
     * every node has a boolean member that told us if we visited at his place.
     */
    void setFlag();

    /*
     * get the point of the current node.
     */
    Point getPointOfnode();

    /*
     * set node with this point
     */
    void setNode(Point newNode);

    /*
     * set father of the current node-pointer to the node of the father.
     */
    void setFather(Node *father);

    /*
     * get the father of the current node.
     */
    Node* getNodeFather();

    /*
     * get the boolean flag of the current node.
     */
    bool getFlag();

    /*
     * overloading operator of == for nodes.
     */
    bool operator==(Node &otherNode);
};

#endif //MISSION1_NODE_H