__author__ = "Stefan"

import keras

def create_tensorboard_config(path):
    return keras.callbacks.TensorBoard(
            log_dir=path,
            histogram_freq=0,
            write_graph=True,
            write_images=False
            )
