from flask import Blueprint, request, jsonify
import json
import os

packets_bp = Blueprint('packets', __name__)

DATA_DIR = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'data')
PACKETS_FILE = os.path.join(DATA_DIR, 'packets.json')

def ensure_data_files():
    """Create data files if they don't exist"""
    os.makedirs(DATA_DIR, exist_ok=True)

    if not os.path.exists(PACKETS_FILE):
        with open(PACKETS_FILE, 'w') as f:
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

@packets_bp.route('/packets', methods=['GET'])
def get_packets():
    """Get all packets"""
    ensure_data_files()
    packets = read_json_file(PACKETS_FILE)
    return jsonify({'success': True, 'data': packets})

@packets_bp.route('/packets', methods=['POST'])
def add_packet():
    """Add a new packet"""
    ensure_data_files()
    data = request.json

    packets = read_json_file(PACKETS_FILE)
    new_id = len(packets) + 1 if packets else 1

    new_packet = {
        'id': new_id,
        'source': data.get('source'),
        'destination': data.get('destination'),
        'size': data.get('size'),
        'priority': data.get('priority'),
        'status': 'pending'
    }

    packets.append(new_packet)
    write_json_file(PACKETS_FILE, packets)

    return jsonify({'success': True, 'data': new_packet})

@packets_bp.route('/packets/process', methods=['POST'])
def process_packet():
    """Process the next packet (FIFO)"""
    ensure_data_files()
    packets = read_json_file(PACKETS_FILE)

    # Find first pending packet
    pending_packets = [p for p in packets if p['status'] == 'pending']

    if not pending_packets:
        return jsonify({'success': False, 'message': 'No pending packets'})

    # Process first packet
    packet_to_process = pending_packets[0]
    for packet in packets:
        if packet['id'] == packet_to_process['id']:
            packet['status'] = 'processed'
            break

    write_json_file(PACKETS_FILE, packets)

    return jsonify({'success': True, 'data': packet_to_process})
