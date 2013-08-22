# Makefile for the programming assignment

CC= g++
CFLAGS= -lpthread -g -Wall
LEX= flex
YACC= bison

server_objects = yacc_file.tab.o lex.yy.o Helper.o Socket.o Server.o server_main.o LinkedList.o
client_objects = Helper.o Socket.o Client.o client_main.o

all : serv cli

serv: $(server_objects)
	$(CC) -o $@ $^ $(CFLAGS)

cli: $(client_objects)
	$(CC) -o $@ $^ $(CFLAGS)

yacc_file.tab.o: yacc_file.yy
	$(YACC) -d $<

lex.yy.o: lex_file.ll
	$(LEX) --header-file="Lexheader.h" $<
	$(CC) -c lex.yy.c yacc_file.tab.cc

Socket.o: Socket.cpp
Client.o: Client.cpp
Helper.o: Helper.cpp
server_main.o: server_main.cpp
client_main.o: client_main.cpp
LinkedList.o: LinkedList.cpp
Server.o: Server.cpp

clean:
	rm -f *.o serv cli Lexheader.h lex.y* yacc_file.t*
