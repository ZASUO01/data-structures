#include "entry.h"
#include "error-assert.h"
#include <stdlib.h>
#include <string.h>

// returns a new entry pointer
Entry *create_entry(char type, const char *word) {
  // allocate memory for an entry
  Entry *entry = (Entry *)malloc(sizeof(Entry));
  error_assert((entry != NULL), "Failed to allocate memory.");

  // init values
  entry->type = type;
  entry->word = strdup(word);

  // allocate list of meanings
  entry->meanings = (char **)malloc(sizeof(char *));
  error_assert((entry->meanings != NULL), "Failed to allocate memory.");

  // init the list as empty
  entry->meanings_size = 0;

  return entry;
}

// add a meaning to the list
void add_meaning(Entry *entry, const char *meaning) {
  // check to prevent NULL meaning
  if (meaning) {
    // reallocate memory for new adition
    entry->meanings = (char **)realloc(
        entry->meanings, (entry->meanings_size + 1) * sizeof(char *));
    error_assert((entry->meanings != NULL), "Failed to allocate memory.");

    // add to the list and increase the list size;
    entry->meanings[entry->meanings_size] = strdup(meaning);
    entry->meanings_size++;
  }
}

// copy the content of an entry and return it
Entry *copy_entry(Entry *src) {
  // it should have been initialized before
  if (src == NULL) {
    return NULL;
  }

  // create a new entry to receive the copy data
  Entry *copy = create_entry(src->type, src->word);
  for (int i = 0; i < src->meanings_size; i++) {
    add_meaning(copy, src->meanings[i]);
  }

  return copy;
}

// print the entry values and meanings in insert order
void print_entry(Entry *entry) {
  printf("%s (%c)\n", entry->word, entry->type);

  for (int i = 0; i < entry->meanings_size; i++) {
    printf("%d. %s\n", i + 1, entry->meanings[i]);
  }
}

// free memory and clean all pointers
void delete_entry(Entry **entry) {
  if (!entry || !(*entry)) {
    return;
  }

  free((*entry)->word);
  (*entry)->word = NULL;

  for (int i = 0; i < (*entry)->meanings_size; i++) {
    free((*entry)->meanings[i]);
    (*entry)->meanings[i] = NULL;
  }

  free((*entry)->meanings);
  (*entry)->meanings = NULL;

  free((*entry));
  *entry = NULL;
}
