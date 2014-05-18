#include "Node.h"
#ifndef PROCESSNODE_H
#define PROCESSNODE_H
//This function proccesses a node. If it is a leaf node, it returns its
//content. If it is a branch node, it returns the operator it represents
//performed on its two children. It also realeases the memory used by the
//node in the heap.
double processNode(node* node);
#endif
