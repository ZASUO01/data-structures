#include "heap-sort.h"

// build the heap from a source index
void build_heap(Record *records, int i, int n) {
  // left node index
  int j = (i * 2) + 1;

  // current node
  Record x = records[i];
  copied++;

  // while j is a child node
  while (j <= n) {
    // if there's a right node check if it is greater than the left
    if (j < n) {
      if (records[j].key < records[j + 1].key) {
        j++;
      }
      compared++;
    }

    // stop checking if the current node is greater than the greater child
    compared++;
    if (x.key >= records[j].key) {
      break;
    }

    // swap the child otherwise
    records[i] = records[j];
    i = j;
    j = (i * 2) + 1;
    copied++;
  }
  records[i] = x;
  copied++;
}

// build the heap to get the greater element at the first position
// move it to the last position
// do it n - 1 times
void heap_sort(Record *records, int n) {
  int i;
  Record tmp;

  // build the heap form each parent node
  for (i = (n / 2) - 1; i >= 0; i--) {
    build_heap(records, i, n - 1);
  }

  // swap the fist and the last until the list is sorted
  for (i = n - 1; i > 0; i--) {
    tmp = records[0];
    records[0] = records[i];
    records[i] = tmp;

    copied += 3;

    build_heap(records, 0, i - 1);
  }
}
