Working on rules engine system for camera motion events.
On the basis of motion events from cameras, we want the system to smart decide on rules to trigger action like sending alerts

# camera motion data schema
1. CameraID: Unique identifier for each camera
2. Timestamp: Date and time of the motion event
3. MotionDetected: Boolean indicating if motion was detected
5. Duration: Duration of the motion event in seconds
6. Area
5. HomeState: "Home", "Away"