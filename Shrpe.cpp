/*
  Shrpe.cpp
  - Library for usage together with the SHRPE shield.
  Authors: Andreas Drotth & Soded Alatia, 
  Created Date: April 9, 2015.
  [license, domain etc?]
*/

#include "Shrpe.h"
#include "Arduino.h"
#include "packet_framing_library\CRC_16.cpp"
#include "packet_framing_library\Framing.cpp"
#include "packet_framing_library\Timer.cpp"

static void shrpe_irq_handler();

volatile uint8_t dataRecieved = 0;
Framing framing;

Shrpe::Shrpe()
{
	
}

void Shrpe::begin()
{
  Serial.begin(115200);
  framing.setTimout(0.1);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  digitalWrite(2, HIGH);
  attachInterrupt(0, shrpe_irq_handler, FALLING);
  delay(6000); // wait for the shield to boot up
}

void Shrpe::uploadObject(uint8_t data_byte)
{
  uint8_t data_array[1] = {data_byte};
  uploadObject(data_array, 1);
}

void Shrpe::uploadObject(uint8_t array[], uint8_t size)
{
  Serial.write(19); //dummy to notice shield we're about to send
  delay(10);
  framing.sendFramedData(array, size);
}

uint8_t Shrpe::getData()
{
   return dataRecieved;
}

static void shrpe_irq_handler(){
  digitalWrite(13, !digitalRead(13));
  dataRecieved = Serial.read();
}

