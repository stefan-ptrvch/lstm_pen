"""
Small script used for predicting from MCU with chip, using overfitted model
"""
from keras.models import load_model
import numpy as np
import serial

from time import time

# Serial interface
ser = serial.Serial("/dev/ttyACM3", 115200)

# End of sequence symbol
eos = "eos\n"

# Load the model
model = load_model("./gml/model_1300.h5")

# Data shape
NUM_FEATURES = 6
NUM_STEPS = 205

def data_thread():
    """Data acquisition thread."""

    # Dummy array for stacking
    dummy = np.zeros((1, NUM_FEATURES))
    zeros_dummy = np.zeros((NUM_STEPS, NUM_FEATURES))

    # Main loop
    while True:

        # Get data, if there is any
        data = ser.readline().decode("utf-8")

        # If it is an "end of sequence" symbol, predict
        if data == eos:
            # Pop unneded row off of top, and keep only 150 samples
            dummy = dummy[1:]

            # Number of samples we've got
            num_samples = dummy.shape[0]
            if num_samples > NUM_STEPS:
                num_samples = NUM_STEPS

            # Pad with zeros
            zeros_dummy[:num_samples] = dummy[:num_samples]

            # Reshape into 3D array
            zeros_dummy = zeros_dummy.reshape((1, NUM_STEPS, NUM_FEATURES))

            # Predict
            prediction = model.predict(zeros_dummy)

            # Print letter to stdout
            print(prediction.argmax())

            # Reinitialize dummy
            dummy = np.zeros((1, NUM_FEATURES))

            # Reinitialize zeros matrix
            zeros_dummy = np.zeros((NUM_STEPS, NUM_FEATURES))

        # If it is a sample, append to numpy array
        else:
            # Convert string to numpy array
            array = np.fromstring(data, sep=',')
            dummy = np.vstack((dummy, array))


data_thread()
