CC=gcc
CFLAGS=-Wall -std=gnu99
Calc: Calculator.o Parser.o
	$(CC) $(CFLAGS) -oCalc Calculator.o Parser.o
Calculator.o: Calculator.c Parser.h
	$(CC) $(CFLAGS) -c Calculator.c
Parser.o: Parser.c Parser.h
	$(CC) $(CFLAGS) -c Parser.c
