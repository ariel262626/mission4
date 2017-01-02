//
// Created by dvir test for github
//

#ifndef UNTITLED_BFC_H
#define UNTITLED_BFC_H

#include "Grid.h"
#include <queue>
#include <stack>
using namespace std;

/*
 * class of bfs algorithm - will get the end point and will manage the algorithm
 * with queue and stack.
 * get the neighbours of node if legal set his father and rise his flag
 * and push to the queue and stack, if the last we pushed is what we looking for
 * go to print method.
 */
class Bfs {
private:
    Node myStart;
    Node myEnd;
    int numOfNeibours;
    Grid* myMatrix;

public:
    //constructor
    Bfs(Node start, Node end, int dimention, Grid *matrix);
    Bfs();
    //deconstructor
    ~Bfs(){};

    /*
     * call to manage queue with the next node until we get the point we need(end point)
     *
     * than call to print method.
     */
    vector<Node*> runBfs(Node* myStarts, Node* myEndS);
    /*
     * get the neighbours of node and check who is legal,  set the current node as his father
     * and change his flag from false to true, and at the end push him at the queue and stack
     */
    void manageQueue(queue<Node*> &queue1, stack<Node*> &stack1, Node *currentNode);
};
#endif //UNTITLED_BFC_H
