#!/bin/bash

echo "Starting Python server in background..."
python3 /app/python-server.py &
PYTHON_PID=$!

echo "Starting Fluent Bit..."
exec fluent-bit --config=/fluent-bit/etc/fluent-bit.conf
