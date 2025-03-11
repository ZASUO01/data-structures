#include "record.h"
#include <stdlib.h>

Record *generate_records(int n, int seed) {
  srand(seed);

  int i, j, k;
  Record *records = (Record *)malloc(n * sizeof(Record));

  if (!records) {
    return NULL;
  }

  const char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

  for (i = 0; i < n; i++) {
    records[i].key = rand() % n;

    for (j = 0; j < 15; j++) {
      records[i].chars[j] = charset[rand() % (sizeof(charset) - 1)];
    }

    for (k = 0; k < 10; k++) {
      records[i].reals[k] = (double)rand() / RAND_MAX * 100.0;
    }
  }

  return records;
}

void clean_records(Record *records) { free(records); }
