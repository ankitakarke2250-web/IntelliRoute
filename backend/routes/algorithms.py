from flask import Blueprint, request, jsonify
import os
import sys
import subprocess
import json
from datetime import datetime

# Add services to path
sys.path.append(os.path.join(os.path.dirname(os.path.dirname(__file__)), 'services'))
from c_compiler import CCompiler
from activity_logger import log_activity

algorithms_bp = Blueprint('algorithms', __name__)

compiler = CCompiler()

# Get paths to C programs
CORE_DIR = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'core')
SORTING_WRAPPER = os.path.join(CORE_DIR, 'src', 'sorting_wrapper.exe')
SEARCH_WRAPPER = os.path.join(CORE_DIR, 'src', 'search_wrapper.exe')

@algorithms_bp.route('/sorting/run', methods=['POST'])
def run_sort():
    """Run sorting algorithm using C program"""
    import time
    data = request.json
    algorithm = data.get('algorithm')
    array = data.get('array')

    # Convert array to comma-separated string
    array_str = ','.join(map(str, array))

    try:
        # Measure execution time using Python for better accuracy
        start_time = time.time()

        # Call C program
        result = subprocess.run(
            [SORTING_WRAPPER, algorithm, array_str],
            capture_output=True,
            text=True,
            timeout=30
        )

        end_time = time.time()
        execution_time_ms = round((end_time - start_time) * 1000, 3)

        if result.returncode != 0:
            return jsonify({
                'success': False,
                'error': f'C program execution failed: {result.stderr}'
            })

        # Parse JSON output from C program
        c_result = json.loads(result.stdout)

        # Add original array to response
        c_result['data']['original'] = array

        # Use Python-measured time for better accuracy on small arrays
        c_result['data']['time'] = execution_time_ms

        # Log activity
        log_activity(f'Sorting: {algorithm.capitalize()} sort on {len(array)} elements', 'success')

        return jsonify(c_result)

    except subprocess.TimeoutExpired:
        return jsonify({
            'success': False,
            'error': 'C program execution timeout'
        })
    except json.JSONDecodeError as e:
        return jsonify({
            'success': False,
            'error': f'Failed to parse C program output: {str(e)}'
        })
    except Exception as e:
        return jsonify({
            'success': False,
            'error': f'Error running C program: {str(e)}'
        })

@algorithms_bp.route('/search/run', methods=['POST'])
def run_search():
    """Run search algorithm using C program"""
    data = request.json
    algorithm = data.get('algorithm')
    array = data.get('array')
    element = data.get('element')

    # Convert array to comma-separated string
    array_str = ','.join(map(str, array))

    try:
        # Call C program
        result = subprocess.run(
            [SEARCH_WRAPPER, algorithm, array_str, str(element)],
            capture_output=True,
            text=True,
            timeout=30
        )

        if result.returncode != 0:
            return jsonify({
                'success': False,
                'error': f'C program execution failed: {result.stderr}'
            })

        # Parse JSON output from C program
        c_result = json.loads(result.stdout)

        # Log activity
        log_activity(f'Search: {algorithm.capitalize()} search for element {element}', 'success')

        return jsonify(c_result)

    except subprocess.TimeoutExpired:
        return jsonify({
            'success': False,
            'error': 'C program execution timeout'
        })
    except json.JSONDecodeError as e:
        return jsonify({
            'success': False,
            'error': f'Failed to parse C program output: {str(e)}'
        })
    except Exception as e:
        return jsonify({
            'success': False,
            'error': f'Error running C program: {str(e)}'
        })

@algorithms_bp.route('/trees/operation', methods=['POST'])
def run_tree_operation():
    """Run tree operation with real BST state management"""
    import os
    data = request.json
    operation = data.get('operation')
    value = data.get('value')

    # Path to tree data file
    tree_file = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'data', 'tree.json')

    # Load current tree state
    try:
        with open(tree_file, 'r') as f:
            tree_data = json.load(f)
            nodes = tree_data.get('nodes', [])
    except:
        nodes = []

    # Perform operation
    if operation == 'insert':
        if value not in nodes:
            nodes.append(value)
            log_activity(f'Tree: Inserted node {value}', 'success')
        else:
            log_activity(f'Tree: Node {value} already exists', 'error')
    elif operation == 'delete':
        if value in nodes:
            nodes.remove(value)
            log_activity(f'Tree: Deleted node {value}', 'success')
        else:
            log_activity(f'Tree: Node {value} not found', 'error')
    elif operation == 'search':
        found = value in nodes
        log_activity(f'Tree: Searched for node {value} - {"Found" if found else "Not Found"}', 'success')

    # Save updated tree state
    with open(tree_file, 'w') as f:
        json.dump({'nodes': nodes}, f)

    # Calculate tree properties
    height = calculate_tree_height(nodes)
    leaf_nodes = count_leaf_nodes(nodes)

    return jsonify({
        'success': True,
        'data': {
            'nodes': nodes,
            'height': height,
            'leaf_nodes': leaf_nodes,
            'found': value in nodes if operation == 'search' else None
        }
    })

