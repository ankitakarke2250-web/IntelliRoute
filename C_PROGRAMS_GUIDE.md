# C Programs Guide

## Overview

The C programs in `core/src/` are complete, production-ready implementations of all data structures and algorithms used in the Smart Network Routing and Management System. This guide explains how to compile, run, and integrate these programs.

## Compiling C Programs

### Basic Compilation

```bash
cd core/src

# Compile individual programs
gcc -I../include network/router.c -o router.exe
gcc -I../include graph/adjacency_matrix.c -o adj_matrix.exe
gcc -I../include graph/adjacency_list.c -o adj_list.exe
gcc -I../include routing/bfs.c -o bfs.exe
gcc -I../include routing/dfs.c -o dfs.exe
gcc -I../include routing/dijkstra.c -o dijkstra.exe
gcc -I../include stack/stack_array.c -o stack_array.exe
gcc -I../include stack/stack_linked.c -o stack_linked.exe
gcc -I../include queue/queue_array.c -o queue_array.exe
gcc -I../include queue/queue_linked.c -o queue_linked.exe
gcc -I../include queue/circular_queue.c -o circular_queue.exe
gcc -I../include sorting/sorting_algorithms.c -o sorting.exe
gcc -I../include searching/searching_algorithms.c -o searching.exe
gcc -I../include trees/bst.c -o bst.exe
```

### Running Compiled Programs

```bash
# Run each program
./router.exe
./adj_matrix.exe
./adj_list.exe
./bfs.exe
./dfs.exe
./dijkstra.exe
./stack_array.exe
./stack_linked.exe
./queue_array.exe
./queue_linked.exe
./circular_queue.exe
./sorting.exe
./searching.exe
./bst.exe
```

## Program Descriptions

### 1. Router Management (`network/router.c`)

**Data Structure:** Linked List

**Functions:**
- `create_router_list()` - Create new router list
- `add_router()` - Add router to list
- `delete_router()` - Delete router by ID
- `find_router()` - Find router by ID
- `display_routers()` - Display all routers

**Purpose:** Implements linked list for efficient router storage and management.

---

### 2. Adjacency Matrix (`graph/adjacency_matrix.c`)

**Data Structure:** 2D Array

**Functions:**
- `create_adj_matrix()` - Create adjacency matrix
- `add_edge_matrix()` - Add edge with weight
- `remove_edge_matrix()` - Remove edge
- `has_edge_matrix()` - Check if edge exists
- `display_adj_matrix()` - Display matrix

**Purpose:** Implements graph representation using adjacency matrix for dense graphs.

---

### 3. Adjacency List (`graph/adjacency_list.c`)

**Data Structure:** Linked List of Linked Lists

**Functions:**
- `create_adj_list()` - Create adjacency list
- `add_edge_list()` - Add edge with weight
- `remove_edge_list()` - Remove edge
- `has_edge_list()` - Check if edge exists
- `display_adj_list()` - Display list

**Purpose:** Implements graph representation using adjacency list for sparse graphs.

---

### 4. BFS Algorithm (`routing/bfs.c`)

**Data Structure:** Queue

**Functions:**
- `bfs()` - Breadth First Search traversal
- Returns: traversal order, path, total cost

**Purpose:** Implements BFS for shortest path finding in unweighted graphs.

---

### 5. DFS Algorithm (`routing/dfs.c`)

**Data Structure:** Stack (recursion)

**Functions:**
- `dfs()` - Depth First Search traversal
- Returns: traversal order, path, total cost

**Purpose:** Implements DFS for graph exploration and path finding.

---

### 6. Dijkstra's Algorithm (`routing/dijkstra.c`)

**Data Structure:** Priority Queue (simulated with array)

**Functions:**
- `dijkstra()` - Shortest path algorithm
- Returns: shortest path, minimum cost

**Purpose:** Implements Dijkstra's algorithm for weighted shortest path finding.

---

### 7. Stack - Array (`stack/stack_array.c`)

**Data Structure:** Array

**Functions:**
- `create_stack_array()` - Create stack
- `push_array()` - Push element
- `pop_array()` - Pop element
- `peek_array()` - View top element
- `display_stack_array()` - Display stack

**Purpose:** Implements stack using array for fixed-size applications.

---

### 8. Stack - Linked List (`stack/stack_linked.c`)

**Data Structure:** Linked List

**Functions:**
- `create_stack_linked()` - Create stack
- `push_linked()` - Push element
- `pop_linked()` - Pop element
- `peek_linked()` - View top element
- `display_stack_linked()` - Display stack

**Purpose:** Implements stack using linked list for dynamic-size applications.

---

### 9. Queue - Array (`queue/queue_array.c`)

**Data Structure:** Array

**Functions:**
- `create_queue_array()` - Create queue
- `enqueue_array()` - Add element
- `dequeue_array()` - Remove element
- `peek_queue_array()` - View front element
- `display_queue_array()` - Display queue

**Purpose:** Implements queue using array for fixed-size applications.

---

### 10. Queue - Linked List (`queue/queue_linked.c`)

**Data Structure:** Linked List

**Functions:**
- `create_queue_linked()` - Create queue
- `enqueue_linked()` - Add element
- `dequeue_linked()` - Remove element
- `peek_queue_linked()` - View front element
- `display_queue_linked()` - Display queue

**Purpose:** Implements queue using linked list for dynamic-size applications.

---

### 11. Circular Queue (`queue/circular_queue.c`)

**Data Structure:** Circular Array

**Functions:**
- `create_circular_queue()` - Create circular queue
- `enqueue_circular()` - Add element
- `dequeue_circular()` - Remove element
- `display_circular()` - Display queue

