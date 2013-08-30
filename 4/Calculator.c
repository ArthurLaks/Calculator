#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Parser.h"
#include "Node.h"
#include "CreateTree.h"
#include "ProccessTree.h"

int main(int nArgs,char** args){
  initialize(*(args+1));//Initialize the parser to the first argument.
  node* tree=createTree();
  double result=proccessNode(tree);
  printf("The result of the calculation is %f\n",result);
  return 0;
}
