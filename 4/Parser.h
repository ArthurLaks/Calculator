#ifndef PARSER_H
#define PARSER_H
//Returns the next double and advances the position of the buffer.
double nextDouble();
//Returns the next character that is not space and advances the buffer.
char nextChar();
//Returns the next character that is not a space and does not change the
//position of the buffer.
char peek();
//This function is expected to be called before any other. It initializes the
//buffer. This module relies on the string that the buffer is pointing to 
//remaining on the stack as long as its functions are called.
void initialize(char* string);
//Returns true if there are no more characters besides spaces in the buffer.
int endOfBuffer();
#endif
