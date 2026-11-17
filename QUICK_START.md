# Quick Start Guide

## Running the Application

### Option 1: Automatic (Recommended)
1. Double-click `start.bat`
2. Wait 3-5 seconds for servers to start
3. Open browser: http://localhost:8081
4. When done, press any key in the startup window

### Option 2: Manual
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

**Access:** http://localhost:8081

---

## What's Included

### Completed Features
1. **Network Management** - Add/delete routers, manage connections
2. **Network Topology** - Visualize network graph
3. **Routing Simulation** - BFS, DFS, Dijkstra algorithms
4. **Packet Management** - FIFO queue processing
5. **Sorting Algorithms** - Bubble, Selection, Insertion, Merge, Quick
6. **Searching Algorithms** - Linear and Binary Search
7. **Tree Explorer** - BST with traversals
8. **Performance Analysis** - Algorithm comparison charts

### C Programs (All Implemented)
- Linked Lists (Router storage)
- Stacks (Array & Linked List)
- Queues (Array, Linked List, Circular)
- Graphs (Adjacency Matrix & List)
- Binary Search Tree
- All Sorting Algorithms
- All Searching Algorithms
- Routing Algorithms (BFS, DFS, Dijkstra)

**Note:** The C programs are complete implementations integrated with the web application. See [C_PROGRAMS_GUIDE.md](C_PROGRAMS_GUIDE.md) for compilation details.

---

## How to Use

### 1. Dashboard
- View network statistics
- Monitor system status
- Check recent activities

### 2. Network Management
- Click "Add Router" to create routers
- Click "Add Connection" to link routers
- View all routers and connections
- Delete routers/connections as needed

### 3. Network Topology
- Visualize your network graph
- Refresh to see updates
- Interactive network diagram

### 4. Routing Simulation
- Select source and destination routers
- Choose algorithm (BFS, DFS, Dijkstra)
- Click "Run Algorithm"
- View traversal order and calculated route

### 5. Packet Management
- Generate packets with size and priority
- Process packets using FIFO queue
- Track packet status (pending/processed)

### 6. Sorting & Searching
- Enter numbers or click "Random"
- Select sorting algorithm
- Click "Sort" to see results
- View comparisons, swaps, and time
- For search: enter element and click "Search"

### 7. Tree Explorer
- Insert, delete, or search nodes
- Click traversal buttons (Inorder, Preorder, Postorder)
- View tree height and leaf nodes

### 8. Performance Analysis
- Click "Run Benchmark"
- View sorting algorithm comparison chart
- View search algorithm comparison chart

---

## Troubleshooting

### Backend won't start
```bash
# Check if port 5000 is in use
netstat -ano | findstr :5000
# Kill the process if needed
taskkill /PID <PID> /F
```

### Frontend won't start
```bash
# Check if port 8081 is in use
netstat -ano | findstr :8081
# Kill the process if needed
taskkill /PID <PID> /F
```

### C compilation errors
- Verify GCC is installed: `gcc --version`
- Check C file paths in `core/src/`

### API errors
- Check backend is running on port 5000
- Check browser console (F12) for errors
- Verify CORS is enabled in backend

---

## Project Structure

```
IntelliRoute/
├── frontend/          # Web interface (HTML/CSS/JS)
├── backend/           # Flask API
├── core/              # C programs
│   ├── include/       # Header files
│   └── src/           # Source files
├── data/              # JSON data storage
├── start.bat          # Windows startup script
└── Documentation files
```

---

## Documentation

- **README.md** - Full project documentation
- **WINDOWS_SETUP.md** - Detailed setup instructions
- **ARCHITECTURE_NOTES.md** - System architecture
- **C_PROGRAMS_GUIDE.md** - C program compilation guide
- **PROJECT_COMPLETION.md** - Project completion report

---

## Verification

Test the system is working:

1. **Backend Health:**
   ```bash
   curl http://localhost:5000/api/health
   ```
   Expected: `{"status": "healthy"}`

2. **Frontend Loading:**
   Open http://localhost:8081 in browser
   Expected: Dark-themed dashboard loads

3. **Sorting Test:**
   Go to Sorting & Searching page
   Enter: `5, 3, 8, 1, 9, 2`
   Click "Sort"
   Expected: Sorted array displayed

---

## Tips

1. **Reset Data:** Use "Reset Data" button in top navigation
2. **Sample Network:** Click reset to load sample routers/connections
3. **Performance:** Close unused terminals for better performance
4. **Debugging:** Check browser console (F12) for frontend errors
5. **Backend Logs:** Check backend terminal for Python errors

---

## Support

For issues:
1. Check WINDOWS_SETUP.md troubleshooting section
2. Verify all prerequisites are installed
3. Check documentation files
4. Review error messages in terminals

---

**Enjoy using the Smart Network Routing and Management System!**
