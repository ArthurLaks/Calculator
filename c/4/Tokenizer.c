#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Include the module's own header file.
#include "Tokenizer.h"
static char* skipSpaces(char* position);
static char* buffer;
void initialize(char* string){
  buffer=string;
}
//Returns the next character that is not space and advances the buffer.
char nextChar(){
  //This function returns the character that the buffer is up to and then
  //increments the buffer.
  buffer=skipSpaces(buffer);
  char retval=*buffer;
  buffer++;
  return retval;
}
//Returns the next double and advances the position of the buffer.
double nextDouble(){
  //strtod takes a reference to a pointer and advances the position of that pointer to after the double. This call returns a double and advances buffer at the same time.
  return strtod(buffer,&buffer);
}
//Returns the next character that is not a space and does not change the
//position of the buffer.
char peek(){
  return *(skipSpaces(buffer));
}
//Takes a pointer to a position in a string and increments it until it does not point to a space.
char* skipSpaces(char* position){
  while(*(position)==' ')
    position++;
  return position;
}
//Returns true if there are no more characters besides spaces in the buffer.
int endOfBuffer(){
  //If the next character besides space is null, the buffer is over.
  return peek()==NULL;
}
