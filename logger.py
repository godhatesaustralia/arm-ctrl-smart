import serial
import csv
import time

# --- CONFIGURATION ---
PORT = "/dev/cu.usbmodem11201"        # Update this to match your Arduino port (e.g., "/dev/cu.usbmodem..." on Mac)
BAUD = 115200

# Create a unique filename with the current date and time
filename = time.strftime("robot_log_%Y%m%d_%H%M%S.csv")

print(f"Connecting to {PORT} at {BAUD} baud...")
ser = serial.Serial(PORT, BAUD, timeout=1)
time.sleep(2)  # Give Arduino time to reset after opening connection

print(f"Logging data to '{filename}'. Move your joystick around!")
print("Press Ctrl+C in your terminal to stop logging and save the file.\n")

try:
    with open(filename, "w", newline="") as f:
        writer = csv.writer(f)
        
        # Write the CSV column headers
        writer.writerow(["Timestamp_ms", "Processing_Time_us", "Servo_Angle"])

        while True:
            # Read a line from the serial port
            line = ser.readline().decode("utf-8", errors="ignore").strip()
            
            if line:
                parts = line.split(",")
                if len(parts) == 3:
                    try:
                        timestamp = int(parts[0])
                        proc_time = int(parts[1])
                        angle = float(parts[2])

                        # Write row to CSV
                        writer.writerow([timestamp, proc_time, angle])
                        
                        # Print live status to your terminal window
                        print(f"[{timestamp}ms] Proc Time: {proc_time} us | Angle: {angle}°")
                        
                    except ValueError:
                        continue  # Skip any corrupted/partial text chunks

except KeyboardInterrupt:
    print(f"\nStopped by user. Your data has been successfully saved to {filename}!")
finally:
    ser.close()