#ifndef PARSER_H
#define PARSER_H
#include "Node.h"
//This function returns the rootNode of a tree constructed from characters
//obtained from the parser.  It is used recursively to generate parentheses,
//because the contents of parentheses can be thought of as miniature 
//expression in of itself.
node* parse(void);

#endif
