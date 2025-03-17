#include "parser.h"
#include "error-assert.h"
#include <unistd.h>

Params parse_arguments(int argc, char **argv) {
  Params p;

  int opt;
  p.input_file_name = NULL;
  p.use_proc_usage = 0;

  while ((opt = getopt(argc, argv, "i:p")) != -1) {
    switch (opt) {
    case 'i':
      p.input_file_name = optarg;
      break;
    case 'p':
      p.use_proc_usage = 1;
      break;
    default:
      break;
    }
  }

  // mandatory params
  error_assert((p.input_file_name != NULL), "Missing Input File.");

  return p;
}
