/*
  Shrpe.cpp
  - Library for usage together with the SHRPE shield.
  Authors: Andreas Drotth & Soded Alatia, 
  Created: May 28, 2015.
*/

#include "Shrpe.h"
#include "Arduino.h"
#include "packet_framing_library\CRC_16.cpp"
#include "packet_framing_library\Framing.cpp"
#include "packet_framing_library\Timer.cpp"

void shrpe_irq_handler();

Framing framing;

Shrpe::Shrpe()
{
	
}

void Shrpe::begin()
{
  delay(6000); // wait for the shield to boot up
  Serial.begin(115200);
  framing.setTimout(0.1);
}

void Shrpe::write(uint8_t data_byte)
{
  uint8_t data_array[1] = {data_byte};
  write(data_array, 1);
}

void Shrpe::write(uint8_t array[], uint8_t size)
{
  framing.sendFramedData(array, size);
}
