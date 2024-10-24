#include <wiringPi.h>
#include <stdio.h>

#define TOUCH_PIN 6
#define LED_PIN 7

void edge_rise(void);

int ledCount = 1;
int touchCount = 0;

int main(void) {
    int prev_state = LOW;
    int current_state;

    if (wiringPiSetup() == -1) return 1;

    pinMode(TOUCH_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    wiringPiISR(TOUCH_PIN, INT_EDGE_RISING, &edge_rise);

    while (1) {
        current_state = digitalRead(TOUCH_PIN);


        if (current_state == HIGH && prev_state == LOW) {
            digitalWrite(LED_PIN, HIGH);
            delay(1000); //
            digitalWrite(LED_PIN, LOW);
            ledCount++;
        }

        prev_state = current_state; // 다음 반복을 위해 이전 상태 업데이트
        delay(100); // 0.1초 간격으로 폴링
    }

    return 0;
}

void edge_rise(void) {
    touchCount++;
    printf("Touch sensor pressed %d times, Led turned on %d times.\n", touchCount, ledCount);
}