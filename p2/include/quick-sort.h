#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "metrics.h"
#include "record.h"

void quick_sort_rec(Record *records, int n);
void quick_sort_selection(Record *records, int n, int m);
void quick_sort_k_median(Record *records, int n, int k);
void quick_sort_iterative(Record *records, int n);
void quick_sort_smart_stack(Record *records, int n);

#endif
