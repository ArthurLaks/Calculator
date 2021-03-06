/* This calculator uses a tree in order to implement order of operations for addition and multiplication without parentheses. Addition and subraction are added at the top of the tree and multiplication and division are added at the bottom. Then, it recursively evaluates the tree, with the leaf nodes the base case, so that multiplication and division are done first.
In this version of the calculator, instead of writing my own code to parse a string with the user's input, I rely on him passing the operands and operators as command-line parameters, seperated by spaces.
*/
#include <stdio.h>
#include <stdlib.h>
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
number proccessNode(struct node* node);
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
  //Initialize the rootNode and rightNode to be the right child of the root
  //node.
  rootNode=createEmptyNode();
  //Initialize the children of rootNode and process the first two parameters (the first operand and the first operator).  The root node should contain the operator and its left child should contain the operand.
  rootNode->leftNode=createEmptyNode();
  addOperator(rootNode,**(args+2));
  addOperand(rootNode->leftNode,atof(*(args+1)));
  rootNode->rightNode=createEmptyNode();
  rightNode=rootNode->rightNode;
  int counter;
  //For every two parameters from the fourth one (excluding the name of the program and the ones that were already proccessed) and until the last one, which gets special treatment.
  for(counter=3;counter<nArgs-1;counter+=2){
    //The operator is the first (and, hopefully the only) character in the second parameter of each group of two.
    char operator=(*(args+counter+1))[0];
    if(operator=='+'||operator=='-'){
      //If the operator is addition or subraction, make a new root containing that operator and the left child of that should contain the tree as it was (in other words, the left node of the new root should refer to the old root node) and the right child should contain the next operand.  The operand before the + or - should be grouped with the previous operator and assigned to rightNode.
      addOperand(rightNode,atof(*(args+counter)));
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
	addOperand(leftOperand,atof(*(args+counter)));
	rightNode->leftNode=leftOperand;
	rightNode->rightNode=createEmptyNode();
	rightNode=rightNode->rightNode;
      }
  }
  //Assign the last operand to rightNode
  addOperand(rightNode,atof(*(args+nArgs-1)));
  number result=proccessNode(rootNode);
  printf("The result of the calculation is %f\n",result);
  return 0;
}
//This function proccesses a node. If it is a leaf node, it returns its content. If it is a branch node, it returns the operator it represents performed on its two children. It also releases the memory used by the node in the heap.
number proccessNode(struct node* node){
  number retval;
  if(node->leftNode==NULL)
    retval=node->contents.operand;
  else{
    number divisor;
    switch(node->contents.operator){
    case '+':
      retval=proccessNode(node->leftNode)+proccessNode(node->rightNode);
      break;
    case '-':
      retval=proccessNode(node->leftNode)-proccessNode(node->rightNode);
      break;
    case '*':
      retval=proccessNode(node->leftNode) * proccessNode(node->rightNode);
      break;
    case '/'://Check for division by zero.
      divisor=proccessNode(node->rightNode);
      if(divisor==0)
	(void)printf("Division by zero error");
      retval=proccessNode(node->leftNode)/divisor;
      break;
    }
  }
  free(node);
  return retval;
}
