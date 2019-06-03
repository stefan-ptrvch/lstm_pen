# LSTM Pen
LSTM project that classifies digits from motion processor data.

## Dependencies
* Python 3.x
* Keras
* scikit-learn
* pyserial
* pandas
* matplotlib
* google-cloud-sdk

## Training
The project uses Google Cloud ML Engine to train its models, for which there is
a project structure in ./gml. The environment has to be sourced from the
./gml/env.sh script before a training instance in gml can be run. A training
instance is run using the ./gml/start.sh shell script, and is stopped using the
./gml/stop.sh script.

## Using a Trained Model
In the ./mbed folder there is a project for the MPU9150 motion processor, which
can be imported into mbed, and compiled for any embedded platform supported by
mbed. The device then streams data to the host PC using serial communication.
Real time classifications can be done using the ./predict_serial.py script.


A detailed description of the whole system (in Serbian) can be found in the
./desc folder.
