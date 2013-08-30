CC=gcc
CFLAGS=-Wall -std=gnu99
Calc: Calculator.o Parser.o CreateTree.o ProccessTree.o
	$(CC) $(CFLAGS) -oCalc Calculator.o CreateTree.o ProccessTree.o \
Parser.o
Calculator.o: Calculator.c Parser.h Node.h CreateTree.h ProccessTree.h
	$(CC) $(CFLAGS) -c Calculator.c
CreateTree.o: CreateTree.c CreateTree.h Parser.h Node.h
	$(CC) $(CFLAGS) -c CreateTree.c
ProccessTree.o: ProccessTree.c ProccessTree.h Node.h
	$(CC) $(CFLAGS) -c ProccessTree.c
Parser.o: Parser.c Parser.h
	$(CC) $(CFLAGS) -c Parser.c
