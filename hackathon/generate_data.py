import csv
import random
from datetime import datetime, timedelta

# Configuration
CAMERAS = ["CAM_001", "CAM_002", "CAM_003", "CAM_004"]
AREAS = ["Front Door", "Backyard", "Garage", "Living Room", "Driveway"]
HOME_STATES = ["Home", "Away"]
NUM_RECORDS = 5000

def generate_motion_data(file_name="camera_motion_data.csv"):
    start_time = datetime.now()
    
    with open(file_name, mode='w', newline='') as file:
        writer = csv.writer(file)
        # Writing the header
        writer.writerow(["CameraID", "Timestamp", "MotionDetected", "Duration", "Area", "HomeState"])
        
        for i in range(NUM_RECORDS):
            camera_id = random.choice(CAMERAS)
            # Stagger timestamps by random intervals
            timestamp = (start_time - timedelta(minutes=random.randint(1, 1000))).strftime("%Y-%m-%d %H:%M:%S")
            
            motion_detected = random.choice([True, True, True, False]) # Weighted towards True
            
            # Logic: Away events might be longer or more critical
            home_state = random.choice(HOME_STATES)
            if home_state == "Away":
                duration = random.randint(10, 300) # Longer events when away
            else:
                duration = random.randint(1, 45)   # Shorter "background" events when home
            
            area = random.choice(AREAS)
            
            writer.writerow([camera_id, timestamp, motion_detected, duration, area, home_state])

    print(f"Successfully generated {NUM_RECORDS} records to {file_name}")

if __name__ == "__main__":
    generate_motion_data()