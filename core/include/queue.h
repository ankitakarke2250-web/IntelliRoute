/*
 * Queue Header
 * Array, Linked List, and Circular Queue implementations
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"

/* Queue using Array */
typedef struct {
    int items[MAX_ARRAY_SIZE];
    int front;
    int rear;
} QueueArray;

/* Queue Node for Linked List */
typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

/* Queue using Linked List */
typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int count;
} QueueLinked;

/* Circular Queue */
typedef struct {
    int items[MAX_ARRAY_SIZE];
    int front;
    int rear;
} CircularQueue;

/* Queue Array Functions */
QueueArray* create_queue_array();
int is_empty_queue_array(QueueArray* q);
int is_full_queue_array(QueueArray* q);
void enqueue_array(QueueArray* q, int value);
int dequeue_array(QueueArray* q);
int peek_queue_array(QueueArray* q);
void display_queue_array(QueueArray* q);

/* Queue Linked List Functions */
QueueLinked* create_queue_linked();
int is_empty_queue_linked(QueueLinked* q);
void enqueue_linked(QueueLinked* q, int value);
int dequeue_linked(QueueLinked* q);
int peek_queue_linked(QueueLinked* q);
void display_queue_linked(QueueLinked* q);
void free_queue_linked(QueueLinked* q);

/* Circular Queue Functions */
CircularQueue* create_circular_queue();
int is_empty_circular(CircularQueue* q);
int is_full_circular(CircularQueue* q);
void enqueue_circular(CircularQueue* q, int value);
int dequeue_circular(CircularQueue* q);
void display_circular(CircularQueue* q);

#endif /* QUEUE_H */
