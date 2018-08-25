"""
Trying to make an LSTM which can tell the difference between a couple different
letters.
"""

from __future__ import print_function

import argparse
import pandas as pd
import numpy as np
import h5py
import pickle
from datetime import datetime
from sklearn.model_selection import train_test_split
from keras.models import Sequential
from keras.layers import Dense, LSTM
from sklearn.preprocessing import OneHotEncoder
from sklearn.metrics import confusion_matrix, f1_score
from tensorflow.python.lib.io import file_io
from pandas.compat import StringIO

MODEL_NAME = "model_150"
HISTORY_NAME = "history_150"

def train_model(train_file='gs://lstm-pencil-data/dataset_digits_5ms',
                job_dir='./tmp/mnist_mlp', **args):

    # Set seed for reproducibility
    np.random.seed(7)
    train_file='gs://lstm-pencil-data/dataset_digits_5ms'
    job_dir='gs://lstm-pencil-data/models'
    # Load data
    print("Dataset path is " + train_file)
    f = file_io.FileIO(train_file, mode='r' )
    print("File is " + str(f))
    df = pd.read_csv(StringIO(f.read()))
    logs_path = job_dir + '/logs/' + datetime.now().isoformat()

    ### FOR TESTING, DROP SOME SAMPLES ###
    #  df = df[(df["digit"] == 1) | (df["digit"] == 2) | (df["digit"] == 3) |
            #  (df["digit"] == 4) | (df["digit"] == 5) | (df["digit"] == 6) |
            #  (df["digit"] == 7) | (df["digit"] == 8) | (df["digit"] == 9) |
    every_nth = 1
    ### FOR TESTING, DROP SOME SAMPLES ###

    # Get sequence with most samples (probably an O)
    NUM_STEPS = df["sample"].value_counts().max()
    NUM_FEATURES = 6
    NUM_CLASSES = df["digit"].unique().size

    # Dummy matrix for zero-padding
    dummy = np.zeros((NUM_STEPS, NUM_FEATURES + 1))

    # Other dummy for stacking
    stack_dummy = np.zeros((1, NUM_FEATURES + 1))

    # Go through all sequences and pad with zeros
    for index in df["sample"].unique()[::every_nth]:
        sequence = df[df["sample"] == index]
        num_samples = sequence.shape[0]
        dummy[:num_samples, :NUM_FEATURES] = sequence[["xa", "ya", "za", "xg",
                                                       "yg", "zg"]].values
        dummy[:, NUM_FEATURES] = sequence["digit"].unique()[0]
        stack_dummy = np.vstack((stack_dummy, dummy))

        # Fill dummy with zeros again
        dummy = np.zeros((NUM_STEPS, NUM_FEATURES + 1))

    # Drop first row of stack dummy
    stack_dummy = stack_dummy[1:]

    # Get feature matrix and reshape it into 3D array
    features = stack_dummy[:, :NUM_FEATURES]
    num_samples = features.shape[0]//NUM_STEPS
    features = features.reshape((num_samples, NUM_STEPS, NUM_FEATURES))

    # Make a label vector and do one-hot encoding on it
    labels = stack_dummy[:, NUM_FEATURES][::NUM_STEPS]
    encoder = OneHotEncoder(sparse=False)
    labels = encoder.fit_transform(labels.reshape((num_samples, 1)))

    # Split data into training and test sets
    X_train, X_test, y_train, y_test = train_test_split(features, labels)

    # Build LSTM model
    model = Sequential()
    model.add(LSTM(150, input_shape=(NUM_STEPS, NUM_FEATURES)))
    model.add(Dense(NUM_CLASSES, activation="softmax"))
    model.compile(loss="categorical_crossentropy", optimizer="adam",
                  metrics=["accuracy"])
    print(model.summary())

    NUM_EPOCHS = 400
    history = model.fit(features, labels, validation_data=[X_test, y_test],
                        epochs=NUM_EPOCHS, batch_size=64)

    # Evaluate model
    scores = model.evaluate(X_test, y_test, verbose=0)
    print("Accuracy: %.2f" % (scores[1]*100))

    # Works great!

    # Compute confusion matrix
    y_pred = model.predict(X_test)
    cnf_matrix = confusion_matrix(y_test.argmax(1), y_pred.argmax(1))

    # Print labels
    print("Labels:", df["digit"].unique())

    # Calculate the F1 score
    print("F1 score per label: " + ', '.join(map(
        str, np.around(f1_score(
            y_test.argmax(1),
            y_pred.argmax(1),
            average=None),
            2))))
    print("Global F1 score: %.2f" % f1_score(y_test.argmax(1), y_pred.argmax(1),
        average="micro"))

    #  Save the model locally
    model.save(MODEL_NAME + ".h5")

    # Save the model to the Cloud Storage bucket's jobs directory
    with file_io.FileIO(MODEL_NAME + ".h5", mode='rb') as input_f:
        with file_io.FileIO(job_dir + '/' + MODEL_NAME + '.h5', mode='w+') as output_f:
            output_f.write(input_f.read())

    # Save history
    with open(HISTORY_NAME + ".pkl", 'wb') as f:
        pickle.dump(history.history, f)

    with file_io.FileIO(HISTORY_NAME + '.pkl', mode='rb') as input_f:
        with file_io.FileIO(job_dir + '/' + HISTORY_NAME + '.pkl', mode='w+') as output_f:
            output_f.write(input_f.read())

if __name__ == '__main__':
    # Parse the input arguments for common Cloud ML Engine options
    parser = argparse.ArgumentParser()
    parser.add_argument(
      '--train-file',
      help='Cloud Storage bucket or local path to training data')
    parser.add_argument(
      '--job-dir',
      help='Cloud storage bucket to export the model and store temp files')
    args = parser.parse_args()
    arguments = args.__dict__
    train_model(**arguments)
