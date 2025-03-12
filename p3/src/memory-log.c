#include "memory-log.h"
#include "error-assert.h"

MemoryLog ml;

// aux function set the time difference between t1 and t2
static void time_diff(struct timespec t1, struct timespec t2,
                      struct timespec *res) {
  if (t2.tv_nsec < t1.tv_nsec) {
    // adjust
    res->tv_nsec = 1000000000 + t2.tv_nsec - t1.tv_nsec;
    res->tv_sec = t2.tv_sec - t1.tv_sec - 1;
  } else {
    res->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    res->tv_sec = t2.tv_sec - t1.tv_sec;
  }
}

// initialize the logger
void init_memory_log(const char *file_name) {
  // set clock mode
  ml.clock_id = CLOCK_MONOTONIC;

  // define log file
  ml.log_file = fopen(file_name, "wt");
  error_assert((ml.log_file != NULL), "Failed to open log file");

  // get init time
  struct timespec tp;
  int result = clock_gettime(ml.clock_id, &tp);
  error_assert((result == 0), "Failed to get clock time");

  ml.init_time.tv_sec = tp.tv_sec;
  ml.init_time.tv_nsec = tp.tv_nsec;

  // init variable
  ml.count = 1;
  ml.phase = 0;
  ml.state = ACTIVE_ML;

  // log header
  result = fprintf(ml.log_file, "I %ld %ld.%.9ld\n", ml.count, tp.tv_sec,
                   tp.tv_nsec);
  error_assert((result >= 0), "Failed to write in the log file");
}

// aux functions to set ml variables
void activate_memory_log() { ml.state = ACTIVE_ML; }
void deactivate_memory_log() { ml.state = INACTIVE_ML; }
void set_next_log_phase() {
  if (ml.state == ACTIVE_ML) {
    ml.phase++;
  }
}

// print a line in the log file with the memory access info
void fprint_log(long int pos, long int size, int id, int type) {
  if (ml.state != ACTIVE_ML) {
    return;
  }

  error_assert((type == READ || type == WRITE || type == NAV),
               "Ivalid log type");

  struct timespec tp, tdif;
  int result = clock_gettime(ml.clock_id, &tp);
  error_assert((result == 0), "Failed to get clock time");

  // set the difference bettwen now and the initial time
  time_diff(ml.init_time, tp, &tdif);

  // update count;
  ml.count++;

  char log_type;
  switch (type) {
  case NAV:
    log_type = 'N';
    break;
  case READ:
    log_type = 'R';
    break;
  case WRITE:
    log_type = 'W';
    break;
  default:
    break;
  }

  // print record
  result =
      fprintf(ml.log_file, "%c %d %ld %d %ld.%.9ld %ld %ld\n", log_type,
              ml.phase, ml.count, id, tdif.tv_sec, tdif.tv_nsec, pos, size);
  error_assert((result >= 0), "Failed to write in the log file");
}

// finish the logger
void finish_memory_log() {
  // final metrics
  struct timespec tp, tdif;
  clock_gettime(ml.clock_id, &tp);

  // set the difference bettwen now and the initial time
  time_diff(ml.init_time, tp, &tdif);

  // update count
  ml.count++;

  // imprime registros finais
  fprintf(ml.log_file, "F %ld %ld.%.9ld %ld.%.9ld\n", ml.count, tp.tv_sec,
          tp.tv_nsec, tdif.tv_sec, tdif.tv_nsec);
  // deactivate ml
  ml.state = INACTIVE_ML;

  // close the log file
  int result = fclose(ml.log_file);
  error_assert((result == 0), "Failled to close the log file");
}
