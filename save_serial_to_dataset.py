"""
Small script used for logging data from an MCU with a 6DOF chip.
"""
from threading import Thread
import serial

# Serial interface
ser = serial.Serial("/dev/ttyACM3", 115200)

# File for logging the data
f = open('dataset', 'w')

# End of sequence symbol
eos = "eos\n"


def data_thread():
    """Data acquisition thread."""

    curr_num = 10

    # Sample number
    sample_num = (curr_num - 1)*60 + 1

    # Main loop
    while True:

        # Get data, if there is any
        data = ser.readline().decode("utf-8")
        ### DEBUG ###
        print(data)
        ### DEBUG ###

        # If it is an "end of sequence" symbol, increment sample number
        if data == eos:
            sample_num += 1

        # If it is a sample, append it to the end of the file
        else:
            f.write(str(sample_num) + "," + data)
            print("Sample: " + str(sample_num))


data_thread()
