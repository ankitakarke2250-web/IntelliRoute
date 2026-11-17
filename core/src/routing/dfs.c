/*
 * Depth First Search Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/routing.h"
#include "../include/graph.h"

/* DFS Helper */
void dfs_util(AdjacencyList* graph, int current, int target, int visited[], int parent[], RoutingResult* result) {
    visited[current] = 1;
    result->traversal[result->traversal_count++] = current;

    if (current == target) return;

    AdjListNode* neighbor = graph->array[current];
    while (neighbor) {
        if (!visited[neighbor->dest]) {
            parent[neighbor->dest] = current;
            dfs_util(graph, neighbor->dest, target, visited, parent, result);
        }
        neighbor = neighbor->next;
    }
}

/* DFS Algorithm */
RoutingResult dfs(AdjacencyList* graph, int start, int target) {
    RoutingResult result;
    memset(&result, 0, sizeof(RoutingResult));

    if (!graph || start >= graph->num_vertices || target >= graph->num_vertices) {
        return result;
    }

    int visited[MAX_ROUTERS] = {0};
    int parent[MAX_ROUTERS];
    for (int i = 0; i < MAX_ROUTERS; i++) parent[i] = -1;

    dfs_util(graph, start, target, visited, parent, &result);

    // Reconstruct path
    if (visited[target]) {
        int path[MAX_ROUTERS];
        int path_count = 0;
        int current = target;

        while (current != -1) {
            path[path_count++] = current;
            current = parent[current];
        }

        // Reverse path
        for (int i = 0; i < path_count; i++) {
            result.route[i] = path[path_count - 1 - i];
        }
        result.route_count = path_count;

        // Calculate total cost
        result.total_cost = 0;
        for (int i = 0; i < result.route_count - 1; i++) {
            AdjListNode* neighbor = graph->array[result.route[i]];
            while (neighbor) {
                if (neighbor->dest == result.route[i + 1]) {
                    result.total_cost += neighbor->weight;
                    break;
                }
                neighbor = neighbor->next;
            }
        }
    }

    return result;
}
