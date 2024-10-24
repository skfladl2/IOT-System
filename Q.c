#include <stdio.h>
#include <pthread.h>
#include <wiringPi.h>

#define TRIG 28
#define OUT 29

#define PIN_1A 27
#define PIN_1B 0
#define PIN_2A 1
#define PIN_2B 24
#define DELAY 8000 //7000 //2000

int isStopped = 0;
pthread_t thread_sm;
int distance = 0;

void stepD() {
    digitalWrite(PIN_1A, HIGH);
    digitalWrite(PIN_1B, LOW);
    digitalWrite(PIN_2A, LOW);
    digitalWrite(PIN_2B, LOW);
    delay(1000);
    digitalWrite(PIN_1A, LOW);
    digitalWrite(PIN_1B, HIGH);
    digitalWrite(PIN_2A, LOW);
    digitalWrite(PIN_2B, LOW);
    delay(1000);
    digitalWrite(PIN_1A, LOW);
    digitalWrite(PIN_1B, LOW);
    digitalWrite(PIN_2A, HIGH);
    digitalWrite(PIN_2B, LOW);
    delay(1000);
    digitalWrite(PIN_1A, LOW);
    digitalWrite(PIN_1B, LOW);
    digitalWrite(PIN_2A, LOW);
    digitalWrite(PIN_2B, HIGH);
    delay(1000);
}

static void* do_stepD(void *arg) {
    while (1) {
        if (*(int *)arg > 30) {
            stepD();
        }
    }
}

int getDistance() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(20);
    digitalWrite(TRIG, LOW);

    while (digitalRead(OUT) == 0);

    long startTime = micros();

    while (digitalRead(OUT) == 1);

    long travelTime = micros() - startTime;

    int distance = travelTime / 58;

    return distance;
}

int main(void) {
    if (wiringPiSetup() == -1) return 1;

    pinMode(TRIG, OUTPUT);
    pinMode(OUT, INPUT);

    while (1) {
        distance = getDistance();
        printf("%dcm \n", distance);

        if (distance < 30 && !isStopped) {
            printf("< 30cm, Step Motor Stopped.\n");
            isStopped = 1;
            pthread_cancel(thread_sm); // Stop the thread
        }
        else if (distance >= 30 && isStopped) {
            printf(">= 30cm, Step Motor Resumed.\n");
            isStopped = 0;
            if (pthread_create(&thread_sm, NULL, do_stepD, (void *)&distance) < 0) {
                printf("Error: failed to create thread.\n");
            }
        }

        delay(100);
    }

    return 0;
}