**Purpose:** Implements circular queue for efficient memory usage in buffer applications.

---

### 12. Sorting Algorithms (`sorting/sorting_algorithms.c`)

**Algorithms:**
- Bubble Sort - O(n²) time complexity
- Selection Sort - O(n²) time complexity
- Insertion Sort - O(n²) time complexity
- Merge Sort - O(n log n) time complexity
- Quick Sort - O(n log n) average time complexity

**Functions:**
- `bubble_sort()` - Basic comparison sort
- `selection_sort()` - Selection-based sort
- `insertion_sort()` - Insertion-based sort
- `merge_sort()` - Divide and conquer sort
- `quick_sort()` - Partition-based sort

**Metrics Tracked:**
- Number of comparisons
- Number of swaps
- Execution time

**Purpose:** Implements all major sorting algorithms with performance metrics.

---

### 13. Searching Algorithms (`searching/searching_algorithms.c`)

**Algorithms:**
- Linear Search - O(n) time complexity
- Binary Search - O(log n) time complexity (requires sorted array)

**Functions:**
- `linear_search()` - Sequential search
- `binary_search()` - Divide and conquer search

**Metrics Tracked:**
- Number of comparisons
- Position of element

**Purpose:** Implements search algorithms with efficiency comparison.

---

### 14. Binary Search Tree (`trees/bst.c`)

**Data Structure:** Binary Search Tree

**Functions:**
- `create_bst()` - Create BST
- `insert_bst()` - Insert node
- `delete_bst()` - Delete node
- `search_bst()` - Search for node
- `inorder_traversal()` - Inorder traversal (sorted order)
- `preorder_traversal()` - Preorder traversal
- `postorder_traversal()` - Postorder traversal
- `tree_height()` - Calculate tree height
- `count_leaf_nodes()` - Count leaf nodes

**Purpose:** Implements BST operations and tree traversals for efficient data organization.

---

## How to Study Each Data Structure

### Step 1: Read the Header File

```bash
core/include/network.h      # For router/linked list
core/include/graph.h        # For graph representations
core/include/routing.h      # For routing algorithms
core/include/stack.h        # For stack implementations
core/include/queue.h        # For queue implementations
core/include/sorting.h      # For sorting algorithms
core/include/searching.h    # For searching algorithms
core/include/trees.h        # For BST
```

### Step 2: Read the Implementation

```bash
core/src/network/router.c
core/src/graph/adjacency_matrix.c
core/src/graph/adjacency_list.c
# ... etc
```

### Step 3: Compile and Run

```bash
cd core/src
gcc -I../include <program>.c -o <program>.exe
./<program>.exe
```

### Step 4: Modify and Experiment

- Add test data
- Modify functions
- Add print statements to trace execution
- Test edge cases
- Benchmark performance

## Integration with Web Application

The web application uses Python Flask for web operations while C programs handle compute-intensive algorithms:

- **C Programs:** Core algorithms and data structures
- **Python Flask:** Web API and orchestration
- **JSON:** Data exchange format
- **Subprocess:** C program execution

This architecture provides:
- **Performance:** Efficient C algorithm execution
- **Reliability:** Robust Python web framework
- **Maintainability:** Clear separation of concerns
- **Scalability:** Modular design

## Common Compilation Issues

### Issue: "undefined reference to..."

**Solution:** Make sure to include all necessary .c files when compiling
```bash
gcc -I../include program.c other_file.c -o program.exe
```

### Issue: "fatal error: common.h: No such file"

**Solution:** Ensure you're in the correct directory and include path is correct
```bash
cd core/src
gcc -I../include program.c -o program.exe
```

### Issue: "too many arguments to function"

**Solution:** Check function signature in header file matches implementation

## Code Quality

These C programs demonstrate:
1. **Proper structure usage** - All data structures implemented correctly
2. **Memory management** - Proper malloc/free usage
3. **Algorithm logic** - Clear, commented implementations
4. **Performance tracking** - Comparison/swap counting
5. **Code organization** - Modular, well-structured code
6. **Error handling** - Proper validation and error checking
7. **Documentation** - Comprehensive comments and headers

## Usage Examples

### Example 1: Using the Sorting Wrapper

```bash
cd core/src
./sorting_wrapper.exe bubble "5,3,8,1,9,2"
```

**Output:**
```json
{
  "success": true,
  "data": {
    "original": [5,3,8,1,9,2],
    "sorted": [1,2,3,5,8,9],
    "comparisons": 15,
    "swaps": 8,
    "time": 0.001
  }
}
```

### Example 2: Using the Routing Wrapper

```bash
cd core/src
./routing_wrapper.exe bfs 1 4 "1:2:2,2:4:1"
```

**Output:**
```json
{
  "success": true,
  "data": {
    "traversal": [1,2,4],
    "route": [1,2,4],
    "cost": 3
  }
}
```

## Best Practices

1. **Always compile with warnings enabled:**
   ```bash
   gcc -Wall -Wextra -I../include program.c -o program.exe
   ```

2. **Use consistent naming conventions:**
   - Functions: `snake_case`
   - Variables: `snake_case`
   - Constants: `UPPER_CASE`

3. **Add proper error handling:**
   - Check return values
   - Validate inputs
   - Handle edge cases

4. **Document your code:**
   - Add function comments
   - Explain complex logic
   - Document data structures

5. **Test thoroughly:**
   - Test edge cases
   - Verify memory management
   - Benchmark performance

---

**Note:** These C programs are complete, production-ready implementations that can be compiled and run independently or integrated with the web application via Flask subprocess calls.
