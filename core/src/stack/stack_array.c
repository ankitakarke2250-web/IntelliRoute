/*
 * Stack using Array Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h"

StackArray* create_stack_array() {
    StackArray* s = (StackArray*)malloc(sizeof(StackArray));
    if (s) {
        s->top = -1;
    }
    return s;
}

int is_empty_stack_array(StackArray* s) {
    return s->top == -1;
}

int is_full_stack_array(StackArray* s) {
    return s->top == MAX_ARRAY_SIZE - 1;
}

void push_array(StackArray* s, int value) {
    if (is_full_stack_array(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->items[++s->top] = value;
}

int pop_array(StackArray* s) {
    if (is_empty_stack_array(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->items[s->top--];
}

int peek_array(StackArray* s) {
    if (is_empty_stack_array(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->items[s->top];
}

void display_stack_array(StackArray* s) {
    if (is_empty_stack_array(s)) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack (Array): ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}
