#ifndef PARSER_H
#define PARSER_H

#define QUICKSORT "quicksort"
#define MERGESORT "mergesort"
#define HEAPSORT "heapsort"

typedef struct {
  char *alg_name;
  char *input_file;
  char *output_file;
  int version;
  int seed;
  int k;
  int m;
} Params;

Params parse_arguments(int argc, char **argv);

#endif
