/*
 * MCP23017.cpp
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#include <SafeLIS3DH.h>
#include <Wire.h>

bool SafeLIS3DH::begin(uint8_t addr) {
	Wire.beginTransmission(addr);
	if (Wire.endTransmission() == 0) {
		pLis = new Adafruit_LIS3DH();
		pLis->begin(addr);	// Yet another Wire.begin...

		return true;
	}

	return false;
}

bool SafeLIS3DH::isClicked() {
	if (pLis) {
		uint8_t click = pLis->getClick();

		if (click != 0) {
			unsigned long nowMs = millis();
			if (nowMs - lastClicked > 1000) {
				lastClicked = nowMs;
				return true;
			}
		}
	}

	return false;
}

void SafeLIS3DH::debug(SafeOLED& oled) {
	if (oled && pLis) {
		oled.setCursor(0, 0);
		oled.print("X:");
		oled.print(pLis->x_g);
		oled.setCursor(0, 1);
		oled.print("Y:");
		oled.print(pLis->y_g);
		oled.setCursor(0, 2);
		oled.print("Z:");
		oled.print(pLis->z_g);
		oled.setCursor(0, 3);
		oled.print("Cl:");
		uint8_t click = pLis->getClick();
		for (int i = sizeof(uint8_t)*8; i > 0; i--) {
			oled.print(((click >> i) & 1) == 1 ? "1" : "0");
		}
	}

}
