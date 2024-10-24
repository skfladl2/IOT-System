#include <wiringPi.h>
#include <stdio.h>

#define TOUCH_PIN 6
#define LED_PIN 7

int main(void) {
    int prev_state = LOW; // Initialize previous state as LOW
    int current_state;
    int j; // Declare variable for loop counter

    if (wiringPiSetup() == -1) return 1;
    pinMode(TOUCH_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    while (1) {
        current_state = digitalRead(TOUCH_PIN);

        // Check if touch sensor is pressed and the previous state was not pressed
        if (current_state == HIGH && prev_state == LOW) {
            for (j = 0; j < 3; j++) { // Loop 3 times
                printf("Pressed\n");
                digitalWrite(LED_PIN, HIGH); // Turn on LED for 0.5 seconds
                delay(500);
                digitalWrite(LED_PIN, LOW); // Turn off LED for 0.5 seconds
                delay(500);
            }
        }

        prev_state = current_state; // Update previous state for next iteration
        delay(100); // Polling interval of 0.1 seconds
    }

    return 0;
}
