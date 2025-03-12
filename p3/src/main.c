#include "avl-tree.h"
#include "error-assert.h"
#include "hash-table.h"
#include "memory-log.h"
#include "parser.h"
#include "usage.h"
#include <stdio.h>
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
  FILE *input_file = fopen(params.input_file_name, "r");
  error_assert((input_file != NULL), "Failed to open input file");

  // output file
  FILE *output_file = fopen(params.output_file_name, "w");
  error_assert((output_file != NULL), "Failed to open output file");

  // line values
  char line[MAX_LINE];
  char tmp_word[MAX_LINE];
  char tmp_meaning[MAX_LINE];
  char type;
  char *word = NULL;
  char *meaning = NULL;

  // logger usage
  if (params.use_logger) {
    error_assert((params.mem_file_name != NULL), "Missing log file.");
    init_memory_log(params.mem_file_name);
    set_next_log_phase();
  }

  double start_time;

  // process usage
  if (params.use_proc_usage) {
    struct rusage start_usage = set_usage();
    start_time = get_proc_time(&start_usage);
  }

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

        // insert the values into the tree
        tree = insert_node(tree, type, word, meaning);

        // reset variables
        word = NULL;
        meaning = NULL;
      }
    }

    // next operation
    set_next_log_phase();

    // print all entries
    fprintf(output_file, "AVL Tree: All Entries\n");
    fprintf(output_file, "\n");
    fprint_tree(tree, output_file);

    // next operation
    set_next_log_phase();

    // delete all entries with at least one meaning
    tree = delete_not_empty(tree);

    // next operation
    set_next_log_phase();

    // print all etries without meanings
    fprintf(output_file, "AVL Tree: Entries Without Meaning\n");
    fprintf(output_file, "\n");
    fprint_tree(tree, output_file);

    // next operation
    set_next_log_phase();

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

        // insert the values into the hash table
        insert_list_node(hash_table, hash_size, type, word, meaning);

        // reset variables
        word = NULL;
        meaning = NULL;
      }
    }

    // next operation
    set_next_log_phase();

    // print all entries
    fprintf(output_file, "Hash Table: All Entries\n");
    fprintf(output_file, "\n");
    fprint_hash_table(hash_table, hash_size, output_file);

    // next operation
    set_next_log_phase();

    // delete all entries with at least one meaning
    delete_not_empty_hash(hash_table, hash_size);

    // next operation
    set_next_log_phase();

    // print all etries without meanings
    fprintf(output_file, "Hash Table: Entries Without Meaning\n");
    fprintf(output_file, "\n");
    fprint_hash_table(hash_table, hash_size, output_file);

    // next operation
    set_next_log_phase();

    // free all the hash elements
    delete_hash_table(hash_table, hash_size);
  }

  // finish logger
  if (params.use_logger) {
    finish_memory_log();
  }

  // close opened files
  int closed = fclose(input_file);
  error_assert((closed == 0), "Failed to close the input file");

  closed = fclose(output_file);
  error_assert((closed == 0), "Failed to close the output file");

  // process usage
  if (params.use_proc_usage) {
    error_assert((params.usage_file_name != NULL), "Missing usage file.");

    struct rusage end_usage = set_usage();
    double end_time = get_proc_time(&end_usage);

    double total_time = end_time - start_time;

    FILE *usage_file = fopen(params.usage_file_name, "a");
    error_assert((usage_file != NULL), "Failed to open usage file");

    fprintf(usage_file, "%f\n", total_time);

    closed = fclose(usage_file);
    error_assert((closed == 0), "Failed to close the usge file");
  }

  return 0;
}
