#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "avl-tree.h"
#include "entry.h"

// Linked list node with an Entry as the key
typedef struct ListNode {
  Entry *entry;
  struct ListNode *next;
} ListNode;

int get_hash_size(int input_size);
void init_hash_table(ListNode **hash_table, int hash_size);
void insert_list_node(ListNode **hash_table, int hash_size, char type,
                      const char *word, const char *meaning);
void print_hash_table(ListNode **hash_table, int hash_size);
void delete_not_empty_hash(ListNode **hash_table, int hash_size);
void delete_hash_table(ListNode **hash_table, int hash_size);

#endif
