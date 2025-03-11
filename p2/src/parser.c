#include "parser.h"
#include "error-assert.h"
#include <unistd.h>

Params parse_arguments(int argc, char **argv) {
  Params p;
  error_assert((argc >= 2), "Usage: program <algorithm> [options]\n");

  p.alg_name = argv[1];

  int opt;

  while ((opt = getopt(argc, argv, "v:k:m:s:i:o:")) != -1) {
    switch (opt) {
    case 'v':
      p.version = atoi(optarg);
      break;
    case 'k':
      if (optarg) {
        p.k = atoi(optarg);
      } else {
        p.k = 3;
      }
      break;
    case 'm':
      if (optarg) {
        p.m = atoi(optarg);
      } else {
        p.m = 10;
      }
      break;
    case 's':
      p.seed = atoi(optarg);
      break;
    case 'i':
      p.input_file = optarg;
      break;
    case 'o':
      p.output_file = optarg;
      break;
    default:
      break;
    }
  }

  error_assert((p.input_file != NULL), "Missing Input File.");
  error_assert((p.output_file != NULL), "Missing Output File.");
  error_assert((p.seed > 0), "The seed must be informed.");
  error_assert((p.version > 0), "The version must be informed.");

  return p;
}
