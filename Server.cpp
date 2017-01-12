
#include <iostream>
#include "Tcp.h"
#include "GameFlow.h"

using namespace std;

int main(int argc, char *argv[]) {
    // create new socket. use in tcp
    Socket *tcp = new Tcp(1, stoi(argv[1]));
    // call gameflow for run the mission from the user
    GameFlow gameFlow = GameFlow(tcp);
    gameFlow.run();
    return 0;
}





