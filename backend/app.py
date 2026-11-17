from flask import Flask, jsonify
from flask_cors import CORS
import os
import sys

# Add parent directory to path to import from services
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

app = Flask(__name__)
CORS(app)

# Import routes
from routes.network import network_bp
from routes.routing import routing_bp
from routes.packets import packets_bp
from routes.algorithms import algorithms_bp
from routes.dashboard import dashboard_bp
from routes.test import test_bp

# Register blueprints
app.register_blueprint(network_bp, url_prefix='/api')
app.register_blueprint(routing_bp, url_prefix='/api')
app.register_blueprint(packets_bp, url_prefix='/api')
app.register_blueprint(algorithms_bp, url_prefix='/api')
app.register_blueprint(dashboard_bp, url_prefix='/api')
app.register_blueprint(test_bp, url_prefix='/api')

@app.route('/')
def home():
    return jsonify({
        'message': 'Smart Network Routing and Management System API',
        'version': '1.0.0',
        'status': 'running'
    })

@app.route('/api/health')
def health():
    return jsonify({'status': 'healthy'})

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
