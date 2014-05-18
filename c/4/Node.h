#ifndef NODE_H
#define NODE_H
struct node{
  struct node* leftNode;
  struct node* rightNode;
//This union is used to store the content of a node. For a leaf node, that is
//a number and for other nodes, that is an operator.
  union{
    double operand;
    char operator;
  }contents;
};
typedef struct node node;
#endif
