/*
 * Binary Search Tree Implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/trees.h"

BST* create_bst() {
    BST* tree = (BST*)malloc(sizeof(BST));
    if (tree) {
        tree->root = NULL;
        tree->count = 0;
    }
    return tree;
}

BSTNode* create_bst_node(int value) {
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    if (newNode) {
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

BSTNode* insert_bst(BSTNode* root, int value) {
    if (root == NULL) {
        return create_bst_node(value);
    }

    if (value < root->data) {
        root->left = insert_bst(root->left, value);
    } else if (value > root->data) {
        root->right = insert_bst(root->right, value);
    }

    return root;
}

BSTNode* find_min(BSTNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

BSTNode* delete_bst(BSTNode* root, int value) {
    if (root == NULL) return root;

    if (value < root->data) {
        root->left = delete_bst(root->left, value);
    } else if (value > root->data) {
        root->right = delete_bst(root->right, value);
    } else {
        if (root->left == NULL) {
            BSTNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BSTNode* temp = root->left;
            free(root);
            return temp;
        }

        BSTNode* temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete_bst(root->right, temp->data);
    }

    return root;
}

BSTNode* search_bst(BSTNode* root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return search_bst(root->left, value);
    }

    return search_bst(root->right, value);
}

void inorder_traversal(BSTNode* root, int result[], int* index) {
    if (root != NULL) {
        inorder_traversal(root->left, result, index);
        result[(*index)++] = root->data;
        inorder_traversal(root->right, result, index);
    }
}

void preorder_traversal(BSTNode* root, int result[], int* index) {
    if (root != NULL) {
        result[(*index)++] = root->data;
        preorder_traversal(root->left, result, index);
        preorder_traversal(root->right, result, index);
    }
}

void postorder_traversal(BSTNode* root, int result[], int* index) {
    if (root != NULL) {
        postorder_traversal(root->left, result, index);
        postorder_traversal(root->right, result, index);
        result[(*index)++] = root->data;
    }
}

int tree_height(BSTNode* root) {
    if (root == NULL) return 0;

    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);

    return (left_height > right_height ? left_height : right_height) + 1;
}

int count_leaf_nodes(BSTNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;

    return count_leaf_nodes(root->left) + count_leaf_nodes(root->right);
}

void free_bst(BST* tree) {
    // TODO: Implement recursive free
    free(tree);
}

void print_bst_result_json(int result[], int count, int height, int leaf_count) {
    printf("{");
    printf("\"success\": true,");
    printf("\"data\": {");
    printf("\"result\": [");
    for (int i = 0; i < count; i++) {
        if (i > 0) printf(",");
        printf("%d", result[i]);
    }
    printf("],");
    printf("\"height\": %d,", height);
    printf("\"leaf_nodes\": %d", leaf_count);
    printf("}");
    printf("}");
}
