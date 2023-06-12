// Example unPhone code for the RGB_led
// Made by Alex Chapman - 2023

// Import(s)
#include "unPhone.h"			// for unPhone

// Creating unPhone
unPhone unphone = unPhone("RGB_led Example");


void setup() {
	// Setup serial and unPhone
	Serial.begin(115200);
	Serial.printf("Starting build from: %s\n", unphone.buildTime);
	unphone.begin();
	unphone.store(unphone.buildTime);

	// power management
	unphone.printWakeupReason();        // what woke us up?
	unphone.checkPowerSwitch();         // if power switch is off, shutdown
	Serial.printf("battery voltage = %3.3f\n", unphone.batteryVoltage());

	// Print stored messages
	unphone.printStore();               // print out stored messages
	unphone.provisioned();              // redisplay the UI for example
	Serial.println("done with setup()");
}


void loop() {
//	Iterates through all of the standard colours
	unphone.rgb(0, 0, 0);
	delay(1000);
	unphone.rgb(0, 0, 255);
	delay(1000);
	unphone.rgb(0, 255, 0);
	delay(1000);
	unphone.rgb(0, 255, 255);
	delay(1000);
	unphone.rgb(255, 0, 0);
	delay(1000);
	unphone.rgb(255, 0, 255);
	delay(1000);
	unphone.rgb(255, 255, 0);
	delay(1000);
	unphone.rgb(255, 255, 255);
	delay(1000);
}