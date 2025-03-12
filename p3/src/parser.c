#include "parser.h"
#include "error-assert.h"
#include <bits/getopt_core.h>
#include <unistd.h>

Params parse_arguments(int argc, char **argv) {
  Params p;
  error_assert((argc >= 2), "Missing params.\n");

  int opt;
  p.input_file_name = NULL;
  p.output_file_name = NULL;
  p.struct_name = NULL;
  p.mem_file_name = NULL;
  p.input_size = 0;
  p.use_logger = 0;

  while ((opt = getopt(argc, argv, "i:o:t:s:m:l")) != -1) {
    switch (opt) {
    case 'i':
      p.input_file_name = optarg;
      break;
    case 'o':
      p.output_file_name = optarg;
      break;
    case 't':
      p.struct_name = optarg;
      break;
    case 's':
      if (optarg) {
        p.input_size = atoi(optarg);
      }
      break;
    case 'm':
      if (optarg) {
        p.mem_file_name = optarg;
      }
      break;
    case 'l':
      p.use_logger = 1;
      break;
    default:
      break;
    }
  }

  // mandatory params
  error_assert((p.input_file_name != NULL), "Missing Input File.");
  error_assert((p.output_file_name != NULL), "Missing Output File.");
  error_assert((p.struct_name != NULL), "The structure name must be informed.");

  return p;
}
