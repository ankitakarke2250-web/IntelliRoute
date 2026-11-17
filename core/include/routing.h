/*
 * Routing Algorithms Header
 * BFS, DFS, and Dijkstra implementations
 */

#ifndef ROUTING_H
#define ROUTING_H

#include "common.h"
#include "graph.h"

/* BFS Result */
typedef struct {
    int traversal[MAX_ROUTERS];
    int traversal_count;
    int route[MAX_ROUTERS];
    int route_count;
    int total_cost;
} RoutingResult;

/* BFS Algorithm */
RoutingResult bfs(AdjacencyList* graph, int start, int target);

/* DFS Algorithm */
RoutingResult dfs(AdjacencyList* graph, int start, int target);

/* Dijkstra's Algorithm */
RoutingResult dijkstra(AdjacencyList* graph, int start, int target);

/* Utility Functions */
void print_routing_result_json(RoutingResult result);

#endif /* ROUTING_H */
