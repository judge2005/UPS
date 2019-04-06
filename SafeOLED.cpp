/*
 * SafeOLED.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#include <Wire.h>
#include <SafeOLED.h>

bool SafeOLED::begin(uint8_t addr, uint8_t sdaPin, uint8_t sclPin) {
	Wire.beginTransmission((addr >> 1) & 0xff);
	if (Wire.endTransmission() == 0) {
		pOled = new U8X8_SSD1306_128X64_NONAME_HW_I2C(U8X8_PIN_NONE, sclPin, sdaPin);
		pOled->setI2CAddress(addr);
		pOled->begin();

		return true;
	}

	return false;
}
