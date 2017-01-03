all: Server Client
Server: Server.o Bfs.o Node.o CabBase.o Grid.o Point.o Matrix2d.o Grid.o InfoTaxi.o Driver.o LuxuryCab.o StandartCab.o Passenger.o Udp.o PharserInfo.o TexiCenter.o Trip.o Udp.o Socket.o ClockTime.o
	g++ -std=c++0x -o Server Server.o Bfs.o Node.o CabBase.o Grid.o Point.o Matrix2d.o Grid.o InfoTaxi.o Driver.o LuxuryCab.o StandartCab.o Passenger.o Udp.o PharserInfo.o TexiCenter.o Trip.o ClockTime.o Socket.o -lboost_serialization

Client: Client.o Bfs.o Node.o CabBase.o Grid.o InfoTaxi.o Point.o Matrix2d.o Grid.o Driver.o LuxuryCab.o StandartCab.o Passenger.o PharserInfo.o Trip.o Udp.o Socket.o ClockTime.o
	g++ -std=c++0x -o Client Client.o Bfs.o Node.o CabBase.o Grid.o InfoTaxi.o Point.o Matrix2d.o Grid.o Driver.o LuxuryCab.o StandartCab.o Passenger.o PharserInfo.o Trip.o Udp.o Socket.o ClockTime.o -lboost_serialization

Bfs.o: Bfs.cpp Bfs.h
	g++ -std=c++0x -c Bfs.cpp

Node.o: Node.cpp Node.h
	g++ -std=c++0x -c Node.cpp

CabBase.o: CabBase.cpp CabBase.h
	g++ -std=c++0x -c CabBase.cpp

Grid.o: Grid.cpp Grid.h
	g++ -std=c++0x -c Grid.cpp

Point.o: Point.cpp Point.h
	g++ -std=c++0x -c Point.cpp

InfoTaxi.o: InfoTaxi.cpp InfoTaxi.h
	g++ -std=c++0x -c InfoTaxi.cpp

Driver.o: Driver.cpp Driver.h
	g++ -std=c++0x -c Driver.cpp


LuxuryCab.o: LuxuryCab.cpp LuxuryCab.h
	g++ -std=c++0x -c LuxuryCab.cpp

StandartCab.o: StandartCab.cpp StandartCab.h
	g++ -std=c++0x -c StandartCab.cpp

Passenger.o: Passenger.cpp Passenger.h
	g++ -std=c++0x -c Passenger.cpp

Matrix2d.o: Matrix2d.cpp Matrix2d.h
	g++ -std=c++0x -c Matrix2d.cpp

PharserInfo.o: PharserInfo.cpp PharserInfo.h
	g++ -std=c++0x -c PharserInfo.cpp

TexiCenter.o: TexiCenter.cpp TexiCenter.h
	g++ -std=c++0x -c TexiCenter.cpp

Trip.o: Trip.cpp Trip.h
	g++ -std=c++0x -c Trip.cpp

ClockTime.o: ClockTime.cpp ClockTime.h
	g++ -std=c++0x -c ClockTime.cpp

Socket.o: Socket.cpp Socket.h
	g++ -std=c++0x -c Socket.cpp

Udp.o: Udp.cpp Udp.h
	g++ -std=c++0x -c Udp.cpp

Client.o: Client.cpp
	g++ -std=c++0x -c Client.cpp -lboost_serialization

Server.o: Server.cpp
	g++ -std=c++0x -c Server.cpp -lboost_serialization
