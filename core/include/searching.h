/*
 * Searching Algorithms Header
 */

#ifndef SEARCHING_H
#define SEARCHING_H

#include "common.h"

/* Search Result */
typedef struct {
    int found;
    int position;
    int comparisons;
} SearchResult;

/* Searching Algorithms */
SearchResult linear_search(int arr[], int size, int element);
SearchResult binary_search(int arr[], int size, int element);

/* Utility Functions */
void print_search_result_json(SearchResult result);

#endif /* SEARCHING_H */
