/*
  Shrpe.cpp
  - Library for usage together with the SHRPE shield.
  Authors: Andreas Drotth & Soded Alatia, 
  Created Date: May 28, 2015.
*/

#ifndef Shrpe_h
#define Shrpe_h

#include "Arduino.h"

class Shrpe
{
  public:
	/*
		Constructor för a Shrpe object.
	*/
    Shrpe();
	/*
		Initializes the Shrpe object and makes it ready for transmission of data.
	*/
	void begin();
	/*
		Writes a single (unsigned) byte to the SHRPE Shield.
	*/
	void write(uint8_t data_byte);
	/*
		Writes an array of (unsigned) bytes to the SHRPE Shield.
		The function is capable of sending between 1-40 bytes.
	*/
	void write(uint8_t array[], uint8_t size);
};

#endif

