cmake_minimum_required(VERSION 3.5)
project(MISSION3src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp Matrix2d.cpp
        Matrix2d.h Grid.cpp Grid.h Bfs.cpp Bfs.h Node.cpp Node.h Point.cpp Point.h Driver.cpp Driver.h StandartCab.cpp
        StandartCab.h
        LuxuryCab.cpp LuxuryCab.h Trip.cpp Trip.h Passenger.cpp Passenger.h
        InfoTaxi.cpp InfoTaxi.h TexiCenter.cpp TexiCenter.h 
         GameFlow.cpp GameFlow.h
         CabBase.h CabBase.cpp PharserInfo.cpp PharserInfo.h)
add_executable(MISSION3src ${SOURCE_FILES})
