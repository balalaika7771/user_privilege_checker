@echo off
start /b node app.js
timeout /t 2
start http://localhost:3000
