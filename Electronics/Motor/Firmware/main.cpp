#include <main.h>

int ensureConfigured() {
	bool calibConfigured = config->calibrated == 1;
	bool idConfigured = config->controllerId != 0 && config->controllerId != -1;
	
	if (!calibConfigured) calibrate();
	
	setStatus(!idConfigured);
}

//

int main(void) {
	initClockExternal();
	initUsart();
	initSpi();
	initSysTick();
	initTemperature();
	initPwm();
	
	//calibrate();
	delay(2000);
	
	ensureConfigured();
	
	//usartTorqueCommandValue = -250;	
	
	usartDmaSendRequested = false;

	while (true){
		spiCurrentAngleInternal = spiReadAngleInternal();
		spiCurrentAngleExternal = spiReadAngleExternal();
		if (tempShutdown) setPwm(0, 0);
		else setPwmTorque();
		
		if (usartDmaSendRequested && !usartDmaSendBusy)
		{
			usartSendAngle();
			usartDmaSendRequested = false;
		}
		
		if (usartCommandReceived)
		{
			processUsartCommand();
			usartCommandReceived = false;
		}
	}
}
