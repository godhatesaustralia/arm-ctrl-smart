import serial
import csv
import time

# --- CONFIGURATION ---
PORT = "/dev/cu.usbmodem11201"   
BAUD = 115200

filename = time.strftime("angle_processingtime_%Y%m%d_%H%M%S.csv")

print(f"Connecting to {PORT} at {BAUD} baud...")
ser = serial.Serial(PORT, BAUD, timeout=1)
time.sleep(2)  

print("Logging data to ", {filename}, " , move joystick around to collect data.")

try:
    with open(filename, "w", newline="") as f:
        writer = csv.writer(f)
        
        #CSV column headers
        writer.writerow(["Timestamp_ms", "Processing_Time_us", "Servo_Angle"])

        while True:
            #Read line from the serial port
            line = ser.readline().decode("utf-8", errors="ignore").strip()
            
            if line:
                parts = line.split(",")
                if len(parts) == 3:
                    try:
                        timestamp = int(parts[0])
                        proc_time = int(parts[1])
                        angle = float(parts[2])

                        #Write row to CSV
                        writer.writerow([timestamp, proc_time, angle])
                        
                        #Print live status to your terminal window
                        print(f"[{timestamp}ms] Proc Time: {proc_time} us | Angle: {angle}°")
                        
                    except ValueError:
                        continue  #Skip any corrupted/partial text chunks

except KeyboardInterrupt:
    print(f"\nStopped by user. Your data has been successfully saved to {filename}!")
finally:
    ser.close()
