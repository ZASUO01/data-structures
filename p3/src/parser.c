#include "parser.h"
#include "error-assert.h"
#include <bits/getopt_core.h>
#include <unistd.h>

Params parse_arguments(int argc, char **argv) {
  Params p;
  error_assert((argc >= 2), "Missing params.\n");

  int opt;

  while ((opt = getopt(argc, argv, "i:o:t:s:")) != -1) {
    switch (opt) {
    case 'i':
      p.input_file = optarg;
      break;
    case 'o':
      p.output_file = optarg;
      break;
    case 't':
      p.struct_name = optarg;
      break;
    case 's':
      if (optarg) {
        p.input_size = atoi(optarg);
      } else {
        p.input_size = 0;
      }
      break;
    default:
      break;
    }
  }

  // mandatory params
  error_assert((p.input_file != NULL), "Missing Input File.");
  error_assert((p.output_file != NULL), "Missing Output File.");
  error_assert((p.struct_name != NULL), "The structure name must be informed.");

  return p;
}
