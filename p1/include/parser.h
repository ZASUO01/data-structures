#ifndef PARSER_H
#define PARSER_H

// Comand line params
typedef struct {
  char *input_file_name;
  int use_proc_usage;
} Params;

Params parse_arguments(int argc, char **argv);

#endif
