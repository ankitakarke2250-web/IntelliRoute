/*
 * Tree Wrapper Program
 * Reads JSON input, executes tree operations, outputs JSON
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/trees.h"

int main(int argc, char* argv[]) {
    BST* tree = create_bst();
    int operation_value = 0;
    char operation[20];
    int result[MAX_ARRAY_SIZE];
    int index = 0;

    // Get operation from command line argument
    if (argc > 1) {
        strcpy(operation, argv[1]);
    } else {
        strcpy(operation, "insert");
    }

    if (argc > 2) {
        operation_value = atoi(argv[2]);
    }

    // Insert some test nodes
    tree->root = insert_bst(tree->root, 50);
    tree->root = insert_bst(tree->root, 30);
    tree->root = insert_bst(tree->root, 70);
    tree->root = insert_bst(tree->root, 20);
    tree->root = insert_bst(tree->root, 40);

    if (strcmp(operation, "insert") == 0) {
        tree->root = insert_bst(tree->root, operation_value);
    } else if (strcmp(operation, "delete") == 0) {
        tree->root = delete_bst(tree->root, operation_value);
    } else if (strcmp(operation, "search") == 0) {
        BSTNode* found = search_bst(tree->root, operation_value);
        // Just return tree state
    } else if (strcmp(operation, "inorder") == 0) {
        inorder_traversal(tree->root, result, &index);
        print_bst_result_json(result, index, tree_height(tree->root), count_leaf_nodes(tree->root));
        return 0;
    } else if (strcmp(operation, "preorder") == 0) {
        preorder_traversal(tree->root, result, &index);
        print_bst_result_json(result, index, tree_height(tree->root), count_leaf_nodes(tree->root));
        return 0;
    } else if (strcmp(operation, "postorder") == 0) {
        postorder_traversal(tree->root, result, &index);
        print_bst_result_json(result, index, tree_height(tree->root), count_leaf_nodes(tree->root));
        return 0;
    }

    // Default: return tree properties
    int height = tree_height(tree->root);
    int leaf_count = count_leaf_nodes(tree->root);

    printf("{");
    printf("\"success\": true,");
    printf("\"data\": {");
    printf("\"height\": %d,", height);
    printf("\"leaf_nodes\": %d", leaf_count);
    printf("}");
    printf("}");

    return 0;
}
