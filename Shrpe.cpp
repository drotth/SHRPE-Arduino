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

volatile bool dataAvailable = false;

Framing framing;
byte input_buff[100];
int input_length, crc_valid;

Shrpe::Shrpe()
{
	
}

void Shrpe::begin()
{
  delay(6000); // wait for the shield to boot up
  Serial.begin(115200);
  framing.setTimout(0.1);
  pinMode(2, INPUT); //
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  digitalWrite(2, HIGH); // turn on pull-up resistor
  attachInterrupt(0, shrpe_irq_handler, FALLING);
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

byte Shrpe::downloadObject(uint8_t* buffer_ptr, uint8_t size)
{
  int bytes_available = Serial.available();
		
    if (bytes_available)
	{
	  framing.receiveFramedData(input_buff, input_length, crc_valid);
	  buffer_ptr = &input_buff[0];
	  
	  return input_length;
	}
	
  dataAvailable = false;
}

bool Shrpe::available()
{
  return dataAvailable;
}

void shrpe_irq_handler()
{
  digitalWrite(13, !digitalRead(13)); // toggle LED to indicate IRQ trigger
  dataAvailable = true;
}
