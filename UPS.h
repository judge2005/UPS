/*
 * UPS.h
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_UPS_UPS_H_
#define LIBRARIES_UPS_UPS_H_

#include <arduino.h>
#include <SafeMCP23017.h>
#include <USBRating.h>

class UPS {
public:
	UPS(SafeMCP23017& mcp) : mcp(mcp), rate("100mA") {
	}

	bool begin();

	bool rateChanged(byte pref, USBRating &rating);
	bool vBusChanged();
	String getRateString();
	String getPowerString() { return vbus == 1 ? "USB" : "Battery"; }
	uint8_t getVBus() {return vbus;}
	operator bool() const {return (bool)mcp;}

private:
	SafeMCP23017& mcp;
	String rate;
	uint8_t oldVbus = 1;
	uint8_t vbus = 1;
};


#endif /* LIBRARIES_UPS_UPS_H_ */
