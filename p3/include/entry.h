#ifndef ENTRY_H
#define ENTRY_H

typedef struct Entry {
  char type;         // [noun, verb, adjective]
  char *word;        // word stored
  char **meanings;   // word meanings list
  int meanings_size; // number of meanings currently stored
} Entry;

Entry *create_entry(char type, const char *word);
void add_meaning(Entry *entry, const char *meaning);
Entry *copy_entry(Entry *src);
void print_entry(Entry *entry);
void delete_entry(Entry **entry);

#endif
