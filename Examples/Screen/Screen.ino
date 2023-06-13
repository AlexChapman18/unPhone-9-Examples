// Example unPhone code for the Screen
// Made by Alex Chapman - 2023


#include "unPhone.h"			// for unPhone
#include <TFT_eSPI.h>       	// Screen


// Change to your screen resolution
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 480;


unPhone unphone = unPhone("Screen Example");
TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); // the LCD screen


void setup() {
	// say hi, init, blink etc.
	Serial.begin(115200);
	Serial.printf("Starting build from: %s\n", unphone.buildTime);
	unphone.begin();
	unphone.store(unphone.buildTime);

	// power management
	unphone.printWakeupReason();        // what woke us up?
	unphone.checkPowerSwitch();         // if power switch is off, shutdown
	Serial.printf("battery voltage = %3.3f\n", unphone.batteryVoltage());
	Serial.printf("enabling expander power\n");

	// Print stored messages
	unphone.printStore();               // print out stored messages
	unphone.provisioned();              // redisplay the UI for example
	Serial.println("done with setup()");

}

// Inverts the screen every 3 seconds
void loop() {
	tft.invertDisplay(false); delay(3000);
	tft.invertDisplay(true); delay(3000);
}

// Function to draw a string onto the screen, whilst also allowing you to set text color and font size
void drawString(char *string, int32_t x, int32_t y, uint16_t color, uint8_t size){
	tft.setTextColor(color);
	tft.setTextSize(size);
	tft.drawString(string, x, y);
}

void setupScreen(){
	// Rotates the screen, and makes it black
	tft.setRotation(0);
	tft.fillScreen(TFT_BLACK);

	// Uses the drawString function to write text to the screen
	drawString("Hello", 5, 5, TFT_BLUE, 4);

	// Draw a line across the screen
	tft.drawLine(320, 0, 0, 480, TFT_RED);

	// Draws a square on the screen
	tft.fillRect(5, 50, 50, 50, TFT_GREEN);

	// Draws a rounded rectangle
	tft.drawRoundRect(200, 360, 100, 100, 10, TFT_YELLOW);

	// Draws a full circle
	tft.fillCircle(55, 175, 50, TFT_WHITE);
};

// There are many more functions inside TFT_eSPI.h file