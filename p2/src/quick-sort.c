#include "quick-sort.h"
#include <stdlib.h>

// partition function to be used in many qs variations
void partition(Record *records, int left, int right, int *i, int *j) {
  Record middle, temp;
  *i = left;
  *j = right;

  middle = records[(*i + *j) / 2];
  copied++;

  do {
    while (middle.key > records[*i].key) {
      (*i)++;
      compared++;
    }
    compared++;

    while (middle.key < records[*j].key) {
      (*j)--;
      compared++;
    }
    compared++;

    if (*i <= *j) {
      temp = records[*i];
      records[*i] = records[*j];
      records[*j] = temp;
      (*i)++;
      (*j)--;

      copied += 3;
    }
  } while (*i <= *j);
}

// original version uses recursion and central pivot partition
void _quick_sort_rec(Record *records, int left, int right) {
  int i, j;
  partition(records, left, right, &i, &j);

  if (left < j)
    _quick_sort_rec(records, left, j);

  if (i < right)
    _quick_sort_rec(records, i, right);
}

// original version
void quick_sort_rec(Record *records, int n) {
  _quick_sort_rec(records, 0, n - 1);
}

void selection_sort(Record *records, int left, int right) {
  int i, j, min;
  Record temp;

  for (i = left; i < right - 1; i++) {
    min = i;

    for (j = i + 1; j < right; j++) {
      if (records[j].key < records[min].key) {
        min = j;
      }
      compared++;
    }
    temp = records[i];
    records[i] = records[min];
    records[min] = temp;

    copied += 3;
  }
}

// if the partition size is smaller than m than sort using selection sort
void _quick_sort_selection(Record *records, int left, int right, int m) {
  if ((right - left) <= m) {
    selection_sort(records, left, right + 1);
  } else {
    int i, j;
    partition(records, left, right, &i, &j);

    if (left < j)
      _quick_sort_selection(records, left, j, m);

    if (i < right)
      _quick_sort_selection(records, i, right, m);
  }
}

// variation that uses selection sort for partitions smaller than m
void quick_sort_selection(Record *records, int n, int m) {
  _quick_sort_selection(records, 0, n - 1, m);
}

// returns the median of k randomly chosen elements
int get_k_median(Record *records, int left, int right, int k) {
  int i, j, temp, min;
  int elements[k];

  int idx;
  for (i = 0; i < k; i++) {
    idx = left + (rand() % (right - left + 1));
    elements[i] = records[idx].key;
    copied++;
  }

  for (i = 0; i < k - 1; i++) {
    min = i;
    for (j = i + 1; j < k; j++) {
      compared++;
      if (elements[j] < elements[min]) {
        min = j;
      }
    }

    temp = elements[i];
    elements[i] = elements[min];
    elements[min] = temp;

    copied += 3;
  }

  return elements[k / 2];
}

// partition variation
// the pivot is the median of k randomly chosen elements
void partition_k_median(Record *records, int left, int right, int *i, int *j,
                        int k) {
  Record temp;
  *i = left;
  *j = right;

  int middle = get_k_median(records, left, right, k);

  do {
    while (middle > records[*i].key) {
      (*i)++;
      compared++;
    }
    compared++;

    while (middle < records[*j].key) {
      (*j)--;
      compared++;
    }
    compared++;

    if (*i <= *j) {
      temp = records[*i];
      records[*i] = records[*j];
      records[*j] = temp;
      (*i)++;
      (*j)--;

      copied += 3;
    }

  } while (*i <= *j);
}

// variation uses the partition with k median pivot
void _quick_sort_k_median(Record *records, int left, int right, int k) {
  int i, j;
  partition_k_median(records, left, right, &i, &j, k);

  if (left < j)
    _quick_sort_k_median(records, left, j, k);

  if (i < right)
    _quick_sort_k_median(records, i, right, k);
}

// k median variation
void quick_sort_k_median(Record *records, int n, int k) {
  _quick_sort_k_median(records, 0, n - 1, k);
}

// iterative version of quicksort
// it uses a stack instead of recursion
void quick_sort_iterative(Record *records, int n) {
  int i, j, left, right;
  int stack[n];
  int top = -1;

  stack[++top] = 0;
  stack[++top] = n - 1;

  while (top >= 0) {
    right = stack[top--];
    left = stack[top--];

    partition(records, left, right, &i, &j);

    if (left < j) {
      stack[++top] = left;
      stack[++top] = j;
    }

    if (i < right) {
      stack[++top] = i;
      stack[++top] = right;
    }
  }
}

// improved iterative version
// it processes the bigger partition first to improve the stack depth usage
void quick_sort_smart_stack(Record *records, int n) {
  int i, j, left, right;
  int stack[n];
  int top = 0;

  left = 0;
  right = n - 1;

  while (top >= 0) {
    if (right > left) {
      partition(records, left, right, &i, &j);

      if ((j - left) > (right - i)) {
        stack[++top] = left;
        stack[++top] = j;
        left = i;
      } else {
        stack[++top] = i;
        stack[++top] = right;
        right = j;
      }
    } else {
      right = stack[top--];
      left = stack[top--];
    }
  }
}
