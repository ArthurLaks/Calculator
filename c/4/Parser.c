#include <stdlib.h>
#include "Node.h"
#include "Parser.h"
#include "Tokenizer.h"
static int precedence(char operator);
static node* createEmptyNode(void);
//Returns a pointer to a an empty node on the heap with both of its children
//null and the contents unititialized.
static node* createEmptyNode(void){
  node* retval=malloc(sizeof(node));
  //Make sure that the children are null and not unitialized
  retval->rightNode=NULL;
  retval->leftNode=NULL;
  return retval;
}
//Takes an operator and returns its precedence in terms of order of operations.
//A higher return value means that the operator should be done earlier.
static int precedence(char operator){
  switch(operator){
  case '+'://Falls through to '-'
  case '-':
    return 1;
  case '*':  
  case '/':
    return 2;
  case '^':
    return 3;
    //The createTree function counts on treating a space as having the lowest
    //precedence so that all operators would be inserted below it.
  default:
    return 0;
  }
}

node* parse(void){
  //The loop has special treatment for the root node if it is empty.  That code
  //is put in the loop and not before it (as in previous versions) so that the
  //treatment of an opening parenthesis would be shared between the code for
  //the first operation and the code for the rest (this is neccessary if an 
  //expression starts with a parenthesis).
  node* rootNode=NULL;
  //Keeps track of the previous operator in order to determine whether the 
  //operand in the next iteration of the loop should be grouped with the 
  //previous operator or with the current operator.
  char prevOperator=' ';
  //The loop keeps track of the previous operator so that it should be able to
  //assign the operand to it if it should be grouped with the previous
  //operator.
  node* prevNode;
  
  //For every operand and operator, add a node for the operator and a child
  //of that for the ooerand.
  while(1){
    //Operand is the operand that the operator is going on. It could be the
    //content of parentheses, in which case it would be a branch node, or 
    //it could be a double.
    node* operand;
    //If the next character is an opening parenthesis than it should skip it
    //and call itself on the contents of the parenthesis.
    if(peek()=='('){
      nextChar();
      operand=parse();
    }else{
      operand=createEmptyNode();
      operand->contents.operand=nextDouble();
    }

    //If the operand is the last one then assign it to rightNode, which is
    //kept blank in the previous iterations of the loop and break.
    if(peek()==')'||endOfBuffer()){
      nextChar();
      prevNode->rightNode=operand;
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
    node* toInsert=createEmptyNode();
    toInsert->contents.operator=operator;
    //The root node is null for the first iteration of the loop, and it should
    //be treated differently.
    if(rootNode==NULL){
      rootNode=toInsert;
      rootNode->leftNode=operand;
    }else{
      node* tempRoot=createEmptyNode();
      tempRoot->rightNode=rootNode;
      node* parentNode=tempRoot;
      //I am relying on the fact that the and operator short-circuits in order
      //to prevent a seg-fault if the right child is null. It also ensures that
      //parent node is not a leaf node.
      while(parentNode->rightNode!=NULL &&
	    precedence(operator)>
	    precedence(parentNode->rightNode->contents.operator)){
	parentNode=parentNode->rightNode;    
      }
      //If the current operator is of higher precedence than the previous 
      //operator than toInsert should be grouped with the current operator,
      //which would be inserted at the bottom of the tree.
      if(precedence(operator)>precedence(prevOperator)){      
	toInsert->leftNode=operand;
      }else{
	//Otherwise, the operand should be grouped with the previous operator
	//and the left node of toInsert should point to the operator with
	//higher precedence that should go lower on the tree.
	prevNode->rightNode=operand;
	toInsert->leftNode=parentNode->rightNode;
      }
      //Insert toInsert.
      parentNode->rightNode=toInsert;
      //If toInsert was supposed to replace rootNode (as explained in an 
      //earliear comment block), this line does so. If not, it does nothing
      //because tempRoot->rightNode is already rootNode.
      rootNode=tempRoot->rightNode;      
      free(tempRoot);
    }
    prevNode=toInsert;
    prevOperator=operator;
  }
  return rootNode;
}
