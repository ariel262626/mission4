//
// Created by dvir on 21/11/16.
//

#include <iostream>
#include <vector>
#include "Matrix2d.h"
#include "Node.h"
#include "Grid.h"

using namespace std;

Matrix2d::Matrix2d(int high, int width, vector<Point> obstaclePoint): myObstaclePoint(obstaclePoint){
    myHigh = high;
    myWidth = width;
    myObstaclePoint = obstaclePoint;
    //build a matrix in maximum size. if the real size is smaller-> we won't
    // refer to the rest of the nodes.
    for (int i = 9; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
            Point p = Point(j, i);
            Node n = Node(p, false);
            matrix[j][i] = n;
        }
    }
    // run of all the obstacle list and find their posion in the matrix, after that,
    // set each boolean 'isObstacle' to true, because we need to know where we mustn't
    // pass.
    if (!getObstaclesList().empty()){
    for (int i = 0; i<getObstaclesList().size(); i++){
        if (matrix[getObstaclesList().at(i).GetX()][getObstaclesList().at(i).GetY()].getPointOfnode() ==
                getObstaclesList().at(i)){
            matrix[getObstaclesList().at(i).GetX()][getObstaclesList().at(i).GetY()].setIsObstacle();
        }
    }
    }
}


Matrix2d::~Matrix2d() {}
void Matrix2d::printReal(vector<Node*> traj1){
    // run the all vector from the end to begin end print. that's the way of the driver
    // in the grid acording to the bfs algorithm
     for (int i = traj1.size()-1; i >= 0; i--){
         cout << traj1.at(i)->getPointOfnode()<< endl;
     }
 }

 vector<Node*> Matrix2d::getNiebours(Node currentNode){
     //the vector of neighbours.
    vector<Node*> array_Niebours;
     //9
     // check if we has neibours in left of 'currentNode'
     if ((currentNode.getPointOfnode().GetX()-1>=0)&&
             !(matrix[currentNode.getPointOfnode().GetX()-1][currentNode.getPointOfnode().GetY()]).getIsObstacle()){
         // insert this node  to the vector as neibour
         Node* node1 = &matrix[currentNode.getPointOfnode().GetX() - 1]
         [currentNode.getPointOfnode().GetY()];
         array_Niebours.push_back(node1);
     } else {
         //if this side is illegal-> we will refer to this point as (-1,-1)
         Node* n1 = new Node(Point(-1,-1), false);
         array_Niebours.push_back(n1);
     }

     //12
     // check if we has neibours in up of 'currentNode'
     if ((currentNode.getPointOfnode().GetY() + 1 < myHigh)&&
     !(matrix[currentNode.getPointOfnode().GetX()][currentNode.getPointOfnode().GetY() + 1]).getIsObstacle()){
         // insert this node  to the vector as neibour
         Node* node2 = &matrix[currentNode.getPointOfnode().GetX()]
         [currentNode.getPointOfnode().GetY() + 1];
         array_Niebours.push_back(node2);
     } else {
         //if this side is illegal-> we will refer to this point as (-1,-1)
         Node* n2 = new Node(Point(-1,-1), false);
         array_Niebours.push_back(n2);
     }

     //3
     // check if we has neibours in right of 'currentNode'
     if ((currentNode.getPointOfnode().GetX() + 1< myWidth)&&
     !(matrix[currentNode.getPointOfnode().GetX() + 1][currentNode.getPointOfnode().GetY()]).getIsObstacle()){
         // insert this node  to the vector as neibour
         Node* node3 = &matrix[currentNode.getPointOfnode().GetX() + 1]
         [currentNode.getPointOfnode().GetY()];
         array_Niebours.push_back(node3);
     } else {
         //if this side is illegal-> we will refer to this point as (-1,-1)
         Node* n3 = new Node(Point(-1,-1), false);
         array_Niebours.push_back(n3);
     }

     //6
     // check if we has neibours in down of 'currentNode'
     if ((currentNode.getPointOfnode().GetY() -1>= 0)&&
     !(matrix[currentNode.getPointOfnode().GetX()][currentNode.getPointOfnode().GetY() - 1]).getIsObstacle()){
         // insert this node  to the vector as neibour
        Node* node4 = &matrix[currentNode.getPointOfnode().GetX()]
        [currentNode.getPointOfnode().GetY() - 1];
         array_Niebours.push_back(node4);
     } else{
         //if this side is illegal-> we will refer to this point as (-1,-1)
         Node* n4 = new Node(Point(-1,-1), false);
         array_Niebours.push_back(n4);
     }
     // after we insert the all neibours, return the vector to bfs algrorithm
    return array_Niebours;
     }

    void Matrix2d::setNodeInMatrix(Node *n) {
      // set node in the matrix -> change the matrix
      matrix[n->getPointOfnode().GetX()][n->getPointOfnode().GetY()] = *n;
    }

int Matrix2d::getHigh() {
    return myHigh;
}

int Matrix2d::getWidth() {
    return myWidth;
}

void Matrix2d::setHigh(int high) {
    myHigh = high;
}

void Matrix2d::setWidth(int width) {
    myWidth = width;
}

void Matrix2d::setobstaclePoint(vector<Point> obstacleList) {
    myObstaclePoint.swap(obstacleList);
}

vector<Point> Matrix2d::getObstaclesList() {
    return myObstaclePoint;
}


