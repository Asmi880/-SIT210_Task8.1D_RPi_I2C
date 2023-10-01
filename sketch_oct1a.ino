# Import the smbus and time libraries for I2C communication and time management.
import smbus
import time

# Define I2C address and control codes.
address = 0x23   # I2C device address
start = 0x01     # Start command
stop = 0x00      # Stop command
reset = 0x07     # Reset command

# Initialize the I2C bus object.
bus = smbus.SMBus(1)  # Use I2C bus 1

# Function to read light intensity from the I2C device.
def light_read():
    new_add = bus.read_i2c_block_data(address, start)  # Read data from the I2C device.
    value = conversion_of_light(new_add)               # Convert raw data to light intensity.
    return value

# Function to convert raw sensor data to light intensity.
def conversion_of_light(new_add):
    converted = ((new_add[1] + (256 * new_add[0])) / 1.2)  # Perform the conversion.
    return converted

# Main program loop.
try:
    while True:
        intensity = light_read()  # Read the light intensity.
        print(f"Reading: {intensity}")

        # Determine and print the intensity level.
        print("Intensity:")
        if intensity >= 4500:
            print("Too bright")
        elif 500 <= intensity < 4500:
            print("Bright")
        elif 90 <= intensity < 500:
            print("Medium")
        elif 50 <= intensity < 90:
            print("Dark")
        elif intensity < 50:
            print("Too Dark")
        time.sleep(1)  # Wait for 1 second between readings.

except KeyboardInterrupt:
    print("ENDING")  # Handle the KeyboardInterrupt and exit the program gracefully.
