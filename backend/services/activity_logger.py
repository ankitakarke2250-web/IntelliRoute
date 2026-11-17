"""
Activity Logger Service
Centralized activity logging for all modules
"""

import json
import os
from datetime import datetime

DATA_DIR = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'data')
ACTIVITY_FILE = os.path.join(DATA_DIR, 'activity_logs.json')

def log_activity(action, status='success'):
    """Log an activity"""
    os.makedirs(DATA_DIR, exist_ok=True)
    
    try:
        with open(ACTIVITY_FILE, 'r') as f:
            activities = json.load(f)
    except:
        activities = []
    
    activity = {
        'timestamp': datetime.now().strftime('%Y-%m-%d %H:%M:%S'),
        'action': action,
        'status': status
    }
    
    activities.append(activity)
    
    # Keep only last 50 activities
    if len(activities) > 50:
        activities = activities[-50:]
    
    with open(ACTIVITY_FILE, 'w') as f:
        json.dump(activities, f, indent=2)
