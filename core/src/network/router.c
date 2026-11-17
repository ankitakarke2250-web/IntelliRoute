/*
 * Router Management Implementation
 * Linked List implementation for router storage
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/network.h"

/* Create a new router list */
RouterList* create_router_list() {
    RouterList* list = (RouterList*)malloc(sizeof(RouterList));
    if (list) {
        list->head = NULL;
        list->count = 0;
    }
    return list;
}

/* Free router list memory */
void free_router_list(RouterList* list) {
    if (!list) return;

    RouterNode* current = list->head;
    while (current) {
        RouterNode* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

/* Add a router to the list */
int add_router(RouterList* list, Router router) {
    if (!list) return 0;

    RouterNode* new_node = (RouterNode*)malloc(sizeof(RouterNode));
    if (!new_node) return 0;

    new_node->data = router;
    new_node->next = list->head;
    list->head = new_node;
    list->count++;

    return 1;
}

/* Delete a router by ID */
int delete_router(RouterList* list, int id) {
    if (!list || !list->head) return 0;

    RouterNode* current = list->head;
    RouterNode* prev = NULL;

    while (current) {
        if (current->data.id == id) {
            if (prev) {
                prev->next = current->next;
            } else {
                list->head = current->next;
            }
            free(current);
            list->count--;
            return 1;
        }
        prev = current;
        current = current->next;
    }

    return 0;
}

/* Find a router by ID */
Router* find_router(RouterList* list, int id) {
    if (!list) return NULL;

    RouterNode* current = list->head;
    while (current) {
        if (current->data.id == id) {
            return &(current->data);
        }
        current = current->next;
    }

    return NULL;
}

/* Display all routers */
void display_routers(RouterList* list) {
    if (!list || !list->head) {
        printf("No routers available.\n");
        return;
    }

    RouterNode* current = list->head;
    printf("=== Router List ===\n");
    while (current) {
        printf("ID: %d, Name: %s, IP: %s, Status: %s\n",
               current->data.id, current->data.name,
               current->data.ip, current->data.status);
        current = current->next;
    }
    printf("===================\n");
}

/* Get router count */
int router_count(RouterList* list) {
    return list ? list->count : 0;
}

/* Print router as JSON */
void print_router_json(Router router) {
    printf("{\"id\": %d, \"name\": \"%s\", \"ip\": \"%s\", \"status\": \"%s\", \"connections\": %d}",
           router.id, router.name, router.ip, router.status, router.connections);
}

/* Print router list as JSON array */
void print_router_list_json(RouterList* list) {
    if (!list || !list->head) {
        printf("[]");
        return;
    }

    printf("[");
    RouterNode* current = list->head;
    int first = 1;

    while (current) {
        if (!first) {
            printf(", ");
        }
        print_router_json(current->data);
        first = 0;
        current = current->next;
    }
    printf("]");
}
