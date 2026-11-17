/*
 * Adjacency Matrix Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/graph.h"

/* Create adjacency matrix */
AdjacencyMatrix* create_adj_matrix(int num_vertices) {
    AdjacencyMatrix* adj = (AdjacencyMatrix*)malloc(sizeof(AdjacencyMatrix));
    if (!adj) return NULL;

    adj->num_vertices = num_vertices;

    // Initialize matrix with 0 (no edges)
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            adj->matrix[i][j] = 0;
        }
    }

    return adj;
}

/* Free adjacency matrix */
void free_adj_matrix(AdjacencyMatrix* adj) {
    if (adj) {
        free(adj);
    }
}

/* Add edge to adjacency matrix */
void add_edge_matrix(AdjacencyMatrix* adj, int src, int dest, int weight) {
    if (!adj || src >= adj->num_vertices || dest >= adj->num_vertices) return;

    adj->matrix[src][dest] = weight;
    adj->matrix[dest][src] = weight; // Undirected graph
}

/* Remove edge from adjacency matrix */
void remove_edge_matrix(AdjacencyMatrix* adj, int src, int dest) {
    if (!adj || src >= adj->num_vertices || dest >= adj->num_vertices) return;

    adj->matrix[src][dest] = 0;
    adj->matrix[dest][src] = 0;
}

/* Check if edge exists */
int has_edge_matrix(AdjacencyMatrix* adj, int src, int dest) {
    if (!adj || src >= adj->num_vertices || dest >= adj->num_vertices) return 0;
    return adj->matrix[src][dest] > 0;
}

/* Display adjacency matrix */
void display_adj_matrix(AdjacencyMatrix* adj) {
    if (!adj) return;

    printf("=== Adjacency Matrix ===\n");
    printf("    ");
    for (int i = 0; i < adj->num_vertices; i++) {
        printf("%3d ", i);
    }
    printf("\n");

    for (int i = 0; i < adj->num_vertices; i++) {
        printf("%3d ", i);
        for (int j = 0; j < adj->num_vertices; j++) {
            printf("%3d ", adj->matrix[i][j]);
        }
        printf("\n");
    }
    printf("========================\n");
}

/* Print adjacency matrix as JSON */
void print_adj_matrix_json(AdjacencyMatrix* adj) {
    if (!adj) {
        printf("[]");
        return;
    }

    printf("[");
    for (int i = 0; i < adj->num_vertices; i++) {
        if (i > 0) printf(",");
        printf("[");
        for (int j = 0; j < adj->num_vertices; j++) {
            if (j > 0) printf(",");
            printf("%d", adj->matrix[i][j]);
        }
        printf("]");
    }
    printf("]");
}
