from flask import Blueprint, request, jsonify
import json
import os
import sys
import subprocess

# Add services to path
sys.path.append(os.path.join(os.path.dirname(os.path.dirname(__file__)), 'services'))
from activity_logger import log_activity

routing_bp = Blueprint('routing', __name__)

DATA_DIR = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'data')
LINKS_FILE = os.path.join(DATA_DIR, 'links.json')
CORE_DIR = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'core')
ROUTING_WRAPPER = os.path.join(CORE_DIR, 'src', 'routing_wrapper.exe')

def read_json_file(filepath):
    """Read JSON file"""
    try:
        with open(filepath, 'r') as f:
            return json.load(f)
    except:
        return []

def build_edges_string():
    """Build edges string for C program"""
    links = read_json_file(LINKS_FILE)
    edges = []
    for link in links:
        source = link.get('source')
        dest = link.get('destination')
        cost = link.get('cost', 1)
        edges.append(f"{source}:{dest}:{cost}")
    return ','.join(edges)

@routing_bp.route('/routing/bfs', methods=['POST'])
def run_bfs():
    """Run BFS routing algorithm using C program"""
    data = request.json
    source = data.get('source')
    destination = data.get('destination')

    try:
        edges_str = build_edges_string()

        result = subprocess.run(
            [ROUTING_WRAPPER, 'bfs', str(source), str(destination), edges_str],
            capture_output=True,
            text=True,
            timeout=30
        )

        if result.returncode != 0:
            return jsonify({
                'success': False,
                'error': f'C program execution failed: {result.stderr}'
            })

        c_result = json.loads(result.stdout)

        log_activity(f'Routing: BFS from {source} to {destination}', 'success')

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

@routing_bp.route('/routing/dfs', methods=['POST'])
def run_dfs():
    """Run DFS routing algorithm using C program"""
    data = request.json
    source = data.get('source')
    destination = data.get('destination')

    try:
        edges_str = build_edges_string()

        result = subprocess.run(
            [ROUTING_WRAPPER, 'dfs', str(source), str(destination), edges_str],
            capture_output=True,
            text=True,
            timeout=30
        )

        if result.returncode != 0:
            return jsonify({
                'success': False,
                'error': f'C program execution failed: {result.stderr}'
            })

        c_result = json.loads(result.stdout)

        log_activity(f'Routing: DFS from {source} to {destination}', 'success')

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

@routing_bp.route('/routing/dijkstra', methods=['POST'])
def run_dijkstra():
    """Run Dijkstra's algorithm using C program"""
    data = request.json
    source = data.get('source')
    destination = data.get('destination')

    try:
        edges_str = build_edges_string()

        result = subprocess.run(
            [ROUTING_WRAPPER, 'dijkstra', str(source), str(destination), edges_str],
            capture_output=True,
            text=True,
            timeout=30
        )

        if result.returncode != 0:
            return jsonify({
                'success': False,
                'error': f'C program execution failed: {result.stderr}'
            })

        c_result = json.loads(result.stdout)

        log_activity(f'Routing: Dijkstra from {source} to {destination}', 'success')

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
