#ifndef RECORD_H
#define RECORD_H

typedef struct {
  int key;
  char chars[15];
  double reals[10];
} Record;

Record *generate_records(int n, int seed);
void clean_records(Record *records);

#endif
