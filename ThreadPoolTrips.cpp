//
// Created by dvir on 25/01/17.
//

#include "ThreadPoolTrips.h"

//constructor
ThreadPoolTrips::ThreadPoolTrips(int pool_size, Matrix2d* map) : m_pool_size(pool_size), myMap(map)
{
    isThreadPoolOver = false;
    for (int i = 0; i < m_pool_size; i++) {
        pthread_t tid;
        int ret = pthread_create(&tid, NULL, execute_thread, (void*) this);
        if (ret != 0) { /* error handling */ }
        threadsOfTrips.push_back(tid);
    }
    cout << m_pool_size << " threads created by the thread pool" << endl;
}

ThreadPoolTrips:: ThreadPoolTrips (int numOfThreads){ }

//destructor
ThreadPoolTrips::~ThreadPoolTrips()
{
    for (int i = 0; i < m_pool_size; i++) {
        pthread_join(threadsOfTrips[i], NULL);
    }
    cout << m_pool_size << " threads exited from the thread pool" << endl;
}

void* ThreadPoolTrips::execute_thread()
{
    Trip* taskTrip = NULL;
    while(true) {
        while (tripDeque.empty()) {
            sleep(1);
        }
        taskTrip = tripDeque.front();
        tripDeque.pop_front();
        taskTrip->getPathOfTripClone(*myMap);
        if (isThreadPoolOver){
            return NULL;
        }
    }
    return NULL;
}

int ThreadPoolTrips::add_task(Trip* taskTrip)
{
    tripDeque.push_back(taskTrip);
}

void ThreadPoolTrips:: setMap (Matrix2d* map){
    myMap = map;
}