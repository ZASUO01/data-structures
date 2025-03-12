#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "entry.h"

// tree node with an Entry as the key and left/right child
typedef struct Node {
  Entry *entry;
  struct Node *left;
  struct Node *right;
  int height;
} Node;

Node *insert_node(Node *node, char type, const char *word, const char *meaning);
Node *delete_not_empty(Node *node);
void fprint_tree(Node *node, FILE *file);
void delete_tree(Node **node);

#endif
