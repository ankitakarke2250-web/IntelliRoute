#!/usr/bin/env bash
# IntelliRoute launcher for Linux / macOS
# Usage: ./start.sh
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT"

# 1. Python virtual environment + dependencies
if [ ! -d venv ]; then
    echo "Creating Python virtual environment..."
    python3 -m venv venv
fi
# shellcheck disable=SC1091
source venv/bin/activate
pip install -q -r backend/requirements.txt

# 2. Compile the C wrappers (the backend expects these .exe file names on every OS)
echo "Compiling C programs..."
(
    cd core/src
    gcc -I../include -o sorting_wrapper.exe sorting_wrapper.c -lm
    gcc -I../include -o search_wrapper.exe search_wrapper.c -lm
    gcc -I../include -o routing_wrapper.exe routing_wrapper.c -lm
)

# 3. Start backend and frontend
python backend/app.py &
BACKEND_PID=$!
python frontend/server.py &
FRONTEND_PID=$!

cleanup() {
    echo
    echo "Stopping servers..."
    kill "$BACKEND_PID" "$FRONTEND_PID" 2>/dev/null || true
    # Flask debug mode spawns a reloader child; make sure it is gone too
    pkill -P "$BACKEND_PID" 2>/dev/null || true
    wait 2>/dev/null || true
    echo "Servers stopped."
}
trap cleanup INT TERM EXIT

sleep 2
echo
echo "========================================"
echo " IntelliRoute is running"
echo "========================================"
echo " Frontend:    http://localhost:8081"
echo " Backend API: http://localhost:5000"
echo " Press Ctrl+C to stop both servers"
echo "========================================"

wait
