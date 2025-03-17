#ifndef USAGE_H
#define USAGE_H

#include <sys/resource.h>

struct rusage set_usage();
double get_proc_time(const struct rusage *usage);

#endif
