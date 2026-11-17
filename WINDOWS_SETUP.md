# Windows Setup Guide

This guide provides step-by-step instructions for setting up and running the Smart Network Routing and Management System on Windows.

## Prerequisites

Before installation, ensure you have the following software installed:

### 1. Python 3.8+

**Check if installed:**
```bash
python --version
```

**Expected output:**
```
Python 3.14.6
```

**If not installed:**
- Download from [python.org/downloads](https://www.python.org/downloads/)
- Install Python 3.10 or higher
- **Important:** Check "Add Python to PATH" during installation

### 2. GCC Compiler (MinGW)

**Check if installed:**
```bash
gcc --version
```

**Expected output:**
```
gcc.exe (MinGW.org GCC-6.3.0-1) 6.3.0
```

**If not installed:**
- Download MinGW-w64 from [mingw-w64.org](https://www.mingw-w64.org/)
- Or install via MSYS2 from [msys2.org](https://www.msys2.org/)
- Add GCC to your system PATH

### 3. Modern Web Browser

- Google Chrome (recommended)
- Mozilla Firefox
- Microsoft Edge

## Installation Steps

### Step 1: Download and Extract Project

1. Download or clone the project repository
2. Extract to your preferred location
3. Navigate to the project directory

### Step 2: Install Python Dependencies

Open Command Prompt or Git Bash in the project directory:

```bash
cd backend
pip install -r requirements.txt
cd ..
```

**Expected output:**
```
Requirement already satisfied: flask in ...
Requirement already satisfied: flask-cors in ...
```

### Step 3: Compile C Programs

Navigate to the C source directory and compile the wrapper programs:

```bash
cd core/src

# Compile sorting wrapper
gcc -o sorting_wrapper.exe sorting_wrapper.c

# Compile searching wrapper
gcc -o search_wrapper.exe search_wrapper.c

# Compile routing wrapper
gcc -o routing_wrapper.exe routing_wrapper.c

cd ../..
```

**Expected output:** No errors, executables created in `core/src/`

### Step 4: Verify Installation

Test the backend health endpoint:

```bash
cd backend
python app.py
```

In another terminal, test the API:

```bash
curl http://localhost:5000/api/health
```

**Expected response:**
```json
{
  "status": "healthy"
}
```

Stop the backend with `Ctrl+C` after testing.

## Running the Application

### Method 1: Using the Startup Script (Recommended)

1. Double-click `start.bat` in the project root
2. Two command windows will open automatically:
   - **Flask Backend** (port 5000)
   - **Frontend Server** (port 8081)
3. Wait 3-5 seconds for servers to start
4. Open your browser and navigate to: **http://localhost:8081**
5. When done, press any key in the startup window to stop servers

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

**Access the application:**
- Frontend: http://localhost:8081
- Backend API: http://localhost:5000

## Verification

### 1. Test Backend Health

```bash
curl http://localhost:5000/api/health
```

**Expected response:**
```json
{
  "status": "healthy"
}
```

### 2. Test C Integration

Test sorting algorithm:

```bash
curl -X POST http://localhost:5000/api/sorting/run \
  -H "Content-Type: application/json" \
  -d '{"algorithm":"bubble","array":[5,3,8,1,9,2]}'
```

**Expected response:**
```json
{
  "success": true,
  "data": {
    "original": [5,3,8,1,9,2],
    "sorted": [1,2,3,5,8,9],
    "comparisons": 15,
    "swaps": 8,
    "time": 0.001
  }
}
```

### 3. Test Frontend

Open browser: **http://localhost:8081**

**Expected:**
- Dark-themed dashboard loads
- Sidebar navigation is visible
- No console errors (press F12 to check)
- System status shows "Online"

## Common Issues and Solutions

### Issue 1: Port Already in Use

**Error:**
```
OSError: [WinError 10048] Address already in use
```

**Solution:**
Find and kill the process using the port:

```bash
# For port 5000 (Backend)
netstat -ano | findstr :5000
taskkill /PID <PID> /F

# For port 8081 (Frontend)
netstat -ano | findstr :8081
taskkill /PID <PID> /F
```

**Alternative:**
Change the port in `frontend/server.py` if port 8081 is in use.

### Issue 2: Python Module Not Found

**Error:**
```
ModuleNotFoundError: No module named 'flask'
```

**Solution:**
```bash
pip install flask flask-cors
```

### Issue 3: GCC Not Found

**Error:**
```
'gcc' is not recognized as an internal or external command
```

**Solution:**
1. Add MinGW to system PATH
2. Or use full path: `C:\MinGW\bin\gcc.exe`
3. Reinstall MinGW if needed

### Issue 4: Permission Denied

**Error:**
```
PermissionError: [WinError 5] Access is denied
```

**Solution:**
1. Run Command Prompt as Administrator
2. Or check file/folder permissions
3. Ensure antivirus is not blocking execution

### Issue 5: Frontend Not Loading

**Symptoms:**
- Blank page
- 404 errors
- Styles not loading

**Solution:**
1. Check frontend server is running
2. Verify file paths in index.html
3. Check browser console for errors (F12)
4. Clear browser cache

### Issue 6: CORS Errors

**Error in browser console:**
```
Access to XMLHttpRequest has been blocked by CORS policy
```

**Solution:**
1. Verify Flask-CORS is installed
2. Check backend is running on port 5000
3. Verify CORS configuration in app.py

### Issue 7: C Programs Not Working

**Symptoms:**
- Sorting/searching returns errors
- Routing returns errors

**Solution:**
1. Verify C programs are compiled: `core/src/*.exe` should exist
2. Recompile if needed:
   ```bash
   cd core/src
   gcc -o sorting_wrapper.exe sorting_wrapper.c
   gcc -o search_wrapper.exe search_wrapper.c
   gcc -o routing_wrapper.exe routing_wrapper.c
   ```
3. Check for compilation errors

## Development Workflow

### Adding New C Programs

1. Create `.c` file in `core/src/`
2. Create corresponding header in `core/include/`
3. Compile manually:
   ```bash
   cd core/src
   gcc -I../include your_program.c -o your_program.exe
   ```
4. Test execution:
   ```bash
   ./your_program.exe
   ```
5. Integrate with Flask backend in `backend/routes/`

### Adding New API Endpoints

1. Create route file in `backend/routes/`
2. Import in `backend/app.py`
3. Register blueprint
4. Add corresponding frontend API call in `frontend/js/api.js`
5. Update UI in `frontend/js/app.js`

### Resetting Data

Use the "Reset Data" button in the top navigation bar, or manually delete JSON files in `data/` folder.

## Performance Tips

1. **Close unused terminals** to free up resources
2. **Disable debug mode** in production (set `debug=False` in app.py)
3. **Use production server** like Gunicorn for Python (not needed for development)
4. **Clear browser cache** if experiencing slow loads

## Security Notes

⚠️ **Development Mode Only:**
- Do not use in production without security hardening
- Debug mode exposes sensitive information
- No authentication implemented
- SQL injection not applicable (using JSON files)

## Uninstallation

To completely remove the project:

1. Stop all running servers
2. Delete the project folder
3. Remove Python virtual environment (if created)
4. No system-wide changes were made

## Additional Resources

- **Flask Documentation:** [flask.palletsprojects.com](https://flask.palletsprojects.com/)
- **Cytoscape.js:** [js.cytoscape.org](https://js.cytoscape.org/)
- **Chart.js:** [chartjs.org](https://www.chartjs.org/)
- **GCC Documentation:** [gcc.gnu.org](https://gcc.gnu.org/onlinedocs/)

## Support

For issues specific to this project:
1. Check the README.md
2. Review ARCHITECTURE_NOTES.md
3. Check browser console (F12) for frontend errors
4. Check backend terminal for Python errors
5. Verify all prerequisites are installed

---

**Last Updated:** November 2026  
**Platform:** Windows 10/11  
**Tested On:** MSYS_NT-10.0-19045 with GCC 6.3.0 and Python 3.14.6
