/*
 * Routing Wrapper Program
 * Accepts algorithm, source, destination, and graph data as command-line arguments
 * Outputs JSON result
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_ROUTERS 100
#define MAX_EDGES 500

/* Graph Edge */
typedef struct {
    int source;
    int dest;
    int cost;
} Edge;

/* Routing Result */
typedef struct {
    int traversal[MAX_ROUTERS];
    int traversal_count;
    int route[MAX_ROUTERS];
    int route_count;
    int total_cost;
} RoutingResult;

char* strdup(const char* s) {
    char* d = malloc(strlen(s) + 1);
    if (d == NULL) return NULL;
    strcpy(d, s);
    return d;
}

/* BFS Algorithm using array-based queue */
RoutingResult bfs(Edge edges[], int edge_count, int start, int target) {
    RoutingResult result;
    memset(&result, 0, sizeof(RoutingResult));

    if (start == target) {
        result.traversal[0] = start;
        result.traversal_count = 1;
        result.route[0] = start;
        result.route_count = 1;
        result.total_cost = 0;
        return result;
    }

    // Build adjacency matrix
    int adj[MAX_ROUTERS][MAX_ROUTERS] = {0};
    int costs[MAX_ROUTERS][MAX_ROUTERS] = {0};

    for (int i = 0; i < edge_count; i++) {
        int s = edges[i].source;
        int d = edges[i].dest;
        int c = edges[i].cost;
        if (s < MAX_ROUTERS && d < MAX_ROUTERS) {
            adj[s][d] = 1;
            adj[d][s] = 1;
            costs[s][d] = c;
            costs[d][s] = c;
        }
    }

    int visited[MAX_ROUTERS] = {0};
    int parent[MAX_ROUTERS];
    for (int i = 0; i < MAX_ROUTERS; i++) parent[i] = -1;

    // Simple array-based queue
    int queue[MAX_ROUTERS];
    int q_front = 0;
    int q_rear = 0;

    queue[q_rear++] = start;
    visited[start] = 1;

    int processed = 0;
    while (q_front < q_rear && processed < MAX_ROUTERS) {
        int current = queue[q_front++];
        result.traversal[result.traversal_count++] = current;
        processed++;

        for (int neighbor = 0; neighbor < MAX_ROUTERS; neighbor++) {
            if (adj[current][neighbor] && !visited[neighbor]) {
                visited[neighbor] = 1;
                parent[neighbor] = current;
                queue[q_rear++] = neighbor;
            }
        }
    }

    // Reconstruct path
    if (visited[target]) {
        int path[MAX_ROUTERS];
        int path_count = 0;
        int current = target;

        while (current != -1) {
            path[path_count++] = current;
            current = parent[current];
        }

        for (int i = 0; i < path_count; i++) {
            result.route[i] = path[path_count - 1 - i];
        }
        result.route_count = path_count;

        result.total_cost = 0;
        for (int i = 0; i < result.route_count - 1; i++) {
            result.total_cost += costs[result.route[i]][result.route[i + 1]];
        }
    }

    return result;
}

/* DFS Algorithm using recursion */
RoutingResult dfs(Edge edges[], int edge_count, int start, int target) {
    RoutingResult result;
    memset(&result, 0, sizeof(RoutingResult));

    if (start == target) {
        result.traversal[0] = start;
        result.traversal_count = 1;
        result.route[0] = start;
        result.route_count = 1;
        result.total_cost = 0;
        return result;
    }

    // Build adjacency matrix
    int adj[MAX_ROUTERS][MAX_ROUTERS] = {0};
    int costs[MAX_ROUTERS][MAX_ROUTERS] = {0};

    for (int i = 0; i < edge_count; i++) {
        int s = edges[i].source;
        int d = edges[i].dest;
        int c = edges[i].cost;
        if (s < MAX_ROUTERS && d < MAX_ROUTERS) {
            adj[s][d] = 1;
            adj[d][s] = 1;
            costs[s][d] = c;
            costs[d][s] = c;
        }
    }

    int visited[MAX_ROUTERS] = {0};
    int parent[MAX_ROUTERS];
    for (int i = 0; i < MAX_ROUTERS; i++) parent[i] = -1;

    int found = 0;
    int current_cost = 0;

    // DFS using stack
    int stack[MAX_ROUTERS];
    int cost_stack[MAX_ROUTERS];
    int top = -1;

    stack[++top] = start;
    cost_stack[top] = 0;
    visited[start] = 1;

    while (top >= 0) {
        int node = stack[top];
        int cost = cost_stack[top];
        top--;

        result.traversal[result.traversal_count++] = node;

        if (node == target) {
            found = 1;
            current_cost = cost;
            break;
        }

        // Push neighbors in reverse order for correct DFS
        for (int neighbor = MAX_ROUTERS - 1; neighbor >= 0; neighbor--) {
            if (adj[node][neighbor] && !visited[neighbor]) {
                visited[neighbor] = 1;
                parent[neighbor] = node;
                stack[++top] = neighbor;
                cost_stack[top] = cost + costs[node][neighbor];
            }
        }
    }

    // Reconstruct path
    if (found) {
        int path[MAX_ROUTERS];
        int path_count = 0;
        int current = target;

        while (current != -1) {
            path[path_count++] = current;
            current = parent[current];
        }

        for (int i = 0; i < path_count; i++) {
            result.route[i] = path[path_count - 1 - i];
        }
        result.route_count = path_count;
        result.total_cost = current_cost;
    }

    return result;
}

