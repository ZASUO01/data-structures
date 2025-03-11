#ifndef PARSER_H
#define PARSER_H

// Comand line params
typedef struct {
  char *input_file;
  char *output_file;
  char *struct_name;
  int input_size;
} Params;

Params parse_arguments(int argc, char **argv);

#endif
