#include "Node.h"
#ifndef PROCCESSNODE_H
#define PROCCESSNODE_H
//This function proccesses a node. If it is a leaf node, it returns its
//content. If it is a branch node, it returns the operator it represents
//performed on its two children. It also realeases the memory used by the
//node in the heap.
double proccessNode(node* node);
#endif
