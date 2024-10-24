#include <wiringPi.h>
#include <stdio.h>

#define PIN 6

int main(void){
        int touch, i;

        if(wiringPiSetup() == -1) return 1;
        pinMode(PIN,INPUT);

        for(i=0; i<20; i++){
        	touch = digitalRead(PIN);
		printf("%d\n",touch);
		delay(100);
	}
}
