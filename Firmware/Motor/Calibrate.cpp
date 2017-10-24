#include <main.h>

uint32_t gCalib1;
uint32_t gPhisicalToElec100;

volatile int32_t gResult;

uint16_t getElectricDegrees() {
	uint16_t adc = ADC1->DR;
	gResult = ((adc - gCalib1) * 360 / gPhisicalToElec100) % 360;
	if (gResult < 0) gResult += 360;
	return gResult;
}

void calibrate() {
	const int turns = 3;
	int a = 0;
	
	// 1 back
	
	for (a = 360; a >= 0; a--)
	{
		delay(1);
		setPwm(a, 30);
	}
		
	setPwm(0, 30);
	delay(500);
	int adcStart1 = ADC1->DR;
	
	// 3 forward
	
	a = 0;
	for (a = 0; a <= 360 * turns; a += 2)
	{
		delay(1);
		setPwm(a, 30);
	}
	
	delay(500);	
	int adcEnd1 = ADC1->DR;
	int ratio1 = (adcStart1 - adcEnd1) / turns;
	
	// 3 backwards

	for (; a >= 0; a -= 2)
	{
		delay(1);
		setPwm(a, 30);
	}
	
	delay(500);	
	int adcStart2 = ADC1->DR;
	int ratio2 = (adcStart2 - adcEnd1) / turns;
	
	setPwm(a, 0);	
	
	//
	
	gCalib1 = (adcStart1 + adcStart2) / 2;
	gPhisicalToElec100 = (ratio1 + ratio2) / 2;
}
