from flask import Blueprint, jsonify
import json
import os
import sys

# Add services to path
sys.path.append(os.path.join(os.path.dirname(os.path.dirname(__file__)), 'services'))
from activity_logger import log_activity

dashboard_bp = Blueprint('dashboard', __name__)

DATA_DIR = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'data')
ROUTERS_FILE = os.path.join(DATA_DIR, 'routers.json')
LINKS_FILE = os.path.join(DATA_DIR, 'links.json')
PACKETS_FILE = os.path.join(DATA_DIR, 'packets.json')
ACTIVITY_FILE = os.path.join(DATA_DIR, 'activity_logs.json')

def ensure_data_files():
    """Create data files if they don't exist"""
    os.makedirs(DATA_DIR, exist_ok=True)

    for filepath in [ROUTERS_FILE, LINKS_FILE, PACKETS_FILE, ACTIVITY_FILE]:
        if not os.path.exists(filepath):
            with open(filepath, 'w') as f:
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

@dashboard_bp.route('/dashboard/stats', methods=['GET'])
def get_dashboard_stats():
    """Get dashboard statistics"""
    ensure_data_files()
    routers = read_json_file(ROUTERS_FILE)
    links = read_json_file(LINKS_FILE)
    packets = read_json_file(PACKETS_FILE)

    active_routers = len([r for r in routers if r['status'] == 'active'])
    pending_packets = len([p for p in packets if p['status'] == 'pending'])
    processed_packets = len([p for p in packets if p['status'] == 'processed'])

    return jsonify({
        'success': True,
        'data': {
            'total_routers': len(routers),
            'active_routers': active_routers,
            'total_connections': len(links),
            'total_packets': len(packets),
            'pending_packets': pending_packets,
            'processed_packets': processed_packets
        }
    })

@dashboard_bp.route('/dashboard/activity', methods=['GET'])
def get_activity_log():
    """Get recent activity log"""
    ensure_data_files()
    activities = read_json_file(ACTIVITY_FILE)

    # Return last 10 activities
    recent_activities = activities[-10:] if len(activities) > 10 else activities

    return jsonify({
        'success': True,
        'data': recent_activities
    })

@dashboard_bp.route('/reset', methods=['POST'])
def reset_data():
    """Reset all data to initial state"""
    ensure_data_files()

    # Reset routers with sample data
    sample_routers = [
        {'id': 1, 'name': 'Router A', 'ip': '192.168.1.1', 'status': 'active', 'connections': 2},
        {'id': 2, 'name': 'Router B', 'ip': '192.168.1.2', 'status': 'active', 'connections': 2},
        {'id': 3, 'name': 'Router C', 'ip': '192.168.1.3', 'status': 'active', 'connections': 1},
        {'id': 4, 'name': 'Router D', 'ip': '192.168.1.4', 'status': 'active', 'connections': 1}
    ]
    write_json_file(ROUTERS_FILE, sample_routers)

    # Reset links with sample data
    sample_links = [
        {'id': 1, 'source': 1, 'destination': 2, 'cost': 2},
        {'id': 2, 'source': 1, 'destination': 3, 'cost': 3},
        {'id': 3, 'source': 2, 'destination': 4, 'cost': 1},
        {'id': 4, 'source': 3, 'destination': 4, 'cost': 2}
    ]
    write_json_file(LINKS_FILE, sample_links)

    # Reset packets
    write_json_file(PACKETS_FILE, [])

    # Reset activity log
    write_json_file(ACTIVITY_FILE, [])
    
    # Log the reset action
    log_activity('System data reset to initial state', 'success')

    return jsonify({
        'success': True,
        'message': 'Data reset successfully'
    })
