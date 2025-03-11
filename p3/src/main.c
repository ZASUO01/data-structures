#include "avl-tree.h"
#include "error-assert.h"
#include "hash-table.h"
#include "parser.h"
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

// aux function to remove possible line breaks in a string
void remove_line_breaks(char *line) {
  for (int i = 0; line[i] != '\0'; i++) {
    if (line[i] == '\n') {
      line[i] = '\0';
      break;
    }
  }
}

int main(int argc, char **argv) {
  // read comand line arguments
  Params params = parse_arguments(argc, argv);

  // input file
  FILE *input_file = fopen(params.input_file, "r");
  error_assert((input_file != NULL), "Failed to open input file");

  // output file
  FILE *output_file = fopen(params.output_file, "w");
  error_assert((output_file != NULL), "Failed to open output file");

  // line values
  char line[MAX_LINE];
  char tmp_word[MAX_LINE];
  char tmp_meaning[MAX_LINE];
  char type;
  char *word = NULL;
  char *meaning = NULL;

  if (strcmp(params.struct_name, "tree") == 0) {
    // init tree root
    Node *tree = NULL;

    // read file lines
    while (fgets(line, sizeof(line), input_file)) {
      // remove possible line breaks
      remove_line_breaks(line);

      // parse the line
      const char *expression = "%c [%255[^]]] %255[^\n]";
      int sc = sscanf(line, expression, &type, tmp_word, tmp_meaning);

      // parse success
      if (sc >= 2) {
        word = strdup(tmp_word);

        // the meaning is optional in the line
        if (sc > 2) {
          meaning = strdup(tmp_meaning);
        }

        tree = insert_node(tree, type, word, meaning);
      }
    }

    // print all entries
    print_tree(tree);

    // delete all entries with at least one meaning
    tree = delete_not_empty(tree);

    // print all etries without meanings
    print_tree(tree);

    // free all the tree nodes
    delete_tree(&tree);
  } else if (strcmp(params.struct_name, "hash") == 0) {
    // get hash size based on input size
    int hash_size = get_hash_size(params.input_size);

    // delcare the hash table
    ListNode *hash_table[hash_size];

    // init the hash table elements
    init_hash_table(hash_table, hash_size);

    // read file lines
    while (fgets(line, sizeof(line), input_file)) {
      // remove possible line breaks
      remove_line_breaks(line);

      // parse the line
      const char *expression = "%c [%255[^]]] %255[^\n]";
      int sc = sscanf(line, expression, &type, tmp_word, tmp_meaning);

      // parse success
      if (sc >= 2) {
        word = strdup(tmp_word);

        // the meaning is optional in the line
        if (sc > 2) {
          meaning = strdup(tmp_meaning);
        }

        insert_list_node(hash_table, hash_size, type, word, meaning);
      }
    }
    // print all entries
    print_hash_table(hash_table, hash_size);

    // delete all entries with at least one meaning
    delete_not_empty_hash(hash_table, hash_size);

    // print all etries without meanings
    print_hash_table(hash_table, hash_size);

    // free all the hash elements
    delete_hash_table(hash_table, hash_size);
  }

  // close opened files
  fclose(input_file);
  fclose(output_file);
  return 0;
}
