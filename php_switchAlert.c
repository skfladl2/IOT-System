#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define PIN 3
void edge_fall(void);

int main(void){
        
    if(wiringPiSetup() == -1) return 1;
    pinMode(PIN,INPUT);
	wiringPiISR(PIN, INT_EDGE_FALLING, edge_fall);
          while(1) {
    	       sleep(1);
	}

}


void edge_fall(void){	
      printf("1");
      exit(0);
}


