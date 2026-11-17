/*
 * Graph Management Header
 * Adjacency Matrix and Adjacency List implementations
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "common.h"

/* Adjacency Matrix */
typedef struct {
    int matrix[MAX_ROUTERS][MAX_ROUTERS];
    int num_vertices;
} AdjacencyMatrix;

/* Adjacency List Node */
typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

/* Adjacency List */
typedef struct {
    AdjListNode* array[MAX_ROUTERS];
    int num_vertices;
} AdjacencyList;

/* Link structure for connections */
typedef struct {
    int id;
    int source;
    int destination;
    int cost;
} Link;

/* Adjacency Matrix Functions */
AdjacencyMatrix* create_adj_matrix(int num_vertices);
void free_adj_matrix(AdjacencyMatrix* adj);
void add_edge_matrix(AdjacencyMatrix* adj, int src, int dest, int weight);
void remove_edge_matrix(AdjacencyMatrix* adj, int src, int dest);
int has_edge_matrix(AdjacencyMatrix* adj, int src, int dest);
void display_adj_matrix(AdjacencyMatrix* adj);
void print_adj_matrix_json(AdjacencyMatrix* adj);

/* Adjacency List Functions */
AdjacencyList* create_adj_list(int num_vertices);
void free_adj_list(AdjacencyList* adj);
void add_edge_list(AdjacencyList* adj, int src, int dest, int weight);
void remove_edge_list(AdjacencyList* adj, int src, int dest);
int has_edge_list(AdjacencyList* adj, int src, int dest);
void display_adj_list(AdjacencyList* adj);
void print_adj_list_json(AdjacencyList* adj);

/* Link Management */
void print_link_json(Link link);

#endif /* GRAPH_H */
