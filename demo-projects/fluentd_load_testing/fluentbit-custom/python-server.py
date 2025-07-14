#!/usr/bin/env python3
from flask import Flask, jsonify, request
import threading
import time
import os
import json
import random
import logging
from datetime import datetime

# Configure logging to write to a file that Fluent Bit can read
logging.basicConfig(
    level=logging.INFO,
    format='%(message)s',
    handlers=[
        logging.FileHandler('/app/logs/app.log'),
        logging.StreamHandler()  # Also log to stdout for debugging
    ]
)

app = Flask(__name__)
logger = logging.getLogger(__name__)

def generate_notification_request():
    """Generate a Notification Request log"""
    return {
        "timestamp": datetime.now().isoformat(),
        "log_type": "Notification Request",
        "request_id": f"req_{random.randint(1000, 9999)}",
        "user_id": f"user_{random.randint(100, 999)}",
        "notification_type": random.choice(["email", "sms", "push"]),
        "priority": random.choice(["high", "medium", "low"]),
        "message": "User action required",
        "container_id": os.environ.get('HOSTNAME', 'unknown')
    }

def generate_zigbee_response():
    """Generate a Zigbee Response log"""
    return {
        "timestamp": datetime.now().isoformat(),
        "log_type": "Zigbee Response",
        "device_id": f"zigbee_{random.randint(1000, 9999)}",
        "network_id": f"net_{random.randint(100, 999)}",
        "signal_strength": random.randint(-80, -20),
        "battery_level": random.randint(10, 100),
        "device_type": random.choice(["sensor", "switch", "dimmer", "thermostat"]),
        "status": random.choice(["online", "offline", "low_battery"]),
        "data_payload": f"0x{random.randint(1000, 9999):04x}",
        "container_id": os.environ.get('HOSTNAME', 'unknown')
    }

def generate_placeholder_data():
    """Generate Placeholder Data log"""
    return {
        "timestamp": datetime.now().isoformat(),
        "log_type": "Placeholder Data",
        "session_id": f"session_{random.randint(10000, 99999)}",
        "operation": random.choice(["create", "read", "update", "delete"]),
        "resource": random.choice(["user", "product", "order", "inventory"]),
        "duration_ms": random.randint(10, 1000),
        "status_code": random.choice([200, 201, 400, 404, 500]),
        "bytes_processed": random.randint(100, 10000),
        "container_id": os.environ.get('HOSTNAME', 'unknown')
    }

def emit_logs():
    """Continuously emit different types of logs"""
    while True:
        try:
            # Randomly choose log type with different probabilities
            rand = random.random()
            if rand < 0.4:  # 40% chance
                log_data = generate_notification_request()
            elif rand < 0.7:  # 30% chance
                log_data = generate_zigbee_response()
            else:  # 30% chance
                log_data = generate_placeholder_data()
            
            # Emit the log as JSON
            logger.info(json.dumps(log_data))
            
            # Wait between 0.5 to 2 seconds before next log
            time.sleep(random.uniform(0.5, 2.0))
            
        except Exception as e:
            logger.error(f"Error generating log: {e}")
            time.sleep(1)

@app.route('/health', methods=['GET'])
def health_check():
    return jsonify({
        'status': 'healthy',
        'container_id': os.environ.get('HOSTNAME', 'unknown'),
        'timestamp': time.time()
    })

@app.route('/metrics', methods=['GET'])
def metrics():
    return jsonify({
        'container_id': os.environ.get('HOSTNAME', 'unknown'),
        'uptime': time.time(),
        'fluent_bit_status': 'running',
        'log_types': ['Notification Request', 'Zigbee Response', 'Placeholder Data']
    })

@app.route('/logs/stats', methods=['GET'])
def log_stats():
    """Endpoint to get log generation statistics"""
    return jsonify({
        'container_id': os.environ.get('HOSTNAME', 'unknown'),
        'log_file': '/tmp/app.log',
        'log_types_generated': ['Notification Request', 'Zigbee Response', 'Placeholder Data'],
        'generation_rate': 'every 0.5-2 seconds'
    })

def run_server():
    app.run(host='0.0.0.0', port=8080, debug=False)

if __name__ == '__main__':
    # Start the Flask server in a separate thread
    server_thread = threading.Thread(target=run_server, daemon=True)
    server_thread.start()
    print("Python server started on port 8080")
    
    # Start log emission in a separate thread
    log_thread = threading.Thread(target=emit_logs, daemon=True)
    log_thread.start()
    print("Log emission started")
    
    # Keep the main thread alive
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("Shutting down...")
