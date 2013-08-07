# Makefile for the programming assignment

server_objects = yacc_file.tab.o lex.yy.o Helper.o Socket.o Server.o server_main.o LinkedList.o
client_objects = Helper.o Socket.o Client.o client_main.o

all : serv cli
	
serv: $(server_objects)
	g++ -o serv $(server_objects)  -pthread


cli: $(client_objects)
	g++ -o cli $(client_objects)
	
yacc_file.tab.o: yacc_file.yy
	bison -d yacc_file.yy
lex.yy.o: lex_file.ll
	flex --header-file="Lexheader.h" lex_file.ll
	g++ -c lex.yy.c yacc_file.tab.cc
	
Socket: Socket.cpp
Client: Client.cpp
Helper: Helper.cpp
Server_main: server_main.cpp
Client_main: client_main.cpp
LinkedList: LinkedList.cpp
Server: Server.cpp

clean:
	rm -f *.o serv cli Lexheader.h lex.y* yacc_file.t*
