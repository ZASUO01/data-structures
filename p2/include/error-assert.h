#ifndef ERROR_ASSERT_H
#define ERROR_ASSERT_H

#include <stdio.h>
#include <stdlib.h>

#define warning_assert(err, msg)                                               \
  ((void)((err) ? 0 : __warning_assert(#err, __FILE__, __LINE__, msg)))

#define __warning_assert(err, file, line, msg)                                 \
  ((void)fprintf(stderr, "%s:%u: Warning: '%s' - %s\n", file, line, err, msg))

#define error_assert(err, msg)                                                 \
  ((void)((err) ? 0 : __error_assert(#err, __FILE__, __LINE__, msg)))

#define __error_assert(err, file, line, msg)                                   \
  ((void)fprintf(stderr, "%s:%u: Error: '%s' - %s\n", file, line, err, msg),   \
   exit(EXIT_FAILURE))

#endif
