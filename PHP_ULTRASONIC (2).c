#include <stdio.h>
#include <wiringPi.h>
#define TRIG 28
#define OUT 29
int main(void){
	int dis;
	long startTime, travelTime;
	if(wiringPiSetup() == -1) return 1;
	pinMode(TRIG,OUTPUT);
	pinMode(OUT,INPUT);
	digitalWrite (TRIG, LOW);
	usleep(2);
	digitalWrite (TRIG, HIGH);
	usleep(20);
	digitalWrite (TRIG, LOW);
	while(digitalRead(OUT) == LOW);
	startTime = micros();
	while(digitalRead(OUT) == HIGH);
	travelTime = micros() - startTime;
	dis = travelTime / 58;
	printf("%d",dis);
}