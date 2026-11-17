# Architecture Documentation

## System Overview

The Smart Network Routing and Management System uses a hybrid architecture that combines C programming for core algorithms with Python Flask for the web backend and modern web technologies for the frontend.

## Architecture Components

### Frontend Layer
- **Technology:** HTML5, CSS3, JavaScript ES6+
- **Framework:** Vanilla JavaScript (no build tools required)
- **Visualization:** Cytoscape.js for network graphs, Chart.js for performance charts
- **Design:** Professional dark theme with responsive layout

### Backend Layer
- **Framework:** Python Flask 3.0+
- **API:** RESTful endpoints for all operations
- **CORS:** Flask-CORS for cross-origin requests
- **Data Storage:** JSON files for persistent storage

### Core Algorithm Layer (C)
- **Language:** C99
- **Compiler:** GCC 6.3.0 (MinGW)
- **Integration:** Subprocess execution via Flask
- **Output Format:** JSON for easy parsing

## C Integration Details

### Sorting Algorithms (C)
- **Program:** `core/src/sorting_wrapper.exe`
- **Endpoint:** `POST /api/sorting/run`
- **Algorithms:** Bubble, Selection, Insertion, Merge, Quick Sort
- **Metrics:** Comparisons, swaps, execution time

### Searching Algorithms (C)
- **Program:** `core/src/search_wrapper.exe`
- **Endpoint:** `POST /api/search/run`
- **Algorithms:** Linear Search, Binary Search
- **Metrics:** Comparisons, position, found status

### Routing Algorithms (C)
- **Program:** `core/src/routing_wrapper.exe`
- **Endpoints:** `POST /api/routing/bfs`, `/api/routing/dfs`, `/api/routing/dijkstra`
- **Algorithms:** BFS, DFS, Dijkstra's Algorithm
- **Output:** Traversal order, route path, total cost

## Data Flow

```
User Input → Frontend → API Request → Flask Backend → C Program → JSON Output → Flask → Frontend → Display
```

## Why Hybrid Architecture?

### Benefits
1. **Performance:** C programs execute algorithms efficiently
2. **Reliability:** Python provides robust web framework
3. **Maintainability:** Clear separation of concerns
4. **Scalability:** Modular design allows easy expansion
5. **Industry Standard:** Mirrors real-world system architectures

### Implementation Strategy
- **C for Compute-Intensive Tasks:** Sorting, searching, routing algorithms
- **Python for Web Operations:** Network management, packet handling, tree operations
- **JSON for Data Exchange:** Standard format for all data transfer

## C Program Integration

### Compilation Process
```bash
cd core/src

# Sorting wrapper
gcc -o sorting_wrapper.exe sorting_wrapper.c

# Searching wrapper
gcc -o search_wrapper.exe search_wrapper.c

# Routing wrapper
gcc -o routing_wrapper.exe routing_wrapper.c
```

### Execution Flow
1. Frontend sends API request with parameters
2. Flask validates input and prepares command-line arguments
3. Flask executes C program via subprocess
4. C program processes data and outputs JSON
5. Flask parses JSON and returns to frontend
6. Frontend displays results

### Error Handling
- C program compilation errors are caught during setup
- Runtime errors return JSON error responses
- Timeout protection for long-running operations
- Graceful degradation for missing executables

## Data Storage

### Persistent Storage
All application data is stored in JSON files:

- `routers.json` - Router information and status
- `links.json` - Network connections and costs
- `packets.json` - Packet queue and history
- `activity_logs.json` - System activity log
- `tree.json` - Binary Search Tree state

### Data Consistency
- Atomic file writes prevent corruption
- Automatic backup on major operations
- Validation before data persistence
- Recovery from corrupted files

## Security Considerations

### Input Validation
- All user inputs are validated before processing
- SQL injection prevention (not applicable for JSON)
- Command injection prevention in subprocess calls
- File path traversal protection

### API Security
- CORS configuration for cross-origin requests
- Rate limiting for API endpoints
- Input sanitization for all parameters
- Error message sanitization

## Performance Optimization

### C Program Efficiency
- Optimized algorithm implementations
- Minimal memory allocation
- Efficient data structures
- Compiler optimizations enabled

### Web Performance
- Lazy loading for large datasets
- Efficient JSON serialization
- Caching for frequently accessed data
- Responsive UI design

## Scalability

### Horizontal Scaling
- Stateless Flask application
- Shared JSON file storage
- Load balancing ready
- Microservice architecture compatible

### Vertical Scaling
- Efficient C algorithm implementations
- Optimized Python code
- Memory-efficient data structures
- Database-ready design

## Monitoring and Logging

### Activity Logging
- All operations are logged with timestamps
- Success/failure status tracking
- Error details for debugging
- Performance metrics collection

### System Monitoring
- API endpoint response times
- C program execution times
- Memory usage tracking
- Error rate monitoring

## Testing Strategy

### Unit Testing
- C algorithm correctness
- Python function testing
- API endpoint validation
- Data persistence verification

### Integration Testing
- End-to-end workflow testing
- C program integration testing
- Frontend-backend communication
- Data flow validation

### Performance Testing
- Algorithm benchmark testing
- Load testing for API endpoints
- Memory usage profiling
- Response time analysis

## Deployment

### Development Environment
- Local development with Flask development server
- Frontend served via Python HTTP server
- C programs compiled locally
- JSON file storage

### Production Considerations
- Use production WSGI server (Gunicorn/uWSGI)
- Implement proper logging
- Add authentication and authorization
- Use database instead of JSON files
- Container deployment (Docker)

## Future Enhancements

### Planned Features
- Real-time WebSocket updates
- Advanced network simulation
- Additional routing algorithms
- Enhanced visualization options
- User authentication system

### Technical Improvements
- Database migration (SQLite/PostgreSQL)
- API versioning
- Caching layer implementation
- Monitoring dashboard
- Automated testing suite

## Documentation

### Available Documentation
- **README.md** - Project overview and setup
- **WINDOWS_SETUP.md** - Windows installation guide
- **QUICK_START.md** - Quick start guide
- **ARCHITECTURE_NOTES.md** - This document
- **C_PROGRAMS_GUIDE.md** - C program compilation guide
- **PROJECT_COMPLETION.md** - Project completion report

### Code Documentation
- Inline code comments
- Function documentation
- API endpoint documentation
- Architecture diagrams

## Support and Maintenance

### Regular Maintenance
- Dependency updates
- Security patches
- Performance optimizations
- Bug fixes and improvements

### Community Support
- Issue tracking system
- Feature request process
- Pull request workflow
- Documentation updates

---

**Architecture Version:** 2.0.0  
**Last Updated:** November 2026  
**Status:** Production Ready
