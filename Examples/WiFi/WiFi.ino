// Example unPhone code for the 3 physical buttons
// Made by Alex Chapman - 2023

// Import(s)

#include <WiFiMulti.h>          // manage WiFi connections

#if __has_include("private.h")  // for WiFi SSIDs/PSKs and LoRa config; see:
// https://gitlab.com/hamishcunningham/the-internet-of-things/-/blob/master/support/private-template.h
#  include "private.h"
#endif
#include "unPhone.h"			// for unPhone

// Creating unPhone
unPhone unphone = unPhone("WiFi Example");


bool useWifi = true;            // toggle wifi connection
WiFiMulti wifiMulti;            // manage...
void wifiSetup();               // ...the wifi...
void wifiConnectTask(void *);   // ...connection


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

  // get a connection and run the wifi connection task
  if(useWifi) {
    Serial.println("trying to connect to wifi...");
    wifiSetup();
    xTaskCreate(wifiConnectTask, "wifi connect task", 4096, NULL, 1, NULL);
  }

	// Print stored messages
	unphone.printStore();               // print out stored messages
	unphone.provisioned();              // redisplay the UI for example
	Serial.println("done with setup()");
}


void loop() {
}


void wifiSetup() { ///////////////////////////////////////////////////////////
#ifdef _MULTI_SSID
  Serial.printf("wifiMulti.addAP %s\n", _MULTI_SSID);
  wifiMulti.addAP(_MULTI_SSID, _MULTI_KEY);
#endif
}


static bool wifiConnected = false; ///////////////////////////////////////////
void wifiConnectTask(void *param) {
  while(true) {
    bool previousWifiState = wifiConnected;
    if(wifiMulti.run() == WL_CONNECTED)
      wifiConnected = true;
    else
      wifiConnected = false;

    // call back to UI controller if state has changed
    if(previousWifiState != wifiConnected) {
      previousWifiState = wifiConnected;
      unphone.provisioned();
    }

    delay(1000);
  }
}



