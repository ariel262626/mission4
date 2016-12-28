cmake_minimum_required(VERSION 3.5)
project(mission4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(core_sockets Socket.cpp Udp.cpp)


set(SOURCE_FILES main.cpp Matrix2d.cpp
        Matrix2d.h Grid.cpp Grid.h Bfs.cpp Bfs.h Node.cpp Node.h Point.cpp Point.h Driver.cpp Driver.h StandartCab.cpp
        StandartCab.h
        LuxuryCab.cpp LuxuryCab.h Trip.cpp Trip.h Passenger.cpp Passenger.h
        InfoTaxi.cpp InfoTaxi.h TexiCenter.cpp TexiCenter.h server.cpp
         GameFlow.cpp GameFlow.h
         CabBase.h CabBase.cpp PharserInfo.cpp PharserInfo.h Udp.cpp Udp.h
        Socket.cpp Socket.h)

set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
add_library(sockets ${core_sockets})
add_executable(server server.cpp)
add_executable(client client.cpp)
add_executable(mission4 ${SOURCE_FILES})
target_link_libraries(server sockets)
target_link_libraries(client sockets)
target_link_libraries(mission4 ${Boost_LIBRARIES})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
target_link_libraries(mission4)
