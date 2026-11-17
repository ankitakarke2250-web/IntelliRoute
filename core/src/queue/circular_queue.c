/*
 * Circular Queue Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/queue.h"

CircularQueue* create_circular_queue() {
    CircularQueue* q = (CircularQueue*)malloc(sizeof(CircularQueue));
    if (q) {
        q->front = -1;
        q->rear = -1;
    }
    return q;
}

int is_empty_circular(CircularQueue* q) {
    return q->front == -1;
}

int is_full_circular(CircularQueue* q) {
    return (q->rear + 1) % MAX_ARRAY_SIZE == q->front;
}

void enqueue_circular(CircularQueue* q, int value) {
    if (is_full_circular(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX_ARRAY_SIZE;
    q->items[q->rear] = value;
}

int dequeue_circular(CircularQueue* q) {
    if (is_empty_circular(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    int value = q->items[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_ARRAY_SIZE;
    }
    return value;
}

void display_circular(CircularQueue* q) {
    if (is_empty_circular(q)) {
        printf("Circular Queue is empty\n");
        return;
    }
    printf("Circular Queue: ");
    int i = q->front;
    while (1) {
        printf("%d ", q->items[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX_ARRAY_SIZE;
    }
    printf("\n");
}
