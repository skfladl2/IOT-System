#include <wiringPi.h>
#include <stdio.h>

#define TOUCH_PIN 6
#define LED_PIN 7

void edge_rise(void);
void edge_fall(void); // Declare edge_fall function prototype

int main(void) {
    if (wiringPiSetup() == -1) return 1;
    pinMode(LED_PIN, OUTPUT);
    
    // Initialize touch pin with an interrupt edge rising
    pinMode(TOUCH_PIN, INPUT);
    wiringPiISR(TOUCH_PIN, INT_EDGE_RISING, &edge_rise); // Setup interrupt
    
    // Main loop delay for demonstration purposes
    delay(10000);
    
    return 0;
}

void edge_rise(void) {
    printf("Pressed\n");
    digitalWrite(LED_PIN, HIGH); // Turn on LED
    delay(1000); // Keep LED on for 1 second
    digitalWrite(LED_PIN, LOW); // Turn off LED
}

void edge_fall(void) {
    // Nothing to do in this function
}
