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
    ThreadPoolTrips(int numOfThreads);
     ThreadPoolTrips(int pool_size, Matrix2d* map);
     ~ThreadPoolTrips();
     void* execute_thread();
     int add_task(Trip* taskTrip);
    void setMap (Matrix2d* map);

};


#endif //MISSION4_THREADPOOLTRIPS_H
