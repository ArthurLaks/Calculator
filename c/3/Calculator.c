#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
#include <math.h>
typedef struct node node;//This is to avoid having to type struct node all 
//the time. I could have defined it to be a pointer but it would make the 
//code less readable.
struct node{
  node* leftNode;
  node* rightNode;
//This union is used to store the content of a node. For a leaf node, that is
//a number and for other nodes, that is an operator.
  union{
    double operand;
    char operator;
  }contents;
  //This enum is used to keep track of the type of the node (whether it is 
  //a leaf node representing an operand or a branch node representing
  //an operator).
  enum{
    leaf,
    branch
  }type;
};

void insertOperator(node* node,char operator);
node* createEmptyNode();
void insertOperand(node* node,double operand);
double proccessNode(node* node);
int precedence(char operator);
//Takes a pointer to an empty node and an operator and assigns the 
//operator to the contents union of the node.  It also makes sure that 
//both of its child members point to nodes, and are not null pointers.
void insertOperator(node* node,char operator){
  node->contents.operator=operator;
  node->type=branch;
if(node->leftNode==NULL)
    node->leftNode=createEmptyNode();
  if(node->rightNode==NULL)
    node->rightNode=createEmptyNode();
}
//Returns a pointer to a an empty node on the heap with both of its children null and the contents unititialized.
node* createEmptyNode(){
  node* retval=malloc(sizeof(node));
  retval->rightNode=NULL;
  retval->leftNode=NULL;
  return retval;
}
//Takes a pointer to an empty node and a double and assigns the double to the
//content of the node.
void insertOperand(node* node,double operand){
  node->contents.operand=operand;
  node->type=leaf;
}
//Takes an operator and returns its precedence in terms of order of operations.
//A higher return value means that the operator should be done earlier.
int precedence(char operator){
  switch(operator){
  case '*':  //Falls through to '/'
  case '/':
    return 2;
    break;
  case '^':
    return 3;
    break;
  case '+':
  case '-':
  default:
    return 1;
    break;

  }
}
//Declare references to the root node and the node that is furthest to the 
//right.  This points to the location where the next operand should be placed.
node* rootNode;
node* rightNode;

int main(int nArgs,char** args){
  initialize(*(args+1));//Initialize the parser to the first argument.
  //Initialize the rootNode and rightNode to be the right child of the root
  //node.
  rootNode=createEmptyNode();
  //Initialize the children of rootNode and process the first two parameters (the first operand and the first operator).  The root node should contain the operator and its left child should contain the operand.
  rootNode->leftNode=createEmptyNode();
  insertOperand(rootNode->leftNode,nextDouble());
  insertOperator(rootNode,nextChar());
  rootNode->rightNode=createEmptyNode();
  rightNode=rootNode->rightNode;
  //Keeps track of the previous operator in order to determine whether the 
  //operand in the next iteration of the loop should be grouped with the 
  //previous operator or with the current operator.
  char prevOperator=rootNode->contents.operator;
  //For every operand and operator, add a node for the operator and a child
  //of that for the ooerand.
  while(1){
    double operand=nextDouble();
    //If the operand is the last one then assign it to rightNode, which is kept blank in the previous iterations of the loop and break.
    if(endOfBuffer()){
      insertOperand(rightNode,operand);
      break;
    }
    //Here is an explanation of the algorithm that is used to construct the 
    //syntax tree:
    
    //The program iterates through the tree and procceeding to the right child
    //of every node until it reaches the node whose right child has equal or
    //greater precedence to the one being inserted (for example, if operator
    //is '*', it stops at the last '+' or '-' before another '*'). If 
    //the current operator has greater precedence than the preceding one
    //then the current operator should be on the bottom of the tree and
    //the operand is grouped with the current operator.  Otherwise, there
    //is an operator with greater precedence than the one being added, and
    //it belongs lower on the tree. Therefore, toInsert->leftNode is assigned
    //to that operator (pNode->operator).  Also, the operand should be 
    //grouped with the previous operator, so it is assigned to rightNode. 
    //Either way, the right child of the node being added remains empty,
    //and it is assigned to rightNode for the next iteration.
    char operator=nextChar();
    //tempRoot is created in case operator is of lower than or equal 
    //precedence as the root operator, in which case toInsert should become
    //the root node and pNode has to be the parent of the root node. Since
    //the left node of toInsert is assigned to the right node of pNode,
    //tempRoot->rightNode is assigned to rootNode. toInsert is deleted later
    //in the loop.
   
    node* tempRoot=createEmptyNode();
    tempRoot->type=branch;
    tempRoot->rightNode=rootNode;
    node* pNode=tempRoot;
    while(pNode->rightNode->type==branch &&
	 precedence(operator)>precedence(pNode->rightNode->contents.operator))
      pNode=pNode->rightNode;
    
    node* toInsert=createEmptyNode();
    insertOperator(toInsert,operator);
    if(precedence(operator)>precedence(prevOperator)){      
      insertOperand(toInsert->leftNode,operand);
    }else{
      insertOperand(rightNode,operand);
      toInsert->leftNode=pNode->rightNode;
    }
    pNode->rightNode=toInsert;
    rightNode=toInsert->rightNode;
    prevOperator=operator;
    //If toInsert was supposed to replace rootNode (as explained in the 
    //previous comment block), this line does so. If not, it does nothing
    //because tempRoot->rightNode is already rootNode.
    rootNode=tempRoot->rightNode;
    free(tempRoot);
  }
  double result=proccessNode(rootNode);
  printf("The result of the calculation is %f\n",result);
  return 0;
}
//This function proccesses a node. If it is a leaf node, it returns its
//content. If it is a branch node, it returns the operator it represents
//performed on its two children. It also realeases the memory used by the
//node in the heap.
double proccessNode(node* node){
  double retval;
  double divisor;
  switch(node->type){
  case leaf:
    retval=node->contents.operand;
    break;
  case branch:
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
      if(divisor==0)
	(void)printf("Division by zero error");
      retval=proccessNode(node->leftNode)/divisor;
      break;
    case '^':
      retval=pow(proccessNode(node->leftNode),proccessNode(node->rightNode));
    }
  }
  free(node);
 return retval;
}
