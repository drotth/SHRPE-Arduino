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
int timeout_counter = 5000;

Shrpe::Shrpe()
{
	
}

void Shrpe::begin()
{
  delay(6000); // wait for the shield to boot up
  Serial.begin(115200);
  framing.setTimout(0.1);
  pinMode(2, INPUT); // IRQ-PIN
  pinMode(13, OUTPUT); // LED-PIN
  pinMode(12, OUTPUT); // "DATA AVAILABLE"-PIN
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
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
  uint8_t msg_array[size+1];
  msg_array[0] = MSG_UPLOAD_OBJ;
  for (int i = 0; i < size; i++){
		msg_array[i+1] = array[i];
  }
  framing.sendFramedData(msg_array, size+1);
  delay(7);
}

byte Shrpe::downloadObject(uint8_t* buffer_ptr, uint8_t size)
{
  uint8_t data_array[1] = {MSG_GET_NEXT_DATA};
  framing.sendFramedData(data_array, 1);
  
  while(!Serial.available() && timeout_counter > 0) {
	  timeout_counter--;
  };
  
  framing.receiveFramedData(input_buff, input_length, crc_valid);
  
  for (int i = 0; i < input_length; i++){
	buffer_ptr[i] = input_buff[i];
  }
	  
  return input_length;
}

bool Shrpe::available()
{
  if (digitalRead(12) == HIGH){
	digitalWrite(12, LOW);
	return true;
  }
  else return false;
}

void shrpe_irq_handler()
{
  digitalWrite(12, HIGH);
}
