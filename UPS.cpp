/*
 * UPS.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#include <UPS.h>

const byte HI_CHGpin = 0;	// Write: LO = 100mA (default), HI = 500mA
const byte V5_ENABLEpin = 1;	// Write: LO = disabled, HI = enabled (default)
const byte VBUS_DETECTpin = 2; // Read: LO = USB disconnected (running on battery), HI = USB connected

bool UPS::begin() {
	mcp.pinMode(VBUS_DETECTpin, INPUT);
	mcp.pullUp(VBUS_DETECTpin, LOW);
	vbus = mcp.digitalRead(VBUS_DETECTpin, 1);
//	mcp.pinMode(V5_ENABLEpin, OUTPUT);
//	mcp.digitalWrite(V5_ENABLEpin, LOW);	// Default to 5V enabled
	mcp.pinMode(HI_CHGpin, OUTPUT);
	mcp.digitalWrite(HI_CHGpin, LOW);		// Default to 100mA charge rate
	rate = "100mA";
}

bool UPS::vBusChanged() {
	oldVbus = vbus;
	vbus = mcp.digitalRead(VBUS_DETECTpin, 1);

	return oldVbus != vbus;
}

bool UPS::rateChanged(byte pref, USBRating &rating) {
	bool changed = false;

	if (pref == 1) {
		if (mcp.digitalRead(HI_CHGpin, LOW) != LOW) {
			mcp.digitalWrite(HI_CHGpin, LOW);		// Set 100mA charge rate
			rate = "100mA";
			changed = true;
		}
	} else if (rating.isHigh() || pref == 2) {
		if (mcp.digitalRead(HI_CHGpin, HIGH) != HIGH) {
			mcp.digitalWrite(HI_CHGpin, HIGH);	// Set 500mA charge rate
			rate = "500mA";
			changed = true;
		}
	} else {
		if (mcp.digitalRead(HI_CHGpin, LOW) != LOW) {
			mcp.digitalWrite(HI_CHGpin, LOW);		// Set 100mA charge raterate
			rate = "100mA";
			changed = true;
		}
	}

	return changed;
}

String UPS::getRateString() {
	return rate;
}