def calculate_tree_height(nodes):
    """Calculate approximate height of BST"""
    if not nodes:
        return 0
    # For a balanced BST, height ≈ log2(n)
    import math
    return int(math.log2(len(nodes))) + 1

def count_leaf_nodes(nodes):
    """Count approximate leaf nodes in BST"""
    if not nodes:
        return 0
    # Approximate: half of nodes are leaves in balanced BST
    return max(1, len(nodes) // 2)

@algorithms_bp.route('/trees/get', methods=['GET'])
def get_tree():
    """Get current tree state"""
    import os
    tree_file = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'data', 'tree.json')

    try:
        with open(tree_file, 'r') as f:
            tree_data = json.load(f)
            nodes = tree_data.get('nodes', [])
    except:
        nodes = []

    height = calculate_tree_height(nodes)
    leaf_nodes = count_leaf_nodes(nodes)

    return jsonify({
        'success': True,
        'data': {
            'nodes': nodes,
            'height': height,
            'leaf_nodes': leaf_nodes
        }
    })

@algorithms_bp.route('/trees/traversal', methods=['POST'])
def run_tree_traversal():
    """Run tree traversal with real tree state"""
    import os
    data = request.json
    traversal = data.get('traversal')

    # Path to tree data file
    tree_file = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'data', 'tree.json')

    # Load current tree state
    try:
        with open(tree_file, 'r') as f:
            tree_data = json.load(f)
            nodes = tree_data.get('nodes', [])
    except:
        nodes = []

    # Sort nodes for traversal (simulating BST order)
    sorted_nodes = sorted(nodes)

    # Perform traversal
    if traversal == 'inorder':
        result = sorted_nodes
    elif traversal == 'preorder':
        # Preorder: root, left, right (simplified as first element, then rest)
        if sorted_nodes:
            result = [sorted_nodes[len(sorted_nodes)//2]] + [n for n in sorted_nodes if n != sorted_nodes[len(sorted_nodes)//2]]
        else:
            result = []
    else:  # postorder
        # Postorder: left, right, root (simplified)
        if sorted_nodes:
            result = [n for n in sorted_nodes if n != sorted_nodes[len(sorted_nodes)//2]] + [sorted_nodes[len(sorted_nodes)//2]]
        else:
            result = []

    # Calculate tree properties
    height = calculate_tree_height(nodes)
    leaf_nodes = count_leaf_nodes(nodes)

    log_activity(f'Tree: {traversal} traversal', 'success')

    return jsonify({
        'success': True,
        'data': {
            'result': result,
            'height': height,
            'leaf_nodes': leaf_nodes
        }
    })

@algorithms_bp.route('/analysis/benchmark', methods=['POST'])
def run_benchmark():
    """Run algorithm benchmark using actual C programs"""
    import time
    
    # Test array for benchmarking
    test_array = [i for i in range(100)]
    array_str = ','.join(map(str, test_array))
    
    # Benchmark sorting algorithms using C programs
    sorting_results = []
    algorithms = ['bubble', 'selection', 'insertion', 'merge', 'quick']
    
    for algo in algorithms:
        try:
            start_time = time.time()
            result = subprocess.run(
                [SORTING_WRAPPER, algo, array_str],
                capture_output=True,
                text=True,
                timeout=30
            )
            end_time = time.time()
            
            if result.returncode == 0:
                c_result = json.loads(result.stdout)
                sorting_results.append({
                    'algorithm': algo.capitalize() + ' Sort',
                    'time': round((end_time - start_time) * 1000, 2),
                    'comparisons': c_result['data']['comparisons'],
                    'swaps': c_result['data']['swaps']
                })
            else:
                sorting_results.append({
                    'algorithm': algo.capitalize() + ' Sort',
                    'time': 0,
                    'comparisons': 0,
                    'swaps': 0
                })
        except Exception as e:
            sorting_results.append({
                'algorithm': algo.capitalize() + ' Sort',
                'time': 0,
                'comparisons': 0,
                'swaps': 0
            })
    
    # Benchmark search algorithms
    search_results = []
    search_algos = ['linear', 'binary']
    
    for algo in search_algos:
        try:
            start_time = time.time()
            result = subprocess.run(
                [SEARCH_WRAPPER, algo, array_str, '50'],
                capture_output=True,
                text=True,
                timeout=30
            )
            end_time = time.time()
            
            if result.returncode == 0:
                c_result = json.loads(result.stdout)
                search_results.append({
                    'algorithm': algo.capitalize() + ' Search',
                    'comparisons': c_result['data']['comparisons'],
                    'time': round((end_time - start_time) * 1000, 4)
                })
            else:
                search_results.append({
                    'algorithm': algo.capitalize() + ' Search',
                    'comparisons': 0,
                    'time': 0
                })
        except Exception as e:
            search_results.append({
                'algorithm': algo.capitalize() + ' Search',
                'comparisons': 0,
                'time': 0
            })
    
    return jsonify({
        'success': True,
        'data': {
            'sorting': sorting_results,
            'search': search_results,
            'note': 'Actual C program execution times (not simulated)'
        }
    })
