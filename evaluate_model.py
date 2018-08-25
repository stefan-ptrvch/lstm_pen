"""
Evaluates lstm-pencil model.
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import pickle
import h5py
from sklearn.model_selection import train_test_split
from keras.models import load_model
from sklearn.preprocessing import OneHotEncoder
from sklearn.metrics import confusion_matrix, f1_score
from utilities import plot_confusion_matrix, save_figure

# Set seed for reproducibility
np.random.seed(7)

# Set interactive mode for pyplot
plt.ion()

# Load data
df = pd.read_csv("./data/dataset_digits_5ms")

# Get sequence with most samples (probably an O)
NUM_STEPS = df["sample"].value_counts().max()
NUM_FEATURES = 6
NUM_CLASSES = df["digit"].unique().size

# Dummy matrix for zero-padding
dummy = np.zeros((NUM_STEPS, NUM_FEATURES + 1))

# Other dummy for stacking
stack_dummy = np.zeros((1, NUM_FEATURES + 1))

# Go through all sequences and pad with zeros
for index in df["sample"].unique():
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

# Load model
model = load_model("./models/model_1300.h5")

# Load history of model
with open("./models/history_1300.pkl", 'rb') as f:
    history = pickle.load(f)

# Get number of epochs
NUM_EPOCHS = len(history["acc"])

# Evaluate model
scores = model.evaluate(X_test, y_test, verbose=0)
print("Accuracy: %.2f" % (scores[1]*100))

# Works great!

# Make plots
loss_acc_fig = plt.figure()
loss_acc_plot = loss_acc_fig.add_subplot(111)
loss_acc_plot.grid()
loss_acc_plot.set_xlabel("epoch")
loss_acc_plot.set_ylabel("accucary/loss")
loss_acc_plot.set_title("LSTM training")

# Plot loss and accuracy
epoch_vector = np.linspace(1, NUM_EPOCHS, NUM_EPOCHS)
for label, data in history.items():

    # Scale accuracy
    if label == "val_acc" or label == "acc":
        data = np.array(data)*100
    loss_acc_plot.semilogy(epoch_vector, data, label=label)
loss_acc_plot.legend(loc="upper left")


# Plot confusion matrix

# Compute confusion matrix
y_pred = model.predict(X_test)
cnf_matrix = confusion_matrix(y_test.argmax(1), y_pred.argmax(1))

# Plot normalized confusion matrix
classes = [0]
classes.extend(df.digit.unique()[:-1])
classes = list(map(str, classes))
plt.figure()
plot_confusion_matrix(cnf_matrix, classes=classes, normalize=True,
                      title='Normalized confusion matrix', cmap=plt.cm.Greys)

plt.show()

# Calculate the F1 score
print("F1 score per label: " + ', '.join(map(
    str, np.around(f1_score(
        y_test.argmax(1),
        y_pred.argmax(1),
        average=None),
        2))))
print("Global F1 score: %.2f" % f1_score(y_test.argmax(1), y_pred.argmax(1),
    average="micro"))
