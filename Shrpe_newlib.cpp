/*
  Shrpe.cpp - Library for Arduino Shrpe shield.
  Copyright (c) 2011-2014 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Shrpe_newlib.h"
#include "packet_framing_library/CRC_16.cpp"
#include "packet_framing_library/Framing.cpp"
#include "packet_framing_library/Timer.cpp"

Framing framing;
byte input_buff[100], upl_obj_ack_buff[1], dl_obj_buff[38];
int input_length, crc_valid, result;

Shrpe::Shrpe()
{
	// Driver initialization
    _state = SHRPE_STATE_DISCONNECTED;
}

int Shrpe::begin()
{
	// wait for reset event
  // reset shield
	Serial.begin(115200);
  framing.setTimout(0.1);
  pinMode(2, INPUT); // IRQ-PIN
  digitalWrite(2, HIGH); // turn on pull-up resistor
  // wait for first state change event
  return SHRPE_OK;
}

void Shrpe::loop()
{
  //while pending message in shield
	
  while (!digitalRead(2)) {
		uint8_t msg[39];
		uint8_t length;
    if(getNextMessage(msg, length) == SHRPE_OK) {
			switch (msg[0]) {
			case SHRPE_RESET_EVENT:
				_state = SHRPE_STATE_DISCONNECTED;
      case SHRPE_STATE_CHANGED:
        _state = (shrpe_state_t) msg[1];
        break;
      case SHRPE_UPLOAD_OBJECT_ACK:
				upl_obj_ack_buff[0] = msg[1];
        break;
      case SHRPE_DOWNLOAD_OBJECT:
				for(int i = 0; i < length; i++) {
					dl_obj_buff[i] = msg[i+1];
				}
        break;
      default:
        break;
			}
		}
  }
}

shrpe_result_t Shrpe::getNextMessage(uint8_t* msg, size_t length)
{
	uint8_t data_array[1] = {SHRPE_GET_NEXT_MSG};
  if (framing.sendFramedData(data_array, 1)) {
  
    framing.receiveFramedData(input_buff, input_length, crc_valid);
    if(crc_valid == 1) {
	  for (int i = 0; i < input_length; i++){
	    msg[i] = input_buff[i];
	  }
			length = input_length;
			return SHRPE_OK;  
    }
		return SHRPE_ERR_CRC;
  }
  return SHRPE_ERR_TIMEOUT;
}

shrpe_result_t Shrpe::sendUploadObject(const uint8_t *buffer, size_t size)
{
  // send UploadObject command
  int result = size;
	uint8_t msg[size+1];
	msg[0] = SHRPE_UPLOAD_OBJECT;
	for(int i = 0; i < size; i++) {
		msg[i+1] = buffer[i];
	}
	if(framing.sendFramedData(msg, size+1)) {
		framing.receiveFramedData(input_buff, input_length, crc_valid);
		if (crc_valid == 1)  {
			return (shrpe_result_t) input_buff[0];
		}
		return SHRPE_ERR_CRC;
	}
  return SHRPE_ERR_TIMEOUT;
}

int Shrpe::receiveUploadObjectAck()
{
  // check if UploadObjectAck is received
  // for now assume that an ack is received
  //buffer[0] = 1; // 1 => ack is received, 0 => tx failed, no ack received
  //buffer[1] = 0; // ack payload if ack received OR error code if tx failed
  //result = upl_obj_ack_buff[0];
  return upl_obj_ack_buff[0];
}

int Shrpe::receiveDownloadObject(uint8_t *buffer, size_t length)
{
  return 0;
}

int Shrpe::available()
{
  return 0;
}

int Shrpe::read()
{
  return -1;
}

int Shrpe::peek()
{
  return -1;
}

void Shrpe::flush()
{
}

size_t Shrpe::write(uint8_t byte)
{
  return 0;
}

size_t Shrpe::write(const uint8_t *buffer, size_t size)
{
  return 0;
}

int Shrpe::flushWriteBuffer()
{
  return SHRPE_OK;
}
