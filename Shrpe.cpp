/*
  Shrpe.cpp
  - Library for usage together with the SHRPE shield.
  Authors: Andreas Drotth & Soded Alatia, 
  Created: May 28, 2015.
  Last Modified: July 1, 2015.
  Release version: v2.0
*/

#include "Shrpe.h"
#include "Arduino.h"
#include "packet_framing_library/CRC_16.cpp"
#include "packet_framing_library/Framing.cpp"
#include "packet_framing_library/Timer.cpp"

void shrpe_irq_handler();

volatile uint8_t dataAvailable2 = 0;


Framing framing;
byte input_buff[100];
int input_length, crc_valid, msg_handled = 0;
int timeout_counter = 15000;

Shrpe::Shrpe()
{
	//empty constructor.
}

void Shrpe::begin()
{
  //delay(2000); // wait for the shield to boot up
  Serial.begin(115200);
  framing.setTimout(0.1);
  pinMode(2, INPUT); // IRQ-PIN
  digitalWrite(2, HIGH); // turn on pull-up resistor
}

int Shrpe::write(uint8_t data_byte, uint8_t msg_type)
{
  uint8_t data_array[1] = {data_byte};
  return write(data_array, 1, msg_type);
}

int Shrpe::write(uint8_t array[], uint8_t size, uint8_t msg_type)
{
  uint8_t msg_array[size+1];
  msg_array[0] = msg_type;
  for (int i = 0; i < size; i++){
		msg_array[i+1] = array[i];
  }
  framing.sendFramedData(msg_array, size+1);
  
  framing.receiveFramedData(input_buff, input_length, crc_valid);
  if (crc_valid == 1)  {
	  
    return input_buff[0];
  }
  return -1;
}

int Shrpe::read(uint8_t* buffer_ptr, uint8_t size)
{
  uint8_t data_array[1] = {MSG_GET_NEXT_DATA};
  if (framing.sendFramedData(data_array, 1)) {
  
    framing.receiveFramedData(input_buff, input_length, crc_valid);
    if(crc_valid == 1) {
	  for (int i = 0; i < input_length; i++){
	    buffer_ptr[i] = input_buff[i];
	  }
	  return input_length;  
    }
	return 0;
  }
  return -1;
}

bool Shrpe::available()
{
  if (!digitalRead(2)){
	return true;
  }
  else return false;
}
