/*
 * Binary Search Tree Header
 */

#ifndef TREES_H
#define TREES_H

#include "common.h"

/* BST Node */
typedef struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

/* BST Structure */
typedef struct {
    BSTNode* root;
    int count;
} BST;

/* BST Operations */
BST* create_bst();
void free_bst(BST* tree);
BSTNode* insert_bst(BSTNode* root, int value);
BSTNode* delete_bst(BSTNode* root, int value);
BSTNode* search_bst(BSTNode* root, int value);

/* Traversals */
void inorder_traversal(BSTNode* root, int result[], int* index);
void preorder_traversal(BSTNode* root, int result[], int* index);
void postorder_traversal(BSTNode* root, int result[], int* index);

/* Tree Properties */
int tree_height(BSTNode* root);
int count_leaf_nodes(BSTNode* root);

/* Utility Functions */
BSTNode* find_min(BSTNode* root);
void print_bst_result_json(int result[], int count, int height, int leaf_count);

#endif /* TREES_H */
