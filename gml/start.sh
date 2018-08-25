source ./env.sh

gcloud ml-engine jobs submit training $JOB_NAME \
    --job-dir $JOB_DIR \
    --module-name training.lstm_pencil_digits \
    --package-path ./training \
    --region $REGION \
    --config=./training/cloudml-gpu.yaml
    -- \
    --train-file gs://$BUCKET_NAME/dataset_digits_5ms
