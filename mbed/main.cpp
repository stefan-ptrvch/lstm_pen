#include "mbed.h"
#include "MPU9150.h"

// Small program that sends sequence of accelerometer/gyroscope data when button
// is pressed

// PC communication
Serial pc(SERIAL_TX, SERIAL_RX, 115200);

// ISR object for button
InterruptIn button1(USER_BUTTON);

// Variariable for debouncing the button
volatile bool button1_enabled = true;

// Timer for debouncing the button
Timeout button1_timeout;

// Variable for state machine
int state = 0;

// Enables button when bouncing is over
void button1_enabled_cb(void)
{
    // Bounce is over, enable button
    button1_enabled = true;
}

// ISR handling button pressed event
// Moves state machine into "send sequence" state
void button1_onpressed_cb(void)
{
    if (button1_enabled) {

        // Disable button while it is bouncing
        button1_enabled = false;

        // Move into "send sequence" state
        if(state == 0)
        {
            state = 1;
        }
        else if(state == 1)
        {
            state = 2;
        }

        // Debounce time 300 ms
        button1_timeout.attach(callback(button1_enabled_cb), 0.3);
    }
}

// ISR handling button released event
// Moves state machine to "indicate end of sequence" state
void button1_rising_edge_cb(void)
{
    if (button1_enabled) {

    // Disable button while it is bouncing
    button1_enabled = false;

    // Move into "indicate end of sequence" state
    state = 2;

    // Debounce time 300 ms
    button1_timeout.attach(callback(button1_enabled_cb), 0.3);
    }
}

int main()
{
    // Set the chip up
    Setup_MPU_9150();

    // Activate pull-up on button
    button1.mode(PullUp);

    // Set interrupt handlers for button press and button release
    button1.fall(callback(button1_onpressed_cb));
    //button1.rise(callback(button1_rising_edge_cb));

    // Main loop
    while(1)
    {
        switch(state)
        {
            // Idle state
            case 0:
            {
                break;
            }

            // Send sequence state
            case 1:
            {

                // Sampling period is 5ms
                wait(0.005);

                // Get samples from chip
                Get_mpu_9150();

                // Send samples, formatted as csv
                pc.printf("%d,", (((uint16_t) g_acc_raw_data[0]) << 8) | g_acc_raw_data[1]);
                pc.printf("%d,", (((uint16_t) g_acc_raw_data[2]) << 8) | g_acc_raw_data[3]);
                pc.printf("%d,", (((uint16_t) g_acc_raw_data[4]) << 8) | g_acc_raw_data[5]);
                pc.printf("%d,", (((uint16_t) g_gyro_raw_data[0]) << 8) | g_gyro_raw_data[1]);
                pc.printf("%d,", (((uint16_t) g_gyro_raw_data[2]) << 8) | g_gyro_raw_data[3]);
                pc.printf("%d", (((uint16_t) g_gyro_raw_data[4]) << 8) | g_gyro_raw_data[5]);
                pc.printf("\n");
                break;
            }

            // End of sequence state
            case 2:
            {
                // Send "end of sequence" command
                pc.printf("eos\n");

                // Go back to idle state
                state = 0;
                break;
            }
        }
    }
}
