/*
 * MCP23017.h
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_UPS_SAFEMCP23017_H_
#define LIBRARIES_UPS_SAFEMCP23017_H_

#include <Arduino.h>
#include <Adafruit_MCP23017.h>

class SafeMCP23017 {
public:
	bool begin(uint8_t addr);

	void pinMode(uint8_t p, uint8_t d) { if (pMcp) { pMcp->pinMode(p, d); } }
	void digitalWrite(uint8_t p, uint8_t d) { if (pMcp) { pMcp->digitalWrite(p, d); } }
	void pullUp(uint8_t p, uint8_t d) { if (pMcp) { pMcp->pullUp(p, d); } }
	uint8_t digitalRead(uint8_t p, uint8_t def) {
		if (pMcp) { return pMcp->digitalRead(p); } else { return def; }
	};
	operator bool() const { return pMcp != NULL; }

private:
	Adafruit_MCP23017 *pMcp;
};

#endif /* LIBRARIES_UPS_SAFEMCP23017_H_ */
