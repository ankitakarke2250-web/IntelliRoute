@echo off
echo Starting Smart Network Routing and Management System...
echo.

echo Starting Flask Backend...
start "Flask Backend" cmd /k "cd backend && python app.py"

echo Waiting for backend to start...
timeout /t 3 /nobreak > nul

echo Starting Frontend Server...
start "Frontend Server" cmd /k "cd frontend && python server.py"

echo.
echo ========================================
echo System Started Successfully!
echo ========================================
echo Frontend: http://localhost:8081
echo Backend API: http://localhost:5000
echo ========================================
echo.
echo Press any key to stop all servers...
pause > nul

echo Stopping servers...
taskkill /FI "WINDOWTITLE eq Flask Backend*" /T /F > nul 2>&1
taskkill /FI "WINDOWTITLE eq Frontend Server*" /T /F > nul 2>&1
echo Servers stopped.
