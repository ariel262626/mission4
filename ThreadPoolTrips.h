//
// Created by dvir on 25/01/17.
//

#ifndef MISSION4_THREADPOOLTRIPS_H
#define MISSION4_THREADPOOLTRIPS_H


#include <sys/param.h>
#include <iostream>
#include <vector>
#include "Trip.h"

using namespace std;
class ThreadPoolTrips {

private:
     int m_pool_size;
     vector<pthread_t> threadsOfTrips;
     deque<Trip*> tripDeque;
     Matrix2d* myMap;
    bool isThreadPoolOver;

public:
    //constructors
    ThreadPoolTrips(int numOfThreads);
     ThreadPoolTrips(int pool_size, Matrix2d* map);
    //destructor
     ~ThreadPoolTrips();

    /**
     * manage the pool trhead
     */
     static void* execute_thread(void* arg);

    /**
     * add task(trip) to our trip list to calculate their path
     * @param taskTrip - trip to add
     * @return if succed
     */
     int add_task(Trip* taskTrip);

    /**
     * set mymap for calculate the path.
     * @param map - map to set
     */
    void setMap (Matrix2d* map);

};


#endif //MISSION4_THREADPOOLTRIPS_H
