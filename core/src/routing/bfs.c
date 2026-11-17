/*
 * Breadth First Search Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/routing.h"
#include "../include/graph.h"

/* Queue for BFS */
typedef struct {
    int items[MAX_ROUTERS];
    int front;
    int rear;
} Queue;

Queue* create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int is_empty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_ROUTERS - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

int dequeue(Queue* q) {
    int item = q->items[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}

/* BFS Algorithm */
RoutingResult bfs(AdjacencyList* graph, int start, int target) {
    RoutingResult result;
    memset(&result, 0, sizeof(RoutingResult));

    if (!graph || start >= graph->num_vertices || target >= graph->num_vertices) {
        return result;
    }

    int visited[MAX_ROUTERS] = {0};
    int parent[MAX_ROUTERS];
    for (int i = 0; i < MAX_ROUTERS; i++) parent[i] = -1;

    Queue* q = create_queue();
    enqueue(q, start);
    visited[start] = 1;

    while (!is_empty(q)) {
        int current = dequeue(q);
        result.traversal[result.traversal_count++] = current;

        if (current == target) break;

        AdjListNode* neighbor = graph->array[current];
        while (neighbor) {
            if (!visited[neighbor->dest]) {
                visited[neighbor->dest] = 1;
                parent[neighbor->dest] = current;
                enqueue(q, neighbor->dest);
            }
            neighbor = neighbor->next;
        }
    }

    free(q);

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
