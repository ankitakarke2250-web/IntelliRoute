/*
 * Searching Wrapper Program
 * Accepts algorithm, array, and element as command-line arguments
 * Outputs JSON result
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_SIZE 1000

/* Search Result */
typedef struct {
    int found;
    int position;
    int comparisons;
} SearchResult;

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
            result.position = i + 1;  // Position is 1-based (index + 1)
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

    // Binary search requires sorted array - check if array is sorted
    int is_sorted = 1;
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            is_sorted = 0;
            break;
        }
    }

    // If not sorted, sort it first
    int sorted_arr[MAX_ARRAY_SIZE];
    for (int i = 0; i < size; i++) {
        sorted_arr[i] = arr[i];
    }

    if (!is_sorted) {
        // Simple bubble sort for the array
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (sorted_arr[j] > sorted_arr[j + 1]) {
                    int temp = sorted_arr[j];
                    sorted_arr[j] = sorted_arr[j + 1];
                    sorted_arr[j + 1] = temp;
                }
            }
        }
    }

    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        result.comparisons++;

        if (sorted_arr[mid] == element) {
            result.found = 1;
            result.position = mid + 1;  // Position is 1-based (index + 1)
            return result;
        }

        if (sorted_arr[mid] < element) {
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

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("{\"success\": false, \"error\": \"Usage: search_wrapper <algorithm> <array> <element>\"}");
        return 1;
    }

    char* algorithm = argv[1];
    char* array_str = argv[2];
    int element = atoi(argv[3]);

    // Parse array from string (comma-separated)
    int array[MAX_ARRAY_SIZE];
    int size = 0;

    char* token = strtok(array_str, ",");
    while (token != NULL && size < MAX_ARRAY_SIZE) {
        array[size++] = atoi(token);
        token = strtok(NULL, ",");
    }

    SearchResult result;

    if (strcmp(algorithm, "linear") == 0) {
        result = linear_search(array, size, element);
    } else if (strcmp(algorithm, "binary") == 0) {
        result = binary_search(array, size, element);
    } else {
        printf("{\"success\": false, \"error\": \"Unknown algorithm\"}");
        return 1;
    }

    print_search_result_json(result);

    return 0;
}
