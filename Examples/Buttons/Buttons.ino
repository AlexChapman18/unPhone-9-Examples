// Example unPhone code for the 3 physical buttons
// Made by Alex Chapman - 2023

// Import(s)
#include "unPhone.h"			// for unPhone

// Creating unPhone
unPhone unphone = unPhone("Buttons Example");

// Declaring RGB variables
uint8_t redValue;
uint8_t greenValue;
uint8_t blueValue;


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

//	Setting values to 0
	redValue = 0;
	greenValue = 0;
	blueValue = 0;

//	If a button is pressed, set that colour to 255
	if (unphone.button1()) {
		redValue = 255;
	}

	if (unphone.button2()) {
		greenValue = 255;
	}

	if (unphone.button3()) {
		blueValue = 255;
	}

//	Sets the unPhone LED to the associated values
	unphone.rgb(redValue, greenValue, blueValue);
}