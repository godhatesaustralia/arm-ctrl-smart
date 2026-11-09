import csv
import glob
import os
import matplotlib.pyplot as plt

# Automatically find the most recent robot log CSV file in your folder
list_of_files = glob.glob('robot_log_*.csv')
if not list_of_files:
    print("No robot log CSV files found in this folder! Make sure you ran the logger first.")
    exit()

latest_file = max(list_of_files, key=os.path.getctime)
print(f"Loading data from: {latest_file}")

# Lists to hold our data columns
timestamps = []
processing_times = []
servo_angles = []

# Read the CSV file
with open(latest_file, "r") as f:
    reader = csv.reader(f)
    next(reader) # Skip the header row (Timestamp_ms, Processing_Time_us, Servo_Angle)
    
    for row in reader:
        if len(row) == 3:
            timestamps.append(float(row[0]))
            processing_times.append(float(row[1]))
            servo_angles.append(float(row[2]))

# Create a figure with two stacked charts (sharing the X axis timeline)
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 6), sharex=True)

# Top Plot: Servo Angle
ax1.plot(timestamps, servo_angles, color="tab:blue", linewidth=1.5)
ax1.set_ylabel("Servo Angle (°)")
ax1.set_title(f"PoC Performance Log — {latest_file}")
ax1.grid(True)

# Bottom Plot: Processing Time (Microseconds)
ax2.plot(timestamps, processing_times, color="tab:orange", linewidth=1.5)
ax2.set_ylabel("Proc Time (µs)")
ax2.set_xlabel("Time (milliseconds)")
ax2.grid(True)

# Add a horizontal reference line for 1,000 microseconds (1 millisecond)
ax2.axhline(1000, color="red", linestyle="--", alpha=0.7, label="1ms Target Limit")
ax2.legend(loc="upper right")

plt.tight_layout()
plt.show()