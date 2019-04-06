/*
 * MCP23017.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#include <SafeMCP23017.h>
#include <Wire.h>

bool SafeMCP23017::begin(uint8_t addr) {
	Wire.beginTransmission(addr);
	if (Wire.endTransmission() == 0) {
		// Initialize expansion ports, default address: 0x20
		pMcp = new Adafruit_MCP23017();
		pMcp->begin(addr - 0x20);	// Yet another Wire.begin...

		return true;
	}

	return false;
}
