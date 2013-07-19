# Makefile for the Echo Server programming example

server_objects = Helper.o Socket.o Server.o server_main.o
client_objects = Helper.o Socket.o Client.o client_main.o

all : serv cli

serv: $(server_objects)
	g++ -o serv $(server_objects) -pthread


cli: $(client_objects)
	g++ -o cli $(client_objects)


Socket: Socket.cpp
Client: Client.cpp
Helper: Helper.cpp
Server: Server.cpp
Server_main:   server_main.cpp
Client_main: client_main.cpp

clean:
	rm -f *.o serv cli
