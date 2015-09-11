CC=gcc
CFLAGS=-Wall -std=gnu99
Calc: Calculator.o Tokenizer.o Parser.o ProcessTree.o
	$(CC) $(CFLAGS)  -oCalc Calculator.o Parser.o ProcessTree.o \
Tokenizer.o -lm
Calculator.o: Calculator.c Tokenizer.h Node.h Parser.h ProcessTree.h
	$(CC) $(CFLAGS) -c Calculator.c
Parser.o: Parser.c Parser.h Tokenizer.h Node.h
	$(CC) $(CFLAGS) -c Parser.c
ProcessTree.o: ProcessTree.c ProcessTree.h Node.h
	$(CC) $(CFLAGS) -c ProcessTree.c
Tokenizer.o: Tokenizer.c Tokenizer.h
	$(CC) $(CFLAGS) -c Tokenizer.c

clean:
	rm -f *~ *.o calc
