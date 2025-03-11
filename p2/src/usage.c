#include "usage.h"
#include "error-assert.h"

struct rusage set_usage() {
  struct rusage usage;
  int rc;

  rc = getrusage(RUSAGE_SELF, &usage);
  error_assert((rc == 0), "getrusage failed.");

  return usage;
}

double get_proc_time(const struct rusage *usage) {
  double stime = (double)usage->ru_stime.tv_sec;
  double stimeu = (double)usage->ru_stime.tv_usec / 1e6;
  double utime = (double)usage->ru_utime.tv_sec;
  double utimeu = (double)usage->ru_utime.tv_usec / 1e6;

  return (utime + utimeu + stime + stimeu);
}
