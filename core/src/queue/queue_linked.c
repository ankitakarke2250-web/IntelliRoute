/*
 * Queue using Linked List Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/queue.h"

QueueLinked* create_queue_linked() {
    QueueLinked* q = (QueueLinked*)malloc(sizeof(QueueLinked));
    if (q) {
        q->front = NULL;
        q->rear = NULL;
        q->count = 0;
    }
    return q;
}

int is_empty_queue_linked(QueueLinked* q) {
    return q->front == NULL;
}

void enqueue_linked(QueueLinked* q, int value) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode) {
        newNode->data = value;
        newNode->next = NULL;

        if (q->rear == NULL) {
            q->front = newNode;
            q->rear = newNode;
        } else {
            q->rear->next = newNode;
            q->rear = newNode;
        }
        q->count++;
    }
}

int dequeue_linked(QueueLinked* q) {
    if (is_empty_queue_linked(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    QueueNode* temp = q->front;
    int value = temp->data;
    q->front = temp->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    q->count--;
    return value;
}

int peek_queue_linked(QueueLinked* q) {
    if (is_empty_queue_linked(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->front->data;
}

void display_queue_linked(QueueLinked* q) {
    if (is_empty_queue_linked(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue (Linked): ");
    QueueNode* current = q->front;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_queue_linked(QueueLinked* q) {
    while (!is_empty_queue_linked(q)) {
        dequeue_linked(q);
    }
    free(q);
}
