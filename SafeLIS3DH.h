/*
 * SafeLIS3DH.h
 *
 *  Created on: Apr 15, 2018
 *      Author: mpand
 */

#ifndef LIBRARIES_UPS_SAFELIS3DH_H_
#define LIBRARIES_UPS_SAFELIS3DH_H_

#include <Adafruit_LIS3DH.h>
#include <SafeOLED.h>

class SafeLIS3DH {
public:
	bool begin(uint8_t addr);

	void setRange(lis3dh_range_t range) { if (pLis) { pLis->setRange(range); }}
	void setClick(uint8_t c, uint8_t clickthresh,
			uint8_t timelimit, uint8_t timelatency, uint8_t timewindow) {
		if (pLis) { pLis->setClick(c, clickthresh, timelimit, timelatency, timewindow); }
	}
	uint8_t getClick(uint8_t def) { if (pLis) { return pLis->getClick();} else { return def;} }
	bool isClicked();
	void read() { if (pLis) { pLis->read(); }}
	float getXG(float def) { if (pLis) { return pLis->x_g; } else {return def;}}
	float getYG(float def) { if (pLis) { return pLis->y_g; } else {return def;}}
	float getZG(float def) { if (pLis) { return pLis->z_g; } else {return def;}}
	operator bool() const { return pLis != NULL; }

	void debug(SafeOLED& oled);

private:
	Adafruit_LIS3DH *pLis;
	unsigned long lastClicked = 0;
};

#endif /* LIBRARIES_UPS_SAFELIS3DH_H_ */
