//
// Created by dvir on 19/11/16.
//

#include <iostream>
#include "Node.h"
#include <iosfwd>
using  namespace std;

Node::Node(Point myNode, bool myFlag) : currentPoint(0,0)
{
    currentPoint = myNode;
    myFather = NULL;
    flag = myFlag;
    isObstacle = false;
}

Node::Node() : currentPoint(0,0) {}

bool Node::getIsObstacle() {
    return isObstacle;
}

void Node::setIsObstacle() {
    isObstacle = true;
}

void Node::setFlag() {
    flag = !flag;
}

void Node::setFlagToFalse() {
    flag = false;
}

bool Node::getFlag() {
    return flag;
}

Point Node::getPointOfnode() {
    return currentPoint;
}

void Node::setNode(Point newNode) {
    currentPoint = newNode;
}

void Node::setFather(Node *father) {
    myFather = father;
}

Node* Node::getNodeFather(){
    return myFather;
}

bool Node::operator==(Node &otherNode) {
    Point p = otherNode.getPointOfnode();
    if((currentPoint == p) && (flag == otherNode.getFlag())) {
        return true;
    }
    return false;
}