#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
//This macro makes it easy to switch types from double to float or int or the like.
#define number double
//This union is used to store the content of a node. For a leaf node, that is
//a number and for other nodes, that is an operator.
union content{
  number operand;
  char operator;
};
struct node{
  struct node* leftNode;
  struct node* rightNode;
  union content contents;
};

void addOperator(struct node* node,char operator);
struct node* createEmptyNode();
void addOperand(struct node* node,number operand);
number processNode(struct node* node);
//Takes a pointer to an empty node and an operator and assigns the operator to the contents union of the node.
void addOperator(struct node* node,char operator){
  union content contents;
  contents.operator=operator;
  node->contents=contents;
}
//Returns a pointer to a an empty node on the heap with both of its children null and the contents unititialized.
struct node* createEmptyNode(){
  struct node* retval=malloc(sizeof(struct node));
  retval->rightNode=NULL;
  retval->leftNode=NULL;
  return retval;
}
//Takes a pointer to an empty node and a number and assigns the number to the
//content of the node.
void addOperand(struct node* node,number operand){
  union content contents;
  contents.operand=operand;
  node->contents=contents;
}
//Declare references to the root node and the node that is furthest to the 
//right.  This points to the location where the next operand should be placed.
struct node* rootNode;
struct node* rightNode;

int main(int nArgs,char** args){
  initialize(*(args+1));//Initialize the parser to the first argument.
  //Initialize the rootNode and rightNode to be the right child of the root
  //node.
  rootNode=createEmptyNode();
  //Initialize the children of rootNode and process the first two parameters (the first operand and the first operator).  The root node should contain the operator and its left child should contain the operand.
  rootNode->leftNode=createEmptyNode();
  addOperand(rootNode->leftNode,nextDouble());
  addOperator(rootNode,nextChar());
  rootNode->rightNode=createEmptyNode();
  rightNode=rootNode->rightNode;
  
  //For every operand and operator, add a node for the operator and a child of that for the ooerand.
  while(true){
    number operand=nextDouble();
    //If the operand is the last one then assign it to rightNode, which is kept blank in the previous iterations of the loop and break.
    if(endOfBuffer()){
      addOperand(rightNode,operand);
      break;
    }
    char operator=nextChar();
    if(operator=='+'||operator=='-'){
      //If the operator is addition or subraction, make a new root containing that operator and the left child of that should contain the tree as it was (in other words, the left node of the new root should refer to the old root node) and the right child should contain the next operand.  The operand before the + or - should be grouped with the previous operator and assigned to rightNode.
      addOperand(rightNode,operand);
      struct node* newRoot=createEmptyNode();
      addOperator(newRoot,operator);
      newRoot->leftNode=rootNode;
      newRoot->rightNode=createEmptyNode();
      rightNode=newRoot->rightNode;
      rootNode=newRoot;
  }else
      if(operator=='*'||operator=='/'){
	//If the operator is * or /, it should be appendend to the bottom of the tree.  rightNode is assigned to the operator and its left child should be the operand before it because it is grouped with it.
	addOperator(rightNode,operator);
	struct node* leftOperand=createEmptyNode();
	addOperand(leftOperand,operand);
	rightNode->leftNode=leftOperand;
	rightNode->rightNode=createEmptyNode();
	rightNode=rightNode->rightNode;
      }
  }
  number result=processNode(rootNode);
  printf("The result of the calculation is %f\n",result);
  return 0;
}
//This function proccesses a node. If it is a leaf node, it returns its content. If it is a branch node, it returns the operator it represents performed on its two children. It also realeases the memory used by the node in the heap.
number proccessNode(struct node* node){
  number retval;
  if(node->leftNode==NULL)
    retval=node->contents.operand;
  else{
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
    case '/'://Check for division by zero.
      number divisor=proccessNode(node->rightNode);
      if(divisor==0)
	(void)printf("Division by zero error");
      retval=proccessNode(node->leftNode)/divisor;
      break;
    }
  }
  free(node);
  return retval;
}
