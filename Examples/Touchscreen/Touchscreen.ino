// Example unPhone code for the Screen
// Made by Alex Chapman - 2023


#include "unPhone.h"			// for unPhone
#include <TFT_eSPI.h>       	// Screen
#include "XPT2046_Touchscreen.h"		// Touchscreen


// Change to your screen resolution
static const uint16_t SCREEN_WIDTH  = 320;
static const uint16_t SCREEN_HEIGHT = 480;

static const uint16_t TS_MINX = 0;
static const uint16_t TS_MAXX = 4000;
static const uint16_t TS_MINY = 0;
static const uint16_t TS_MAXY = 4000;

unPhone unphone = unPhone("Screen Example");
TFT_eSPI tft = TFT_eSPI(SCREEN_WIDTH, SCREEN_HEIGHT); // the LCD screen
XPT2046_Touchscreen ts(TOUCH_CS); // the Touchscreen with TOUCH_CS pin (38)

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

	// Setup screen and Touchscreen
	setupScreen();
	setupTouchscreen();
}


// Inverts the screen every 3 seconds
void loop() {
	if(ts.touched()){
		TS_Point point = ts.getPoint();
		char x_string[50];
		sprintf(x_string, "X: %d", adjustTSX(point.x), ", ", point.x);
		char y_string[50];
		sprintf(y_string, "Y: %d", adjustTSY(point.y), ", ", point.y);

		tft.fillScreen(TFT_YELLOW);
		drawString(x_string, 5, 5, TFT_BLACK, 3);
		drawString(y_string, 5, 55, TFT_BLACK, 3);

		while (ts.touched()){

		}
	}
}


// Function to draw a string onto the screen, whilst also allowing you to set text color and font size
void drawString(char *string, int32_t x, int32_t y, uint16_t color, uint8_t size){
	tft.setTextColor(color);
	tft.setTextSize(size);
	tft.drawString(string, x, y);
}


void setupScreen(){
	// Rotates the screen, makes it yellow, and draws X and Y
	tft.setRotation(0);
	tft.fillScreen(TFT_YELLOW);
	drawString("X: ", 5, 5, TFT_BLACK, 3);
	drawString("Y: ", 5, 55, TFT_BLACK, 3);
}

void setupTouchscreen(){
	//	Starts and rotates Touchscreen
	ts.begin();
	ts.setRotation(2);
}

uint16_t adjustTSX(uint16_t x){
	return map(x, TS_MAXX, TS_MINX, SCREEN_WIDTH, 0);
}

uint16_t adjustTSY(uint16_t y){
	return map(y, TS_MAXY, TS_MINY, 0, SCREEN_HEIGHT);
}