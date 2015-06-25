/*
  Shrpe.h
  - Library for usage together with the SHRPE shield.
  Authors: Andreas Drotth & Soded Alatia, 
  Created Date: May 28, 2015.
*/

#ifndef Shrpe_h
#define Shrpe_h

#include "Arduino.h"

#define MSG_RES_OK			0x00
#define MSG_UPLOAD_OBJ		0x01
#define MSG_UPLOAD_ACK		0x02
#define MSG_UPLOAD_NACK		0x03
#define MSG_GET_NEXT_DATA	0x04

class Shrpe
{
  private:
	volatile bool dataAvailable;
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
	  @param	array	the data to be sent.
	  @param	size	size of the array.
	*/
	int write(uint8_t array[], uint8_t size);
	/*
	  Receives an array of (unsigned) bytes from the SHRPE Shield.
	  The function is capable of receiving up to 38 bytes.
	  Returns the numbers of bytes in the array.
	  @param	buffer_ptr	pointer to where to store the data.
	  @param	size		size of the array.
	  @return				the length of the array.
	*/
	byte read(uint8_t* buffer_ptr, uint8_t size);
	/*
	  @Return	true if the shield has data available, otherwise false.
	*/
	boolean available();
};

#endif

