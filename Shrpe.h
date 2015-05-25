/*
  Shrpe.cpp
  - Library for usage together with the SHRPE shield.
  Authors: Andreas Drotth & Soded Alatia, 
  Created Date: April 9, 2015.
  [license, domain etc?]
*/

#ifndef Shrpe_h
#define Shrpe_h

#include "Arduino.h"

class Shrpe
{
  public:
    Shrpe();
	void begin();
	void uploadObject(uint8_t data_byte);
	void uploadObject(uint8_t array[], uint8_t size);
	uint8_t getData();
  private:
    uint8_t dataRecieved;
};

#endif

