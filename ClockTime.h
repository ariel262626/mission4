//
// Created by ariel on 29/12/16.
//

#ifndef MISSION4_CLOCKTIME_H
#define MISSION4_CLOCKTIME_H

/**
 * class of the time of our world of the program
 */
class ClockTime {
private:
int myCurrentTime;
public:
    //construcor
    ClockTime();

    /**
     * set the time to curent time +1
     */
    void setTime();

    /**
     * get the current time
     * @return - the time
     */
    int getTime();
};


#endif //MISSION4_CLOCKTIME_H
