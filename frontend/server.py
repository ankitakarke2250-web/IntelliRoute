#!/usr/bin/env python3
"""
Simple HTTP server for frontend development
Serves the frontend directory on port 8080
"""

import http.server
import socketserver
import os

# Change to frontend directory
frontend_dir = os.path.dirname(os.path.abspath(__file__))
os.chdir(frontend_dir)

PORT = 8081

Handler = http.server.SimpleHTTPRequestHandler

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print(f"Frontend server running at http://localhost:{PORT}")
    print(f"Serving directory: {frontend_dir}")
    httpd.serve_forever()
