#include <wiringPi.h>
#include <stdio.h>

#define TOUCH_PIN 6
#define LED_PIN 7

void edge_rise(void);

int touchCount = 0;
int ledCount = 0;

int main(void) {
    if (wiringPiSetup() == -1)
        return 1;

    pinMode(TOUCH_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    wiringPiISR(TOUCH_PIN, INT_EDGE_RISING, &edge_rise);

    while (1) {
        delay(10000); // 10초 동안 대기
    }

    return 0;
}

void edge_rise(void) {
    digitalWrite(LED_PIN, HIGH); // LED 켜기
    touchCount++; // 터치 센서가 눌린 횟수 증가
    ledCount++; // LED가 켜진 횟수 증가
    delay(1000); // 1초 동안 LED 켜져 있도록 대기
    digitalWrite(LED_PIN, LOW); // LED 끄기
    printf("Touch sensor pressed %d, LEDs turned on %d\n", touchCount, ledCount); // touch sensor, LED가 켜진 횟수 출력
}
