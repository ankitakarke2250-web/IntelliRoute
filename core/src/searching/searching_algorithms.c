/*
 * Searching Algorithms Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/searching.h"

/* Linear Search */
SearchResult linear_search(int arr[], int size, int element) {
    SearchResult result;
    result.found = 0;
    result.position = -1;
    result.comparisons = 0;

    for (int i = 0; i < size; i++) {
        result.comparisons++;
        if (arr[i] == element) {
            result.found = 1;
            result.position = i;
            break;
        }
    }

    return result;
}

/* Binary Search */
SearchResult binary_search(int arr[], int size, int element) {
    SearchResult result;
    result.found = 0;
    result.position = -1;
    result.comparisons = 0;

    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        result.comparisons++;

        if (arr[mid] == element) {
            result.found = 1;
            result.position = mid;
            return result;
        }

        if (arr[mid] < element) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return result;
}

/* Print search result as JSON */
void print_search_result_json(SearchResult result) {
    printf("{");
    printf("\"success\": true,");
    printf("\"data\": {");
    printf("\"found\": %s,", result.found ? "true" : "false");
    printf("\"position\": %d,", result.position);
    printf("\"comparisons\": %d", result.comparisons);
    printf("}");
    printf("}");
}
