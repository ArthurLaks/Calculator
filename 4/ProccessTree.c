#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ProccessTree.h"
#include "Node.h"
double proccessNode(node* node){
  double retval;
  double divisor;
  if(node->rightNode==NULL)
    retval=node->contents.operand;
  else
    switch(node->contents.operator){
    case '+':
      retval=proccessNode(node->leftNode)+proccessNode(node->rightNode);
      break;
    case '-':
      retval=proccessNode(node->leftNode)-proccessNode(node->rightNode);
      break;
    case '*':
      retval=proccessNode(node->leftNode)*proccessNode(node->rightNode);
      break;
    case '/':
      //Check for division by zero.
      divisor=proccessNode(node->rightNode);
      if(divisor==0){
	(void)printf("Division by zero error");
	exit(1);
      }
      retval=proccessNode(node->leftNode)/divisor;
      break;
    case '^':
      retval=pow(proccessNode(node->leftNode),proccessNode(node->rightNode));
    }
  free(node);
  return retval;
}
