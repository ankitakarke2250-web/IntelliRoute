/*
 * Network Management Header
 * Structures and function declarations for router management
 */

#ifndef NETWORK_H
#define NETWORK_H

#include "common.h"

/* Router Node for Linked List */
typedef struct RouterNode {
    Router data;
    struct RouterNode* next;
} RouterNode;

/* Linked List structure */
typedef struct {
    RouterNode* head;
    int count;
} RouterList;

/* Router Management Functions */
RouterList* create_router_list();
void free_router_list(RouterList* list);
int add_router(RouterList* list, Router router);
int delete_router(RouterList* list, int id);
Router* find_router(RouterList* list, int id);
void display_routers(RouterList* list);
int router_count(RouterList* list);

/* Utility Functions */
void print_router_json(Router router);
void print_router_list_json(RouterList* list);

#endif /* NETWORK_H */
