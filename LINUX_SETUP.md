# Linux Setup Guide (Ubuntu / Debian)

This guide explains how to run IntelliRoute on Ubuntu or another Debian-based Linux distribution. It was tested on Ubuntu 24.04 with GCC 13 and Python 3.13.

## Quick start

```bash
git clone https://github.com/ankitakarke2250-web/IntelliRoute.git
cd IntelliRoute
sudo apt update
sudo apt install -y git gcc python3 python3-venv python3-pip curl
chmod +x start.sh
./start.sh
```

Then open **http://localhost:8081** in your browser. Press `Ctrl+C` in the terminal to stop both servers.

`start.sh` creates a virtual environment, installs the Python dependencies, compiles the C programs and starts the backend and frontend for you. The manual steps below do the same thing one at a time.

## Prerequisites

| Tool | Why it is needed | Check |
|------|------------------|-------|
| Python 3.8+ | Flask backend and frontend server | `python3 --version` |
| `python3-venv` | Isolated Python environment | `python3 -m venv --help` |
| GCC | Compiles the C algorithm programs | `gcc --version` |
| A web browser | Runs the UI | |

Install everything on Ubuntu with:

```bash
sudo apt update
sudo apt install -y git gcc python3 python3-venv python3-pip curl
```

The frontend loads Cytoscape.js, Chart.js and Font Awesome from public CDNs, so the machine needs internet access when you open the page.

## Manual setup

### 1. Get the code

```bash
git clone https://github.com/ankitakarke2250-web/IntelliRoute.git
cd IntelliRoute
```

### 2. Create a virtual environment and install dependencies

Modern Ubuntu (23.04+) blocks `pip install` into the system Python, so use a virtual environment:

```bash
python3 -m venv venv
source venv/bin/activate
pip install -r backend/requirements.txt
```

You must run `source venv/bin/activate` again in every new terminal before starting the backend.

### 3. Compile the C programs

The backend runs three compiled helpers from `core/src/`. Keep the `.exe` file names: the backend looks for those exact names on every operating system, and Linux runs them fine.

```bash
cd core/src
gcc -I../include -o sorting_wrapper.exe sorting_wrapper.c -lm
gcc -I../include -o search_wrapper.exe search_wrapper.c -lm
gcc -I../include -o routing_wrapper.exe routing_wrapper.c -lm
cd ../..
```

No output means success. Confirm with `ls core/src/*.exe`.

### 4. Start the backend (Terminal 1)

```bash
source venv/bin/activate
cd backend
python app.py
```

The API listens on port 5000.

### 5. Start the frontend (Terminal 2)

```bash
cd frontend
python3 server.py
```

The UI is served on port 8081. Open **http://localhost:8081**.

## Verify it works

With the backend running:

```bash
# Health check
curl http://localhost:5000/api/health

# Load the sample network
curl -X POST http://localhost:5000/api/reset

# Sorting (runs the C program)
curl -X POST http://localhost:5000/api/sorting/run \
  -H "Content-Type: application/json" \
  -d '{"algorithm":"bubble","array":[5,3,8,1,9,2]}'

# Searching (the field is called "element")
curl -X POST http://localhost:5000/api/search/run \
  -H "Content-Type: application/json" \
  -d '{"algorithm":"linear","array":[5,3,8,1,9,2],"element":8}'

# Routing
curl -X POST http://localhost:5000/api/routing/dijkstra \
  -H "Content-Type: application/json" \
  -d '{"source":1,"destination":4}'
```

Expected: the health check returns `{"status": "healthy"}`, sorting returns `[1,2,3,5,8,9]`, and Dijkstra returns route `[1,2,4]` with cost 3 on the sample network.

## Troubleshooting

### `externally-managed-environment` when running pip
Ubuntu protects the system Python. Use the virtual environment from step 2 instead of installing globally.

### `The virtual environment was not created successfully` / `ensurepip is not available`
```bash
sudo apt install -y python3-venv
```

### `gcc: command not found`
```bash
sudo apt install -y gcc
```
Or install the full toolchain with `sudo apt install -y build-essential`.

### `Permission denied` when starting `start.sh`
```bash
chmod +x start.sh
```

### Port already in use (`Address already in use`)
Find and stop whatever is using the port:
```bash
sudo lsof -i :5000      # backend
sudo lsof -i :8081      # frontend
kill <PID>
```
Port 5000 is also used by some other tools, so if it is taken, stop that tool first.

### Sorting, searching or routing returns an error
The C programs are missing or stale. Recompile them (step 3) and confirm `core/src/*.exe` exist and are executable (`ls -l core/src/*.exe`).

### The page loads but has no styling or graphs
The browser could not reach the CDNs. Check your internet connection, then hard refresh with `Ctrl+Shift+R`.

### Frontend cannot reach the backend (CORS or network error in the console)
Make sure the backend is running and that `curl http://localhost:5000/api/health` works. The frontend expects the API at `http://localhost:5000/api` (set in `frontend/js/api.js`).

### Data looks wrong or empty
Click **Reset Data** in the top navigation, or run `curl -X POST http://localhost:5000/api/reset`. Data lives in `data/*.json`, which is created on first use.

## Notes

- The backend runs Flask in debug mode and listens on all network interfaces (`0.0.0.0`). That is fine for local development, but do not expose port 5000 to untrusted networks.
- `*.exe` files, `venv/` and `data/*.json` are ignored by git, so rebuilding or resetting never dirties your working tree.
- Other Linux distributions: replace `apt` with your package manager (`dnf install gcc python3`, `pacman -S gcc python`, and so on).
