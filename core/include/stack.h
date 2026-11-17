/*
 * Stack Header
 * Array and Linked List implementations
 */

#ifndef STACK_H
#define STACK_H

#include "common.h"

/* Stack using Array */
typedef struct {
    int items[MAX_ARRAY_SIZE];
    int top;
} StackArray;

/* Stack Node for Linked List */
typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

/* Stack using Linked List */
typedef struct {
    StackNode* top;
    int count;
} StackLinked;

/* Stack Array Functions */
StackArray* create_stack_array();
int is_empty_stack_array(StackArray* s);
int is_full_stack_array(StackArray* s);
void push_array(StackArray* s, int value);
int pop_array(StackArray* s);
int peek_array(StackArray* s);
void display_stack_array(StackArray* s);

/* Stack Linked List Functions */
StackLinked* create_stack_linked();
int is_empty_stack_linked(StackLinked* s);
void push_linked(StackLinked* s, int value);
int pop_linked(StackLinked* s);
int peek_linked(StackLinked* s);
void display_stack_linked(StackLinked* s);
void free_stack_linked(StackLinked* s);

#endif /* STACK_H */
