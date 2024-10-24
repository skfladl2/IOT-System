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
        delay(10000); // 10�� ���� ���
    }

    return 0;
}

void edge_rise(void) {
    digitalWrite(LED_PIN, HIGH); // LED �ѱ�
    touchCount++; // ��ġ ������ ���� Ƚ�� ����
    ledCount++; // LED�� ���� Ƚ�� ����
    delay(1000); // 1�� ���� LED ���� �ֵ��� ���
    digitalWrite(LED_PIN, LOW); // LED ����
    printf("Touch sensor pressed %d, LEDs turned on %d\n", touchCount, ledCount); // touch sensor, LED�� ���� Ƚ�� ���
}
