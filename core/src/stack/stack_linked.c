/*
 * Stack using Linked List Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h"

StackLinked* create_stack_linked() {
    StackLinked* s = (StackLinked*)malloc(sizeof(StackLinked));
    if (s) {
        s->top = NULL;
        s->count = 0;
    }
    return s;
}

int is_empty_stack_linked(StackLinked* s) {
    return s->top == NULL;
}

void push_linked(StackLinked* s, int value) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode) {
        newNode->data = value;
        newNode->next = s->top;
        s->top = newNode;
        s->count++;
    }
}

int pop_linked(StackLinked* s) {
    if (is_empty_stack_linked(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    StackNode* temp = s->top;
    int value = temp->data;
    s->top = temp->next;
    free(temp);
    s->count--;
    return value;
}

int peek_linked(StackLinked* s) {
    if (is_empty_stack_linked(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->top->data;
}

void display_stack_linked(StackLinked* s) {
    if (is_empty_stack_linked(s)) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack (Linked): ");
    StackNode* current = s->top;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_stack_linked(StackLinked* s) {
    while (!is_empty_stack_linked(s)) {
        pop_linked(s);
    }
    free(s);
}
