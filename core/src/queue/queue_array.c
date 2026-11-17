/*
 * Queue using Array Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/queue.h"

QueueArray* create_queue_array() {
    QueueArray* q = (QueueArray*)malloc(sizeof(QueueArray));
    if (q) {
        q->front = -1;
        q->rear = -1;
    }
    return q;
}

int is_empty_queue_array(QueueArray* q) {
    return q->front == -1;
}

int is_full_queue_array(QueueArray* q) {
    return q->rear == MAX_ARRAY_SIZE - 1;
}

void enqueue_array(QueueArray* q, int value) {
    if (is_full_queue_array(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->items[++q->rear] = value;
}

int dequeue_array(QueueArray* q) {
    if (is_empty_queue_array(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    int value = q->items[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return value;
}

int peek_queue_array(QueueArray* q) {
    if (is_empty_queue_array(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->items[q->front];
}

void display_queue_array(QueueArray* q) {
    if (is_empty_queue_array(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue (Array): ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}
