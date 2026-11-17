/*
 * Dijkstra's Algorithm Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../include/routing.h"
#include "../include/graph.h"

#define INF INT_MAX

/* Find minimum distance vertex */
int min_distance(int dist[], int visited[], int num_vertices) {
    int min = INF;
    int min_index = -1;

    for (int v = 0; v < num_vertices; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

/* Dijkstra's Algorithm */
RoutingResult dijkstra(AdjacencyList* graph, int start, int target) {
    RoutingResult result;
    memset(&result, 0, sizeof(RoutingResult));

    if (!graph || start >= graph->num_vertices || target >= graph->num_vertices) {
        return result;
    }

    int dist[MAX_ROUTERS];
    int visited[MAX_ROUTERS] = {0};
    int parent[MAX_ROUTERS];

    for (int i = 0; i < graph->num_vertices; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[start] = 0;

    for (int count = 0; count < graph->num_vertices - 1; count++) {
        int u = min_distance(dist, visited, graph->num_vertices);

        if (u == -1 || dist[u] == INF) break;

        visited[u] = 1;
        result.traversal[result.traversal_count++] = u;

        if (u == target) break;

        AdjListNode* neighbor = graph->array[u];
        while (neighbor) {
            if (!visited[neighbor->dest] && dist[u] != INF &&
                dist[u] + neighbor->weight < dist[neighbor->dest]) {
                dist[neighbor->dest] = dist[u] + neighbor->weight;
                parent[neighbor->dest] = u;
            }
            neighbor = neighbor->next;
        }
    }

    // Reconstruct path
    if (dist[target] != INF) {
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
        result.total_cost = dist[target];
    }

    return result;
}

/* Print routing result as JSON */
void print_routing_result_json(RoutingResult result) {
    printf("{");
    printf("\"success\": true,");
    printf("\"data\": {");
    printf("\"traversal\": [");
    for (int i = 0; i < result.traversal_count; i++) {
        if (i > 0) printf(",");
        printf("%d", result.traversal[i]);
    }
    printf("],");
    printf("\"route\": [");
    for (int i = 0; i < result.route_count; i++) {
        if (i > 0) printf(",");
        printf("%d", result.route[i]);
    }
    printf("],");
    printf("\"cost\": %d", result.total_cost);
    printf("}");
    printf("}");
}
