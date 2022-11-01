/*
 * SafeGPS.h
 *
 *  Created on: Oct 25, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_UPS_SAFEGPS_H_
#define LIBRARIES_UPS_SAFEGPS_H_

#include <Arduino.h>
#include <Wire.h>

class SafeGPS {
public:
	bool begin(uint8_t addr);

    uint8_t available(); //Returns available number of bytes. Will call check() if zero is available.
    uint8_t read(); //Returns the next available byte

	operator bool() const { return found; }

private:
    void check(); //Checks module for new data

    bool found = false;
    uint8_t i2caddr;

    uint8_t _head; //Location of next available spot in the gpsData array. Limited to 255.
    uint8_t _tail; //Location of last spot read from gpsData array. Limited to 255.
    uint8_t gpsData[255]; //The place to store valid incoming gps data

};

#endif /* LIBRARIES_UPS_SAFEGPS_H_ */
