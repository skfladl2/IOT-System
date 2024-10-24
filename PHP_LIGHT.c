#include <stdio.h>
#include <wiringPi.h>

//reading for ADC value
#define SPI_CH 0 
#define ADC_CH 0
#define ADC_CS 29
#define SPI_SPEED 500000

int main(void) {
	int value = 0, i;
	unsigned char buf[3];

	if (wiringPiSetup() == -1) return 1; //ready for GPIO communication
	
	if (wiringPiSPISetup() == -1) return -1; // ready for SPI communication
	
	pinMode(ADC_CS, OUTPUT); // CS pin is to control the start and end of the communication
	
	buf[0] = 0x06 | ((ADC_CH & 0x04) >> 2);
	buf[1] = ((ADC_CH & 0x03) << 6);
	buf[2] = 0x00;
	
	digitalWrite(ADC_CS, 0); //con is LOW -start

	wiringPiSPIDataRW(SPI_CH, buf, 3); //read SPI data and save in buf 
	
	buf[1] = 0x0F & buf[1];
	value = (buf[1] << 8) | buf[2];
	
	digitalWrite(ADC_CS, 1); //con is HIGH -end
	printf("%d", value);
}
