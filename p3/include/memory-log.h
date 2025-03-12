#ifndef MEMORY_LOG_H
#define MEMORY_LOG_H

#include <stdio.h>
#include <time.h>

typedef struct {
  FILE *log_file;
  clockid_t clock_id;
  struct timespec init_time;
  long int count;
  int phase;
  int state;
} MemoryLog;

// to be used in main function
extern MemoryLog ml;

// states definition
#define ACTIVE_ML 1
#define INACTIVE_ML 0

#define READ 0
#define WRITE 1
#define NAV 2

// macro for performance
#define PRINT_LOG(pos, sz, id, tp)                                             \
  ((void)((ml.state == ACTIVE_ML) ? fprint_log(pos, sz, id, tp) : 0));

void init_memory_log(const char *file_name);
void activate_memory_log();
void deactivate_memory_log();
void set_next_log_phase();
void fprint_log(long int pos, long int size, int id, int type);
void finish_memory_log();

#endif
