
all: server client

# Put here all the common files which are being used both in client and server
COMMON_SOURCES = Matrix2d.cpp Matrix2d.h Grid.cpp Grid.h Bfs.cpp Bfs.h Node.cpp Node.h Point.cpp Point.h Driver.cpp Driver.h StandartCab.cpp StandartCab.h LuxuryCab.cpp LuxuryCab.h Trip.cpp Trip.h Passenger.cpp Passenger.h TexiCenter.cpp TexiCenter.h GameFlow.cpp GameFlow.h CabBase.h CabBase.cpp PharserInfo.cpp PharserInfo.h Tcp.cpp Tcp.h ClockTime.cpp ClockTime.h Socket.cpp Socket.h SocketToDriver.cpp SocketToDriver.h ConnectionClients.cpp ConnectionClients.h TripMap.cpp TripMap.h BooleanToDescriptor.cpp BooleanToDescriptor.h
server:
	g++ -std=c++0x Server.cpp $(COMMON_SOURCES) -lboost_serialization -I. -o server.out -pthread -D_GLIBCXX_USE_NANOSLEEP 
# (for example)
client:
	g++ -std=c++0x Client.cpp $(COMMON_SOURCES) -lboost_serialization -I. -o client.out -pthread
