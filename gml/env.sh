#!/bin/bash

export BUCKET_NAME="lstm-pencil-data"
export JOB_NAME="lstm_pencil$(date +%Y%m%d_%H%M%S)"
export JOB_DIR="gs://$BUCKET_NAME/$JOB_NAME"
export REGION=europe-west1
