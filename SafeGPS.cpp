/*
 * SafeGPS.cpp
 *
 *  Created on: Oct 25, 2020
 *      Author: mpand
 */

#include <SafeGPS.h>

#define MAX_PACKET_SIZE 255

bool SafeGPS::begin(uint8_t addr) {
	found = false;
	_tail = _head = 0;

	Wire.beginTransmission(addr);
	Wire.write(0); //Write dummy value
	Wire.endTransmission();

	if (Wire.requestFrom((int)addr, 1)) {
		i2caddr = addr;
		found = true;
	}

	return found;
}

//Reads a 255 byte packet from GPS module
//If new data is there, appends it to the gpsData array
//Function requires 26ms @ 100kHz I2C, 9ms @ 400kHz I2C so call sparingly
void SafeGPS::check()
{
	if (found) {
	  for (uint8_t x = 0; x < MAX_PACKET_SIZE; x++)
	  {
		if (x % 32 == 0)                      //Arduino can only Wire.read() in 32 byte chunks. Yay.
		  Wire.requestFrom((int)i2caddr, 32); //Request 32 more bytes

		uint8_t incoming = Wire.read();

		if (incoming != 0x0A)
		{
		  //Record this byte
		  gpsData[_head++] = incoming;
		  _head %= MAX_PACKET_SIZE; //Wrap variable
		}
	  }
	}
}

uint8_t SafeGPS::available()
{
  //If tail=head then no new data is available in the local buffer
  //So now check to see if the module has anything new in its buffer
  if (_tail == _head)
  {
    check(); //Check to module to see if new I2C bytes are available
  }

  //Return new data count
  if (_head > _tail)
    return (_head - _tail);
  if (_tail > _head)
    return (MAX_PACKET_SIZE - _tail + _head);

  return (0); //No data available
}

//Returns the next available byte from the gpsData array
//Returns 0 if no byte available
uint8_t SafeGPS::read(void)
{
  if (_tail != _head)
  {
    uint8_t datum = gpsData[_tail++];
    if (_tail == MAX_PACKET_SIZE)
      _tail = 0; //Wrap variable
    return (datum);
  }
  else
    return (0); //No new data
}
