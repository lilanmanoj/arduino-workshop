## Firebase Connect - Send realtime temperature/humidity to Firebase Realtime DB

Sending realtime temperature/humidity to Firebase Realtime DB and turn on/off the built-in LED according to an key/value pair in same DB.

## Instructions
1. Edit `env.sh` with appropriate values
2. Source the `env.sh` using:
```
source env.sh
```
3. Run platformio project for `esp32-s3-devkit-c1` using:
```
pio run -e esp32-s3-devkitc-1 -t upload
```
4. Serial monitor:
```
# Get the port
pio device list

# Start serial monitor
pio device monitor -p /dev/ttyACM0 -b 115200
```
