#include "avl-tree.h"
#include "error-assert.h"
#include "memory-log.h"
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (a > b ? a : b)

// create a new node and init values
static Node *create_node(Entry *entry) {
  // allocate node memory
  Node *n = (Node *)malloc(sizeof(Node));
  error_assert((n != NULL), "Failed to allocate memory.");

  // init values
  n->entry = entry;
  n->left = NULL;
  n->right = NULL;
  n->height = 1;

  return n;
}

// aux function to get the current node height
static int get_height(Node *node) { return node != NULL ? node->height : 0; }

// returns the balance value of the current subtree
static int balance_factor(Node *node) {
  if (node != NULL) {
    return get_height(node->left) - get_height(node->right);
  }

  return 0;
}

// get the update height based on current children heights
static int get_updated_height(Node *node) {
  if (node != NULL) {
    return 1 + MAX(get_height(node->left), get_height(node->right));
  }

  return 0;
}

// single left rotation
static Node *rotate_left(Node *x) {
  Node *y = x->right;
  Node *yl = y->left;

  y->left = x;
  x->right = yl;

  x->height = get_updated_height(x);
  y->height = get_updated_height(y);

  return y;
}

// single right rotation
static Node *rotate_right(Node *y) {
  Node *x = y->left;
  Node *xr = x->right;

  x->right = y;
  y->left = xr;

  y->height = get_updated_height(y);
  x->height = get_updated_height(x);

  return x;
}

// perform the rotations if needed to balance the subtree
static Node *balance_node(Node *node) {
  node->height = get_updated_height(node);
  int balance = balance_factor(node);

  // case 1 - left left
  if (balance > 1 && balance_factor(node->left) >= 0) {
    // register memory access
    PRINT_LOG((long int)(node), sizeof(Node), 0, WRITE);

    return rotate_right(node);
  }

  // case 2 - right right
  if (balance < -1 && balance_factor(node->right) <= 0) {
    // register memory access
    PRINT_LOG((long int)(node), sizeof(Node), 0, WRITE);

    return rotate_left(node);
  }

  // case 3 - left right
  if (balance > 1 && balance_factor(node->left) < 0) {
    node->left = rotate_left(node->left);

    // register memory access
    PRINT_LOG((long int)(node), sizeof(Node), 0, WRITE);

    return rotate_right(node);
  }

  // case 4 - right left
  if (balance < -1 && balance_factor(node->right) > 0) {
    node->right = rotate_right(node->right);

    // register memory access
    PRINT_LOG((long int)(node), sizeof(Node), 0, WRITE);

    return rotate_left(node);
  }

  return node;
}

// insert a new node to the tree
Node *insert_node(Node *node, char type, const char *word,
                  const char *meaning) {
  // create a new node if it's node in the tree yet
  if (node == NULL) {
    Entry *entry = create_entry(type, word);
    add_meaning(entry, meaning);
    Node *new = create_node(entry);

    // register the memory access
    PRINT_LOG((long int)(new), sizeof(Node), 0, WRITE);

    return new;
  }

  // compare the target word with the node word
  int cmp = strcmp(word, node->entry->word);

  // go to left if is lower
  if (cmp < 0) {
    node->left = insert_node(node->left, type, word, meaning);

    // go to right if is higher
  } else if (cmp > 0) {
    node->right = insert_node(node->right, type, word, meaning);
  } else {
    // the word is already added
    // only add the meaning if the target type is equal the node type
    if (type == node->entry->type) {
      // register memory access
      PRINT_LOG((long int)(node), sizeof(Node), 0, READ);

      add_meaning(node->entry, meaning);
      return node;
    }
    // go to the right otherwise
    else {
      node->right = insert_node(node->right, type, word, meaning);
    }
  }

  // after insertion, balance the current node
  return balance_node(node);
}

// aux function to free a node pointer
static void _delete_node(Node **node) {
  // register memory access
  PRINT_LOG((long int)(*node), sizeof(node), 0, WRITE);

  delete_entry(&(*node)->entry);
  free(*node);
  *node = NULL;
}

// it returns the lower node in the given subtree
static Node *min_value_node(Node *node) {
  Node *current = node;
  while (current != NULL && current->left != NULL) {
    current = current->left;
  }

  return current;
}

// delete a target node and update the tree to maintain the structure
static Node *delete_node(Node *node, char type, const char *word) {
  if (node == NULL) {
    return NULL;
  }

  // compare the target word wit the node word
  int cmp = strcmp(word, node->entry->word);

  // go to the left if it's lower
  if (cmp < 0) {
    node->left = delete_node(node->left, type, word);

    // go to the right if it's higher
  } else if (cmp > 0) {
    node->right = delete_node(node->right, type, word);
  } else {
    // the target is found
    // perform deletion if the target type is equal de node type
    if (type == node->entry->type) {
      Node *tmp;
      // case 1 - 0 or 1 child
      if (node->left == NULL) {
        tmp = node->right;
        _delete_node(&node);
        return tmp;
      } else if (node->right == NULL) {
        tmp = node->left;
        _delete_node(&node);
        return tmp;
        // case 2 -  both child
      } else {
        tmp = min_value_node(node->right);

        // register memory access
        PRINT_LOG((long int)(tmp), sizeof(Node), 0, READ)

        delete_entry(&node->entry);
        node->entry = copy_entry(tmp->entry);
        node->right =
            delete_node(node->right, tmp->entry->type, tmp->entry->word);
      }

    }
    // go to the right otherwise
    else {
      node->right = delete_node(node->right, type, word);
    }
  }

  // after deletion, balance the current node
  return balance_node(node);
}

// delete all nodes with at least 1 meaning
Node *delete_not_empty(Node *node) {
  if (node == NULL) {
    return NULL;
  }

  node->left = delete_not_empty(node->left);
  node->right = delete_not_empty(node->right);

  if (node->entry->meanings_size > 0) {
    return delete_node(node, node->entry->type, node->entry->word);
  }

  return node;
}

// traverse the tree in order and call print each node entry
void fprint_tree(Node *node, FILE *file) {
  if (node != NULL) {
    fprint_tree(node->left, file);

    // register memory access
    PRINT_LOG((long int)(node), sizeof(Node), 0, READ);
    fprint_entry(node->entry, file);

    fprint_tree(node->right, file);
  }
}

// free every pointer in the tree
void delete_tree(Node **node) {
  if (*node != NULL) {
    delete_tree(&(*node)->left);
    delete_tree(&(*node)->right);

    // register memory access
    PRINT_LOG((long int)(*node), sizeof(Node), 0, WRITE);
    delete_entry(&(*node)->entry);
    free(*node);
    *node = NULL;
  }
}
