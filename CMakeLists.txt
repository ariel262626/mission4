cmake_minimum_required(VERSION 3.5)
project(mission4)

set(core_sockets Socket.cpp Udp.cpp Tcp.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp Matrix2d.cpp
        Matrix2d.h Grid.cpp Grid.h Bfs.cpp Bfs.h Node.cpp Node.h Point.cpp Point.h Driver.cpp Driver.h StandartCab.cpp
        StandartCab.h
        LuxuryCab.cpp LuxuryCab.h Trip.cpp Trip.h Passenger.cpp Passenger.h
        InfoTaxi.cpp InfoTaxi.h TexiCenter.cpp TexiCenter.h 
         GameFlow.cpp GameFlow.h
         CabBase.h CabBase.cpp PharserInfo.cpp PharserInfo.h Udp.cpp Udp.h server.cpp clientDriver.cpp
        Socket.cpp Socket.h)

set(BOOST_ROOT CACHE PATH "/usr/include/boost/") # or equivalent location
find_package(Boost 1.58.0 COMPONENTS serialization system) # or equivalent version

add_executable(mission4 ${SOURCE_FILES})
add_executable(server server.cpp)
#add_executable(client client.cpp)

target_link_libraries(mission4)
include_directories()

