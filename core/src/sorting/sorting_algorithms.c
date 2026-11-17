/*
 * Sorting Algorithms Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/sorting.h"

void copy_array(int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

/* Bubble Sort */
SortingResult bubble_sort(int arr[], int size) {
    SortingResult result;
    copy_array(arr, result.array, size);
    result.size = size;
    result.comparisons = 0;
    result.swaps = 0;

    clock_t start = clock();

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            result.comparisons++;
            if (result.array[j] > result.array[j + 1]) {
                int temp = result.array[j];
                result.array[j] = result.array[j + 1];
                result.array[j + 1] = temp;
                result.swaps++;
            }
        }
    }

    result.time_ms = ((double)(clock() - start) / CLOCKS_PER_SEC) * 1000;
    return result;
}

/* Selection Sort */
SortingResult selection_sort(int arr[], int size) {
    SortingResult result;
    copy_array(arr, result.array, size);
    result.size = size;
    result.comparisons = 0;
    result.swaps = 0;

    clock_t start = clock();

    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            result.comparisons++;
            if (result.array[j] < result.array[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = result.array[i];
            result.array[i] = result.array[min_idx];
            result.array[min_idx] = temp;
            result.swaps++;
        }
    }

    result.time_ms = ((double)(clock() - start) / CLOCKS_PER_SEC) * 1000;
    return result;
}

/* Insertion Sort */
SortingResult insertion_sort(int arr[], int size) {
    SortingResult result;
    copy_array(arr, result.array, size);
    result.size = size;
    result.comparisons = 0;
    result.swaps = 0;

    clock_t start = clock();

    for (int i = 1; i < size; i++) {
        int key = result.array[i];
        int j = i - 1;

        while (j >= 0 && result.array[j] > key) {
            result.comparisons++;
            result.array[j + 1] = result.array[j];
            result.swaps++;
            j--;
        }
        if (j >= 0) result.comparisons++;
        result.array[j + 1] = key;
    }

    result.time_ms = ((double)(clock() - start) / CLOCKS_PER_SEC) * 1000;
    return result;
}

/* Merge Sort Helper */
void merge(int arr[], int l, int m, int r, int* comparisons, int* swaps) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        (*comparisons)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        (*swaps)++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        (*swaps)++;
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        (*swaps)++;
        j++;
        k++;
    }
}

void merge_sort_util(int arr[], int l, int r, int* comparisons, int* swaps) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_util(arr, l, m, comparisons, swaps);
        merge_sort_util(arr, m + 1, r, comparisons, swaps);
        merge(arr, l, m, r, comparisons, swaps);
    }
}

/* Merge Sort */
SortingResult merge_sort(int arr[], int size) {
    SortingResult result;
    copy_array(arr, result.array, size);
    result.size = size;
    result.comparisons = 0;
    result.swaps = 0;

    clock_t start = clock();
    merge_sort_util(result.array, 0, size - 1, &result.comparisons, &result.swaps);
    result.time_ms = ((double)(clock() - start) / CLOCKS_PER_SEC) * 1000;

    return result;
}

/* Quick Sort Helper */
int partition(int arr[], int low, int high, int* comparisons, int* swaps) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        (*comparisons)++;
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            (*swaps)++;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    (*swaps)++;

    return i + 1;
}

void quick_sort_util(int arr[], int low, int high, int* comparisons, int* swaps) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons, swaps);
        quick_sort_util(arr, low, pi - 1, comparisons, swaps);
        quick_sort_util(arr, pi + 1, high, comparisons, swaps);
    }
}

/* Quick Sort */
SortingResult quick_sort(int arr[], int size) {
    SortingResult result;
    copy_array(arr, result.array, size);
    result.size = size;
    result.comparisons = 0;
    result.swaps = 0;

    clock_t start = clock();
    quick_sort_util(result.array, 0, size - 1, &result.comparisons, &result.swaps);
    result.time_ms = ((double)(clock() - start) / CLOCKS_PER_SEC) * 1000;

    return result;
}

/* Print sorting result as JSON */
void print_sorting_result_json(SortingResult result) {
    printf("{");
    printf("\"success\": true,");
    printf("\"data\": {");
    printf("\"original\": [");
    for (int i = 0; i < result.size; i++) {
        if (i > 0) printf(",");
        printf("%d", result.array[i]);
    }
    printf("],");
    printf("\"sorted\": [");
    for (int i = 0; i < result.size; i++) {
        if (i > 0) printf(",");
        printf("%d", result.array[i]);
    }
    printf("],");
    printf("\"comparisons\": %d,", result.comparisons);
    printf("\"swaps\": %d,", result.swaps);
    printf("\"time\": %.3f", result.time_ms);
    printf("}");
    printf("}");
}
