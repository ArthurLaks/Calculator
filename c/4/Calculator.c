#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
#include "Node.h"
#include "Tokenizer.h"
#include "ProcessTree.h"

int main(int nArgs,char** args){
  initialize(*(args+1));//Initialize the parser to the first argument.
  node* tree=parse();
  double result=processNode(tree);
  printf("The result of the calculation is %f\n",result);
  return 0;
}
