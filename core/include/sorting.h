/*
 * Sorting Algorithms Header
 */

#ifndef SORTING_H
#define SORTING_H

#include "common.h"

/* Sorting Result */
typedef struct {
    int array[MAX_ARRAY_SIZE];
    int size;
    int comparisons;
    int swaps;
    double time_ms;
} SortingResult;

/* Sorting Algorithms */
SortingResult bubble_sort(int arr[], int size);
SortingResult selection_sort(int arr[], int size);
SortingResult insertion_sort(int arr[], int size);
SortingResult merge_sort(int arr[], int size);
SortingResult quick_sort(int arr[], int size);

/* Utility Functions */
void print_sorting_result_json(SortingResult result);
void copy_array(int source[], int dest[], int size);

#endif /* SORTING_H */
