#include "hash-table.h"
#include "error-assert.h"
#include "memory-log.h"
#include "stdlib.h"
#include <string.h>

// create, init and return a new node
static ListNode *create_list_node(Entry *entry) {
  // allocate required memory
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  error_assert((node != NULL), "Failed to allocate memory");

  // init values
  node->entry = entry;
  node->next = NULL;

  return node;
}

// hash function that transforms the key into an index
static int hash(const char *word, int hash_size) {
  int index = 0;
  const char *p = &word[0];
  while (*p != '\0') {
    index += (int)*p;
    ++p;
  }

  return index % hash_size;
}

// experimental value: 0.6 <=input_size / hash_size <= 0.75
int get_hash_size(int input_size) { return (int)(input_size / 0.75); }

// init the list values
void init_hash_table(ListNode **hash_table, int hash_size) {
  for (int i = 0; i < hash_size; i++) {
    hash_table[i] = NULL;
  }
}

// insert function
void insert_list_node(ListNode **hash_table, int hash_size, char type,
                      const char *word, const char *meaning) {
  // index based on the target word
  int index = hash(word, hash_size);

  // head of the linked list at this index
  ListNode *current = hash_table[index];

  // walk in the linked list
  while (current != NULL) {
    // if the word and type are found, then just add the new meaning
    if (strcmp(word, current->entry->word) == 0 &&
        type == current->entry->type) {
      // register memory access
      PRINT_LOG((long int)(current), sizeof(ListNode), 0, READ);

      add_meaning(current->entry, meaning);
      return;
    }
    current = current->next;
  }

  // otherwise add a new node
  Entry *entry = create_entry(type, word);
  add_meaning(entry, meaning);
  current = create_list_node(entry);

  current->next = hash_table[index];
  hash_table[index] = current;

  // record the memory writing
  PRINT_LOG((long int)(current), sizeof(ListNode *), 0, WRITE);
}

// returns a single list with the copy of all elements in the hash table
static ListNode **get_full_list(ListNode **hash_table, int hash_size,
                                int *list_size) {
  int i, j;
  int nodes_num = 0;
  ListNode *current;

  // get the number of elements in the hash table
  for (i = 0; i < hash_size; i++) {
    current = hash_table[i];
    while (current != NULL) {
      nodes_num++;
      current = current->next;
    }
  }

  // allocate the required memory for that number
  ListNode **full_list = (ListNode **)malloc(nodes_num * sizeof(ListNode *));
  error_assert((full_list != NULL), "Failed to allocate memory.");

  // this value is needed out of this scope
  *list_size = nodes_num;

  // copy the hash elements to the new list
  nodes_num = 0;
  for (i = 0; i < hash_size; i++) {
    current = hash_table[i];
    while (current != NULL) {
      Entry *entry = create_entry(current->entry->type, current->entry->word);
      for (j = 0; j < current->entry->meanings_size; j++) {
        add_meaning(entry, current->entry->meanings[j]);
      }

      full_list[nodes_num++] = create_list_node(entry);

      // register memory access
      PRINT_LOG((long int)(full_list[nodes_num - 1]), sizeof(ListNode), 0,
                WRITE);

      current = current->next;
    }
  }

  return full_list;
}

// aux function to be used in qsort alg
static int compare(const void *a, const void *b) {
  ListNode *_a = *(ListNode **)a;
  ListNode *_b = *(ListNode **)b;

  int cmp = strcmp(_a->entry->word, _b->entry->word);
  if (cmp == 0) {
    return _a->entry->type - _b->entry->type;
  } else {
    return cmp;
  }
}

// print all elements in alfabetical order
void fprint_hash_table(ListNode **hash_table, int hash_size, FILE *file) {
  int list_size;

  // get a single list with all the hash table elements
  ListNode **full_list = get_full_list(hash_table, hash_size, &list_size);

  // sort the list in ascending order of the words
  qsort(full_list, list_size, sizeof(ListNode *), compare);

  // print and clean the elements
  for (int i = 0; i < list_size; i++) {
    // register memory access
    PRINT_LOG((long int)(full_list[i]), sizeof(ListNode), 0, READ);

    fprint_entry(full_list[i]->entry, file);
    delete_entry(&full_list[i]->entry);
    free(full_list[i]);
  }

  free(full_list);
}

// delete all the elements that have at least 1 meaning
void delete_not_empty_hash(ListNode **hash_table, int hash_size) {
  for (int i = 0; i < hash_size; i++) {
    ListNode *current = hash_table[i];
    ListNode *prev = NULL;
    ListNode *target;

    // walk in the linked list
    while (current != NULL) {
      // case there's at least 1 meaning
      if (current->entry->meanings_size > 0) {
        target = current;

        // case the current node is the head
        if (prev == NULL) {
          hash_table[i] = current->next;

        } else {
          prev->next = current->next;
        }

        // move the pointer to the next
        current = current->next;

        // register memory access
        PRINT_LOG((long int)(target), sizeof(ListNode), 0, WRITE);

        // delete the current
        delete_entry(&target->entry);
        free(target);
      }
      // otherwise just move next
      else {
        prev = current;
        current = current->next;
      }
    }
  }
}

// clean all space allocated in the hash table
void delete_hash_table(ListNode **hash_table, int hash_size) {
  for (int i = 0; i < hash_size; i++) {
    ListNode *current = hash_table[i];
    ListNode *next;

    while (current != NULL) {
      next = current->next;

      // register memory access
      PRINT_LOG((long int)(current), sizeof(ListNode), 0, WRITE);
      delete_entry(&current->entry);
      free(current);

      current = next;
    }
  }
}
