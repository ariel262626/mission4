//
// Created by dvir on 19/11/16.
//

#include "Point.h"
#include "Node.h"
#include "Grid.h"
#include "Bfs.h"

using namespace std;

//constructor
Bfs::Bfs(Node start, Node end, int dimention, Grid *matrix)
{
    myStart = start;
    myEnd = end;
    numOfNeibours= dimention * 2;
    myMatrix = matrix;
}

//destructor
Bfs::Bfs(){};

/**
 * find the trajectory of bfs, from start node to the end node. use in queue and stack.
 * for every node in the matrix, find all the valid niebours and enter them to queue. each time update every
 * node, which one is his father, in order to we could find the trajectory.
 * @param myStarts: my start node
 * @param myEndS: my end node
 * @return vector of nodes in trajectory of bfs
 */
vector<Node*> Bfs:: runBfs(Node* myStarts, Node* myEndS) {
    //we use stack for know who was the last one that we pushed to the queue.
    queue<Node*> trip_queue;
    stack<Node*> trip_stack;
    //actions for the first point.
    myStarts->setFlag();
   // vector<Node*> garbage;
    trip_queue.push(myStarts);
    trip_stack.push(myStarts);
    myMatrix->setNodeInMatrix(myStarts);
    manageQueue(trip_queue, trip_stack, myStarts);
    //until the queue is not empty
    while (!trip_queue.empty()) {
        Node* last_in_q = trip_queue.front();
        //if the last node we pushed to the stack is the destination node-print.
        if (*last_in_q == *myEndS) {
            vector<Node *> trajectory;
            trajectory.push_back(last_in_q);
            Node *next = last_in_q->getNodeFather();
            while (next!= NULL) {
                trajectory.push_back(next);
                next = next->getNodeFather();
            }
            return trajectory;
        }
        //pop the last node we check.
        trip_queue.pop();
        Node* next_node = trip_queue.front();
        //update last in stack
        Node* last_in_stack = trip_stack.top();
        if (last_in_stack == myEndS) {
            //delete next_node;
            break;
        } else {
            manageQueue(trip_queue, trip_stack, next_node);
        }
    }
}

/**
 * this method get node, find his valid neibours and put them into the queue.
 * @param queue1: the queue with the all optional nodes that can be find in the trajectory of the bfs.
 * @param stack1: the stack
 * @param currentNode: node in the matrix
 */
void Bfs:: manageQueue(queue<Node*> &queue1, stack<Node*> &stack1, Node *currentNode) {
    //return array of neibours.
    vector<Node*> neighbours = myMatrix->getNiebours(*currentNode);
    for (int i = 0; i < numOfNeibours; i++) {
        //put in the neibours array the right neibours.
        // if the neighbour is exist...not -1 -1
        if ((neighbours[i]->getPointOfnode().GetX() != -1) && !neighbours[i]->getFlag()){
            //keep the father of the node in matrix
            neighbours[i]->setFather(currentNode);
            //set the flag when it's come to queue and update the matrix
            neighbours[i]->setFlag();
            Node *neig = neighbours[i];
            myMatrix->setNodeInMatrix(neig);
            //push the node to queue and stack.
            queue1.push(neighbours[i]);
            stack1.push(neighbours[i]);
        } else {
            //delete the bad neigbours
            if (!(neighbours[i]->getFlag())) {
            delete neighbours[i];
        }
        }
    }
}