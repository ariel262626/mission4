cmake_minimum_required(VERSION 3.6)
project(mission4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES  Matrix2d.cpp
        Matrix2d.h Grid.cpp Grid.h Bfs.cpp Bfs.h Node.cpp Node.h Point.cpp Point.h Driver.cpp Driver.h StandartCab.cpp
        StandartCab.h
        LuxuryCab.cpp LuxuryCab.h Trip.cpp Trip.h Passenger.cpp Passenger.h
        InfoTaxi.cpp InfoTaxi.h TexiCenter.cpp TexiCenter.h
        GameFlow.cpp GameFlow.h
        CabBase.h CabBase.cpp PharserInfo.cpp PharserInfo.h Tcp.cpp Tcp.h ClockTime.cpp ClockTime.h
        Socket.cpp Socket.h SocketToDriver.cpp SocketToDriver.h ConnectionClients.cpp ConnectionClients.h)

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})


add_executable(Server Server.cpp ${SOURCE_FILES} Server.h TaxiCenter.cpp )
add_executable(Client Client.cpp ${SOURCE_FILES} )

target_link_libraries(Server ${Boost_LIBRARIES})
target_link_libraries(Client ${Boost_LIBRARIES})
