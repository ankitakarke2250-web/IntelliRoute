# Smart Network Routing and Management System

**Version:** 2.0.0

A comprehensive web-based network simulation platform that demonstrates the practical application of data structures and algorithms in computer networking. Built with C for core algorithms, Python Flask for the backend, and modern web technologies for the frontend.

## Overview

This project provides a complete network simulation environment where users can:
- Create and manage network routers with configurable connections
- Visualize network topology using interactive graphs
- Execute routing algorithms (BFS, DFS, Dijkstra) on real network data
- Generate and process network packets using queue data structures
- Analyze sorting and searching algorithm performance
- Explore binary search tree operations
- Benchmark algorithm performance with actual measurements

## Technology Stack

### Core Algorithms (C)
- **Language:** C99
- **Compiler:** GCC 6.3.0 (MinGW)
- **Data Structures:** Linked Lists, Arrays, Stacks, Queues, Graphs, Trees
- **Algorithms:** Sorting (5 types), Searching (2 types), Routing (3 types)

### Backend (Python)
- **Framework:** Flask 3.0+
- **CORS:** Flask-CORS
- **Data Storage:** JSON files
- **C Integration:** Subprocess execution

### Frontend (Web)
- **Languages:** HTML5, CSS3, JavaScript ES6+
- **Visualization:** Cytoscape.js, Chart.js
- **Design:** Dark theme, responsive, professional UI

## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    Frontend (Browser)                        │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐  │
│  │Dashboard │  │ Network  │  │ Routing  │  │ Packets  │  │
│  │          │  │  Mgmt    │  │ Sim      │  │ Mgmt     │  │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘  │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐  │
│  │Sorting & │  │   Tree   │  │Performance│  │  About   │  │
│  │Searching │  │ Explorer │  │ Analysis │  │          │  │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘  │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                    Backend (Flask)                          │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐  │
│  │  Routes  │  │ Services │  │   C     │  │  Data    │  │
│  │          │  │          │  │Compiler │  │  Files   │  │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘  │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                    C Programs (Core)                        │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐  │
│  │Sorting   │  │Searching │  │ Routing  │  │  Trees   │  │
│  │Wrapper   │  │Wrapper   │  │Wrapper   │  │   BST    │  │
│  └──────────┘  └──────────┘  └──────────┘  └──────────┘  │
└─────────────────────────────────────────────────────────────┘
```

## Features

### Network Management
- Add, edit, and delete routers with IP addresses and status
- Create connections between routers with configurable costs
- Automatic connection cleanup when deleting routers
- Real-time router status tracking

### Network Topology
- Interactive network graph visualization using Cytoscape.js
- Zoom, pan, and layout algorithms
- Edge cost labels with professional styling
- Dashboard topology preview

### Routing Algorithms
- **BFS (Breadth-First Search):** Unweighted shortest path
- **DFS (Depth-First Search):** Depth-first traversal
- **Dijkstra's Algorithm:** Weighted shortest path
- All algorithms implemented in C and executed via Flask subprocess
- Real-time traversal order, route path, and cost calculation

### Packet Management
- Generate packets with source, destination, size, and priority
- Process packets using FIFO queue
- Track packet status (pending/processed)
- View packet history and statistics

### Sorting & Searching
- **Sorting:** Bubble, Selection, Insertion, Merge, Quick Sort
- **Searching:** Linear Search, Binary Search
- All algorithms implemented in C with actual execution
- Display comparisons, swaps, and execution time
- Support for custom input and random array generation

### Tree Explorer
- Binary Search Tree operations (Insert, Delete, Search)
- Tree traversals (Inorder, Preorder, Postorder)
- Tree height and leaf node calculation
- Modern visualization with glowing nodes and animations
- Pan and zoom functionality

### Performance Analysis
- Algorithm benchmarking with actual C execution
- Sorting and searching performance comparison
- Execution time measurements
- Interactive charts using Chart.js
- Theoretical complexity information

## Project Structure

```
IntelliRoute/
├── frontend/                    # Frontend application
│   ├── css/
│   │   └── style.css           # Main stylesheet
│   ├── js/
│   │   ├── api.js              # API service layer
│   │   └── app.js              # Main application logic
│   ├── index.html              # Main HTML file
│   └── server.py               # Frontend HTTP server
│
├── backend/                     # Flask backend
│   ├── app.py                  # Main Flask application
│   ├── routes/                 # API route modules
│   │   ├── network.py          # Network management routes
│   │   ├── routing.py          # Routing algorithm routes
│   │   ├── packets.py          # Packet management routes
│   │   ├── algorithms.py       # Sorting/searching/tree routes
│   │   ├── dashboard.py        # Dashboard routes
│   │   └── test.py             # Test routes
│   ├── services/               # Backend services
│   │   ├── activity_logger.py  # Activity logging
│   │   └── c_compiler.py       # C compilation service
│   └── requirements.txt        # Python dependencies
│
├── core/                        # C programs
│   ├── include/                # Header files
│   │   ├── common.h
│   │   ├── graph.h
│   │   ├── network.h
│   │   ├── queue.h
│   │   ├── routing.h
│   │   ├── searching.h
│   │   ├── sorting.h
│   │   ├── stack.h
│   │   └── trees.h
│   └── src/                    # C source files
│       ├── routing_wrapper.c   # Routing algorithms wrapper
│       ├── sorting_wrapper.c   # Sorting algorithms wrapper
│       ├── search_wrapper.c    # Searching algorithms wrapper
│       ├── network/            # Network management C code
│       ├── graph/              # Graph implementations
│       ├── routing/            # Routing algorithm implementations
│       ├── stack/              # Stack implementations
│       ├── queue/              # Queue implementations
│       ├── sorting/            # Sorting algorithm implementations
│       ├── searching/          # Searching algorithm implementations
│       └── trees/              # Tree implementations
│
├── data/                        # Persistent data storage
│   ├── routers.json            # Router data
│   ├── links.json              # Connection data
│   ├── packets.json            # Packet data
│   ├── activity_logs.json      # Activity log
│   └── tree.json               # BST data
│
├── docs/                        # Documentation
│   └── diagrams/
│
├── start.bat                    # Windows startup script
├── README.md
├── ARCHITECTURE_NOTES.md       # Architecture documentation
├── WINDOWS_SETUP.md             # Windows setup guide
├── QUICK_START.md               # Quick start guide
└── PROJECT_COMPLETION.md        # Project completion report
```

## Installation

### Prerequisites

- **Windows 10/11** (or compatible OS)
- **Python 3.8+** (tested with 3.14.6)
- **GCC** (MinGW) for C compilation
- **Modern web browser** (Chrome, Firefox, Edge)

### Setup Steps

1. **Clone or download the project**
   ```bash
   git clone <repository-url>
   cd IntelliRoute
   ```

2. **Install Python dependencies**
   ```bash
   cd backend
   pip install -r requirements.txt
   cd ..
   ```

3. **Verify GCC installation**
   ```bash
   gcc --version
   ```

4. **Compile C programs**
   ```bash
   cd core/src
   gcc -o sorting_wrapper.exe sorting_wrapper.c
   gcc -o search_wrapper.exe search_wrapper.c
   gcc -o routing_wrapper.exe routing_wrapper.c
   cd ../..
   ```

## Running the Application

### Method 1: Using the Startup Script (Recommended)

Double-click `start.bat` to launch both the frontend and backend servers automatically.

### Method 2: Manual Startup

**Terminal 1 - Backend:**
```bash
cd backend
python app.py
```

**Terminal 2 - Frontend:**
```bash
cd frontend
python server.py
```

### Access the Application

- **Frontend**: http://localhost:8081
- **Backend API**: http://localhost:5000
- **API Health Check**: http://localhost:5000/api/health

## API Documentation

### Network Management
- `GET /api/routers` - Get all routers
- `POST /api/routers` - Add new router
- `DELETE /api/routers/{id}` - Delete router
- `GET /api/links` - Get all connections
- `POST /api/links` - Add new connection
- `DELETE /api/links/{id}` - Delete connection
- `GET /api/network/graph` - Get graph data for visualization

### Routing Algorithms
- `POST /api/routing/bfs` - Run BFS algorithm
- `POST /api/routing/dfs` - Run DFS algorithm
- `POST /api/routing/dijkstra` - Run Dijkstra algorithm

### Packet Management
- `GET /api/packets` - Get all packets
- `POST /api/packets` - Generate new packet
- `POST /api/packets/process` - Process next packet

### Algorithms
- `POST /api/sorting/run` - Run sorting algorithm
- `POST /api/search/run` - Run search algorithm
- `POST /api/trees/operation` - Perform tree operation
- `POST /api/trees/traversal` - Perform tree traversal
- `GET /api/trees/get` - Get current tree state

### Dashboard
- `GET /api/dashboard/stats` - Get dashboard statistics
- `GET /api/dashboard/activity` - Get activity log
- `POST /api/reset` - Reset all data to initial state

## Usage Guide

### Dashboard
- View real-time network statistics
- Monitor system status and activity
- Preview network topology

### Network Management
- Add routers with IP addresses and status
- Create connections between routers with costs
- Delete routers and connections
- View router connections and status

### Network Topology
- Interactive network graph visualization
- Zoom, pan, and layout controls
- Edge cost labels with professional styling

### Routing Simulation
- Select source and destination routers
- Choose routing algorithm (BFS, DFS, Dijkstra)
- View traversal order, route path, and total cost
- Results from actual C program execution

### Packet Management
- Generate packets with source, destination, size, priority
- Process packets using FIFO queue
- Track packet status (pending/processed)
- View packet history

### Sorting & Searching
- Enter custom numbers or generate random array
- Select sorting algorithm (5 options)
- View comparisons, swaps, and execution time
- Perform linear or binary search
- Results from actual C program execution

### Tree Explorer
- Insert, delete, and search nodes in BST
- Perform tree traversals (inorder, preorder, postorder)
- View tree height and leaf node count
- Modern visualization with pan and zoom

### Performance Analysis
- Run algorithm benchmarks
- Compare sorting and searching performance
- View execution time charts
- Analyze algorithm complexity

## Data Persistence

All application data is stored in JSON files in the `data/` directory:

- `routers.json` - Router information
- `links.json` - Connection information
- `packets.json` - Packet information
- `activity_logs.json` - System activity log
- `tree.json` - Binary Search Tree state

## Troubleshooting

### Backend won't start
- Check if port 5000 is already in use
- Verify Python and Flask are installed
- Check for syntax errors in Python files

### Frontend won't load
- Check if port 8081 is already in use
- Verify the frontend server is running
- Check browser console for errors

### C program execution fails
- Verify GCC is installed and accessible
- Check C source file paths
- Review compilation errors in backend logs

### Data not persisting
- Check data directory permissions
- Verify JSON file integrity
- Use Reset Data button to restore defaults

## Development

### Building C Programs

```bash
cd core/src

# Sorting wrapper
gcc -o sorting_wrapper.exe sorting_wrapper.c

# Searching wrapper  
gcc -o search_wrapper.exe search_wrapper.c

# Routing wrapper
gcc -o routing_wrapper.exe routing_wrapper.c
```

### Running Tests

```bash
# Health check
curl http://localhost:5000/api/health

# Test sorting
curl -X POST http://localhost:5000/api/sorting/run \
  -H "Content-Type: application/json" \
  -d '{"algorithm":"bubble","array":[5,3,8,1,9,2]}'

# Test routing
curl -X POST http://localhost:5000/api/routing/bfs \
  -H "Content-Type: application/json" \
  -d '{"source":1,"destination":4}'
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

This project is licensed under the MIT License. See LICENSE file for details.

## Support

For issues, questions, or contributions, please refer to the project documentation or create an issue in the repository.

## Acknowledgments

- Cytoscape.js for network visualization
- Chart.js for performance charts
- Flask for the web framework
- GCC for C compilation

---

**Version:** 2.0.0
**Last Updated:** November 2026
**Status:** Production Ready