/* Dijkstra's Algorithm */
RoutingResult dijkstra(Edge edges[], int edge_count, int start, int target) {
    RoutingResult result;
    memset(&result, 0, sizeof(RoutingResult));

    if (start == target) {
        result.traversal[0] = start;
        result.traversal_count = 1;
        result.route[0] = start;
        result.route_count = 1;
        result.total_cost = 0;
        return result;
    }

    // Build adjacency matrix
    int adj[MAX_ROUTERS][MAX_ROUTERS] = {0};
    int costs[MAX_ROUTERS][MAX_ROUTERS];
    for (int i = 0; i < MAX_ROUTERS; i++) {
        for (int j = 0; j < MAX_ROUTERS; j++) {
            costs[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < edge_count; i++) {
        int s = edges[i].source;
        int d = edges[i].dest;
        int c = edges[i].cost;
        if (s < MAX_ROUTERS && d < MAX_ROUTERS) {
            adj[s][d] = 1;
            adj[d][s] = 1;
            costs[s][d] = c;
            costs[d][s] = c;
        }
    }

    int distances[MAX_ROUTERS];
    int visited[MAX_ROUTERS] = {0};
    int parent[MAX_ROUTERS];
    for (int i = 0; i < MAX_ROUTERS; i++) {
        distances[i] = INT_MAX;
        parent[i] = -1;
    }
    distances[start] = 0;

    for (int count = 0; count < MAX_ROUTERS - 1; count++) {
        int min_dist = INT_MAX;
        int u = -1;
        for (int v = 0; v < MAX_ROUTERS; v++) {
            if (!visited[v] && distances[v] < min_dist) {
                min_dist = distances[v];
                u = v;
            }
        }

        if (u == -1 || distances[u] == INT_MAX) break;
        visited[u] = 1;
        result.traversal[result.traversal_count++] = u;

        if (u == target) break;

        for (int v = 0; v < MAX_ROUTERS; v++) {
            if (adj[u][v] && !visited[v] && costs[u][v] != INT_MAX) {
                if (distances[u] + costs[u][v] < distances[v]) {
                    distances[v] = distances[u] + costs[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // Reconstruct path
    if (distances[target] != INT_MAX) {
        int path[MAX_ROUTERS];
        int path_count = 0;
        int current = target;

        while (current != -1) {
            path[path_count++] = current;
            current = parent[current];
        }

        for (int i = 0; i < path_count; i++) {
            result.route[i] = path[path_count - 1 - i];
        }
        result.route_count = path_count;
        result.total_cost = distances[target];
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

int main(int argc, char* argv[]) {
    if (argc < 5) {
        printf("{\"success\": false, \"error\": \"Usage: routing_wrapper <algorithm> <source> <destination> <edges>\"}");
        printf("\nEdges format: source1:dest1:cost1,source2:dest2:cost2,...");
        return 1;
    }

    char* algorithm = argv[1];
    int source = atoi(argv[2]);
    int destination = atoi(argv[3]);
    char* edges_str = argv[4];

    // Parse edges from string manually
    Edge edges[MAX_EDGES];
    int edge_count = 0;

    char* edges_copy = strdup(edges_str);
    char* token = edges_copy;

    while (token != NULL && edge_count < MAX_EDGES && *token != '\0') {
        // Find the end of this edge (comma or end of string)
        char* comma = strchr(token, ',');
        if (comma) {
            *comma = '\0';
        }

        // Parse source:dest:cost
        char* colon1 = strchr(token, ':');
        if (colon1) {
            *colon1 = '\0';
            char* colon2 = strchr(colon1 + 1, ':');
            if (colon2) {
                *colon2 = '\0';
                edges[edge_count].source = atoi(token);
                edges[edge_count].dest = atoi(colon1 + 1);
                edges[edge_count].cost = atoi(colon2 + 1);
                edge_count++;
            }
        }

        // Move to next edge
        if (comma) {
            token = comma + 1;
        } else {
            break;
        }
    }
    free(edges_copy);

    RoutingResult result;

    if (strcmp(algorithm, "bfs") == 0) {
        result = bfs(edges, edge_count, source, destination);
    } else if (strcmp(algorithm, "dfs") == 0) {
        result = dfs(edges, edge_count, source, destination);
    } else if (strcmp(algorithm, "dijkstra") == 0) {
        result = dijkstra(edges, edge_count, source, destination);
    } else {
        printf("{\"success\": false, \"error\": \"Unknown algorithm\"}");
        return 1;
    }

    print_routing_result_json(result);

    return 0;
}
