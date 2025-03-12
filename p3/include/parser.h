#ifndef PARSER_H
#define PARSER_H

// Comand line params
typedef struct {
  char *input_file_name;
  char *output_file_name;
  char *struct_name;
  char *mem_file_name;
  int input_size;
  int use_logger;
} Params;

Params parse_arguments(int argc, char **argv);

#endif
