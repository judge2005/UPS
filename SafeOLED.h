/*
 * SafeOLED.h
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_UPS_SAFEOLED_H_
#define LIBRARIES_UPS_SAFEOLED_H_
#include <U8x8lib.h>

class SafeOLED {
public:
	bool begin(uint8_t addr, uint8_t sclPin, uint8_t sdaPin);

	void setFont(const uint8_t *font_8x8) {  if (pOled) {pOled->setFont(font_8x8);} }
	void setCursor(uint8_t x, uint8_t y) { if (pOled) {pOled->setCursor(x, y);} }
	void clearDisplay() { if (pOled) {pOled->clearDisplay();} }

	void print(const char *arg) { if (pOled) {pOled->print(arg);} }
	void print(const bool arg) { if (pOled) {pOled->print(arg);} }
	void print(const int arg) { if (pOled) {pOled->print(arg);} }
	void print(const float arg) { if (pOled) {pOled->print(arg);} }
	operator bool() const { return pOled != NULL; }

private:
	U8X8_SSD1306_128X64_NONAME_HW_I2C *pOled = NULL;
};



#endif /* LIBRARIES_UPS_SAFEOLED_H_ */
