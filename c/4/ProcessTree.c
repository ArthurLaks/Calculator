#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ProcessTree.h"
#include "Node.h"
double processNode(node* node){
  double retval;
  double divisor;
  if(node->rightNode==NULL)
    retval=node->contents.operand;
  else
    switch(node->contents.operator){
    case '+':
      retval=processNode(node->leftNode)+processNode(node->rightNode);
      break;
    case '-':
      retval=processNode(node->leftNode)-processNode(node->rightNode);
      break;
    case '*':
      retval=processNode(node->leftNode)*processNode(node->rightNode);
      break;
    case '/':
      //Check for division by zero.
      divisor=processNode(node->rightNode);
      if(divisor==0){
	(void)printf("Division by zero error");
	exit(1);
      }
      retval=processNode(node->leftNode)/divisor;
      break;
    case '^':
      retval=pow(processNode(node->leftNode),processNode(node->rightNode));
    }
  free(node);
  return retval;
}
