//
// Created by ariel on 17/01/17.
//

#ifndef MISSION4_BOOLEANTODESCRIPTOR_H
#define MISSION4_BOOLEANTODESCRIPTOR_H


class BooleanToDescriptor {
private:
    int myDescriptor;
    bool isMoved;

public:
    BooleanToDescriptor (int descriptor);
    int getMyDescriptor();
    void setIsMovedToFalse ();
    void setIsMovedToTrue ();
    bool getIsMoved ();



};


#endif //MISSION4_BOOLEANTODESCRIPTOR_H
