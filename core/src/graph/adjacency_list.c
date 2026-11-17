/*
 * Adjacency List Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/graph.h"

/* Create new adjacency list node */
AdjListNode* new_adj_list_node(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (newNode) {
        newNode->dest = dest;
        newNode->weight = weight;
        newNode->next = NULL;
    }
    return newNode;
}

/* Create adjacency list */
AdjacencyList* create_adj_list(int num_vertices) {
    AdjacencyList* adj = (AdjacencyList*)malloc(sizeof(AdjacencyList));
    if (!adj) return NULL;

    adj->num_vertices = num_vertices;

    // Initialize each adjacency list as empty
    for (int i = 0; i < num_vertices; i++) {
        adj->array[i] = NULL;
    }

    return adj;
}

/* Free adjacency list */
void free_adj_list(AdjacencyList* adj) {
    if (!adj) return;

    for (int i = 0; i < adj->num_vertices; i++) {
        AdjListNode* current = adj->array[i];
        while (current) {
            AdjListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(adj);
}

/* Add edge to adjacency list */
void add_edge_list(AdjacencyList* adj, int src, int dest, int weight) {
    if (!adj || src >= adj->num_vertices || dest >= adj->num_vertices) return;

    // Add edge from src to dest
    AdjListNode* newNode = new_adj_list_node(dest, weight);
    newNode->next = adj->array[src];
    adj->array[src] = newNode;

    // Since graph is undirected, add edge from dest to src
    newNode = new_adj_list_node(src, weight);
    newNode->next = adj->array[dest];
    adj->array[dest] = newNode;
}

/* Remove edge from adjacency list */
void remove_edge_list(AdjacencyList* adj, int src, int dest) {
    if (!adj || src >= adj->num_vertices || dest >= adj->num_vertices) return;

    // Remove src -> dest
    AdjListNode* current = adj->array[src];
    AdjListNode* prev = NULL;

    while (current) {
        if (current->dest == dest) {
            if (prev) {
                prev->next = current->next;
            } else {
                adj->array[src] = current->next;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }

    // Remove dest -> src (undirected)
    current = adj->array[dest];
    prev = NULL;

    while (current) {
        if (current->dest == src) {
            if (prev) {
                prev->next = current->next;
            } else {
                adj->array[dest] = current->next;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
}

/* Check if edge exists */
int has_edge_list(AdjacencyList* adj, int src, int dest) {
    if (!adj || src >= adj->num_vertices || dest >= adj->num_vertices) return 0;

    AdjListNode* current = adj->array[src];
    while (current) {
        if (current->dest == dest) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

/* Display adjacency list */
void display_adj_list(AdjacencyList* adj) {
    if (!adj) return;

    printf("=== Adjacency List ===\n");
    for (int i = 0; i < adj->num_vertices; i++) {
        printf("%d -> ", i);
        AdjListNode* current = adj->array[i];
        while (current) {
            printf("%d (w:%d) ", current->dest, current->weight);
            current = current->next;
        }
        printf("\n");
    }
    printf("=====================\n");
}

/* Print adjacency list as JSON */
void print_adj_list_json(AdjacencyList* adj) {
    if (!adj) {
        printf("[]");
        return;
    }

    printf("[");
    for (int i = 0; i < adj->num_vertices; i++) {
        if (i > 0) printf(",");
        printf("{\"node\": %d, \"neighbors\": [", i);

        AdjListNode* current = adj->array[i];
        int first = 1;
        while (current) {
            if (!first) printf(",");
            printf("{\"dest\": %d, \"weight\": %d}", current->dest, current->weight);
            first = 0;
            current = current->next;
        }

        printf("]}");
    }
    printf("]");
}

/* Print link as JSON */
void print_link_json(Link link) {
    printf("{\"id\": %d, \"source\": %d, \"destination\": %d, \"cost\": %d}",
           link.id, link.source, link.destination, link.cost);
}
