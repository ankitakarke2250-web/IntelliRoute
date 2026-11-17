/*
 * Common header file for all C programs
 * Contains shared structures and utilities
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Maximum sizes */
#define MAX_ROUTERS 100
#define MAX_NAME 50
#define MAX_IP 20
#define MAX_PACKETS 1000
#define MAX_ARRAY_SIZE 1000

/* Router structure */
typedef struct {
    int id;
    char name[MAX_NAME];
    char ip[MAX_IP];
    char status[20];
    int connections;
} Router;

/* Packet structure */
typedef struct {
    int id;
    int source;
    int destination;
    int size;
    char priority[20];
    char status[20];
} Packet;

/* Result structure for algorithms */
typedef struct {
    int comparisons;
    int swaps;
    double time_ms;
} AlgorithmResult;

/* Utility functions */
void print_json_start();
void print_json_end();
void print_json_string(const char* key, const char* value);
void print_json_int(const char* key, int value);
void print_json_bool(const char* key, bool value);

#endif /* COMMON_H */
