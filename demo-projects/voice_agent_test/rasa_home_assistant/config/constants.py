"""
Configuration constants for the Rasa Smart Home Assistant
"""
import os

# NATS Configuration
NATS_HOST = "10.1.4.238"
NATS_PORT = 9769
NATS_TOKEN = "keus-iot-platform"
SITE_ID = "Keus-199786d6-cf1f-47a7-87d9-af7f2a3ab9b0"

# Data file paths
# Go up two levels from config/
_BASE_DIR = os.path.dirname(os.path.dirname(__file__))
ROOMS_DATA_PATH = os.path.join(_BASE_DIR, "data", "rooms.json")
SCENES_DATA_PATH = os.path.join(_BASE_DIR, "data", "scenes.json")
