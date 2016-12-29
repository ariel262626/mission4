




cmake_minimum_required(VERSION 3.6)
project(mission4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES  Matrix2d.cpp
        Matrix2d.h Grid.cpp Grid.h Bfs.cpp Bfs.h Node.cpp Node.h Point.cpp Point.h Driver.cpp Driver.h StandartCab.cpp
        StandartCab.h
        LuxuryCab.cpp LuxuryCab.h Trip.cpp Trip.h Passenger.cpp Passenger.h
        InfoTaxi.cpp InfoTaxi.h TexiCenter.cpp TexiCenter.h
        GameFlow.cpp GameFlow.h
        CabBase.h CabBase.cpp PharserInfo.cpp PharserInfo.h Udp.cpp Udp.h
        Socket.cpp Socket.h)
#add_executable(mission4 ${SOURCE_FILES})



set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})


add_executable(server server.cpp ${SOURCE_FILES} ClockTime.cpp ClockTime.h)
add_executable(client client.cpp ${SOURCE_FILES} ClockTime.cpp ClockTime.h)

target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(client ${Boost_LIBRARIES})
