from flask import Blueprint, request, jsonify
import json
import os
import sys

# Add services to path
sys.path.append(os.path.join(os.path.dirname(os.path.dirname(__file__)), 'services'))
from activity_logger import log_activity

network_bp = Blueprint('network', __name__)

DATA_DIR = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'data')
ROUTERS_FILE = os.path.join(DATA_DIR, 'routers.json')
LINKS_FILE = os.path.join(DATA_DIR, 'links.json')

def ensure_data_files():
    """Create data files if they don't exist"""
    os.makedirs(DATA_DIR, exist_ok=True)

    if not os.path.exists(ROUTERS_FILE):
        with open(ROUTERS_FILE, 'w') as f:
            json.dump([], f)

    if not os.path.exists(LINKS_FILE):
        with open(LINKS_FILE, 'w') as f:
            json.dump([], f)

def read_json_file(filepath):
    """Read JSON file"""
    try:
        with open(filepath, 'r') as f:
            return json.load(f)
    except:
        return []

def write_json_file(filepath, data):
    """Write JSON file"""
    with open(filepath, 'w') as f:
        json.dump(data, f, indent=2)

@network_bp.route('/routers', methods=['GET'])
def get_routers():
    """Get all routers"""
    ensure_data_files()
    routers = read_json_file(ROUTERS_FILE)
    return jsonify({'success': True, 'data': routers})

@network_bp.route('/routers', methods=['POST'])
def add_router():
    """Add a new router"""
    ensure_data_files()
    data = request.json

    routers = read_json_file(ROUTERS_FILE)
    new_id = len(routers) + 1 if routers else 1

    new_router = {
        'id': new_id,
        'name': data.get('name'),
        'ip': data.get('ip'),
        'status': data.get('status', 'active'),
        'connections': 0
    }

    routers.append(new_router)
    write_json_file(ROUTERS_FILE, routers)
    
    log_activity(f'Added router: {new_router["name"]} (ID: {new_id})', 'success')

    return jsonify({'success': True, 'data': new_router})

@network_bp.route('/routers/<int:router_id>', methods=['DELETE'])
def delete_router(router_id):
    """Delete a router"""
    ensure_data_files()
    routers = read_json_file(ROUTERS_FILE)
    
    router_name = next((r['name'] for r in routers if r['id'] == router_id), 'Unknown')

    routers = [r for r in routers if r['id'] != router_id]
    write_json_file(ROUTERS_FILE, routers)
    
    log_activity(f'Deleted router: {router_name} (ID: {router_id})', 'success')

    return jsonify({'success': True, 'message': 'Router deleted'})

@network_bp.route('/links', methods=['GET'])
def get_links():
    """Get all links"""
    ensure_data_files()
    links = read_json_file(LINKS_FILE)
    return jsonify({'success': True, 'data': links})

@network_bp.route('/links', methods=['POST'])
def add_link():
    """Add a new link"""
    ensure_data_files()
    data = request.json

    links = read_json_file(LINKS_FILE)
    new_id = len(links) + 1 if links else 1

    new_link = {
        'id': new_id,
        'source': data.get('source'),
        'destination': data.get('destination'),
        'cost': data.get('cost', 1)
    }

    links.append(new_link)
    write_json_file(LINKS_FILE, links)
    
    log_activity(f'Added connection: Router {new_link["source"]} to Router {new_link["destination"]} (Cost: {new_link["cost"]})', 'success')

    return jsonify({'success': True, 'data': new_link})

@network_bp.route('/links/<int:link_id>', methods=['DELETE'])
def delete_link(link_id):
    """Delete a link"""
    ensure_data_files()
    links = read_json_file(LINKS_FILE)
    
    link = next((l for l in links if l['id'] == link_id), None)
    if link:
        log_activity(f'Deleted connection: Router {link["source"]} to Router {link["destination"]}', 'success')

    links = [l for l in links if l['id'] != link_id]
    write_json_file(LINKS_FILE, links)

    return jsonify({'success': True, 'message': 'Link deleted'})

@network_bp.route('/network/graph', methods=['GET'])
def get_graph():
    """Get network graph data for visualization"""
    ensure_data_files()
    routers = read_json_file(ROUTERS_FILE)
    links = read_json_file(LINKS_FILE)

    elements = {
        'nodes': [{'data': {'id': str(r['id']), 'label': r['name']}} for r in routers],
        'edges': [{'data': {'source': str(l['source']), 'target': str(l['destination']), 'label': str(l['cost'])}} for l in links]
    }

    return jsonify({'success': True, 'data': {'elements': elements}})
