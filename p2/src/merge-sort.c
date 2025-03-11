#include "merge-sort.h"
#include "error-assert.h"
#include <stdlib.h>

// merge two sublists in a sorted list
void merge(Record *records, int left, int mid, int right) {
  // size of sublists
  int nl = (mid - left) + 1;
  int nr = right - mid;

  // creating temporary sublists
  Record *values_l = (Record *)malloc(nl * sizeof(Record));
  Record *values_r = (Record *)malloc(nr * sizeof(Record));

  error_assert((values_l != NULL && values_r != NULL),
               "Failed to allocate memory.\n");

  int i, j, k;

  for (i = 0; i < nl; i++) {
    values_l[i] = records[left + i];
    copied++;
  }

  for (j = 0; j < nr; j++) {
    values_r[j] = records[mid + 1 + j];
    copied++;
  }

  i = 0, j = 0, k = left;

  // merge temp sublists in the original list
  while (i < nl && j < nr) {
    if (values_l[i].key < values_r[j].key) {
      records[k] = values_l[i];
      copied++;

      i++;
    } else {
      records[k] = values_r[j];
      copied++;

      j++;
    }
    k++;
    compared++;
  }

  // copy the rest elements of left sublist
  while (i < nl) {
    records[k] = values_l[i];
    copied++;

    i++;
    k++;
  }

  // copy the rest elements of right sublist
  while (j < nr) {
    records[k] = values_r[j];
    copied++;

    j++;
    k++;
  }

  free(values_l);
  free(values_r);
}

// divide the list in two lists until there's one single element in each
//  sort the single lists
//  Merge the two lists
void _merge_sort(Record *records, int left, int right) {
  // if there's more than one element, then divide
  if (left < right) {
    int mid = left + ((right - left) / 2);

    // left sublist
    _merge_sort(records, left, mid);

    // right sublist
    _merge_sort(records, mid + 1, right);

    // merge both
    merge(records, left, mid, right);
  }
}

void merge_sort(Record *records, int n) { _merge_sort(records, 0, n - 1); }
