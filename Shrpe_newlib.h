/*
  WiFi.h - Library for Arduino Wifi shield.
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

#ifndef Shrpe_newlib_h
#define Shrpe_newlib_h

#include "Arduino.h"
#include "Stream.h"



extern "C" {
  typedef enum {
    SHRPE_STATE_DISCONNECTED = -1,
    SHRPE_STATE_CONNECTING = 16,
    SHRPE_STATE_CONNECTED = 32
  } shrpe_state_t;
  typedef enum {
    SHRPE_OK = 0,
    SHRPE_ERR_UNDEFINED = -1,
    SHRPE_ERR_TIMEOUT = -2,
    SHRPE_ERR_STATE = -3,
    SHRPE_ERR_CRC = -4,
    SHRPE_ERR_LEN = -5,
    SHRPE_ERR_SEND = -6
    // Etc
  } shrpe_result_t;
	typedef enum {
		SHRPE_UPLOAD_OBJECT = 2,
		SHRPE_GET_NEXT_MSG = 3,
		SHRPE_GET_STATE = 5
	} shrpe_msg_t;
	typedef enum {
		SHRPE_RESET_EVENT = -1,
		SHRPE_UPLOAD_OBJECT_ACK = 0,
		SHRPE_DOWNLOAD_OBJECT = 4,
		SHRPE_STATE_CHANGED = 5
	} shrpe_event_t;
}

class Shrpe : public Stream
{
private:   
    shrpe_state_t _state;
		
		/*
     * Get the next message in shield
     *
     * return: shrpe_result if it was successful/error
     */
		shrpe_result_t getNextMessage(int* msg, size_t* length);
		
public:
    Shrpe();

    /* 
     * Initiate the shield
     */
    int begin();

    /* 
     * Handle shield events
     * Shall be called by app in loop-function
     */
    void loop();
		
    /*
     * Get the shield state
     *
     * return: the state
     */
    shrpe_state_t getState() const
      { return _state; }

    /*
     * Send an UploadObject message.
     * The shield only supports one outgoing message at a time.
     * It is possible to send in any state.
     * If the message is not acknowledged the send is considered failed
     * and the shield tries to re-connect automatically.
     *
     * param buffer: byte array that contains the data to send
     * param size: number of bytes to send
     *
     * return: number of bytes written or SHRPE_ERR_TIMEOUT
     */
    int sendUploadObject(const uint8_t *buffer, size_t size);
    
    /*
     * Receive an UploadObject acknowledgment.
     *
     * param buffer: byte array that will contain the received data after the call
     * param length: the length of the array
     *
     * return: number of bytes received or error (<0)
     */
    int receiveUploadObjectAck();
    
    /*
     * Receive a DownloadObject message, if any pending
     *
     * param buffer: byte array that will contain the received data after the call
     * param length: the length of the array
     *
     * return: number of bytes received or error (<0)
     */
    int receiveDownloadObject(uint8_t *buffer, size_t length);
    
    /*
     * Set contacts
     *
     * param contacts: bit array containing 8 contacts
     *
     * return: result 
     */
    int setContacts(uint8_t contacts);
    
    /*
     * Get shield information
     */
    //int getShieldInfo();

    /* 
     ***************************
     * Standard stream interface
     ***************************
     */
     
    /*
     * Check if a DownloadObject message is available
     *
     * return: number of bytes available, 0 if nothing
     */
    virtual int available();
    /*
     * Read next byte of a DownloadObject message, if available
     * Use function readBytes read mnay bytes at a time
     *
     * return: next byte or -1 if no data is available
     */
    virtual int read();
    /*
     * Peek at next byte of a DownloadObject message, if available
     *
     * return: next byte or -1 if no data is available
     */
    virtual int peek();
    /*
     * Flush the rest of the DownloadObject message, if any
     */
    virtual void flush();
    /*
     * Write the next byte of an UploadObject message
     *
     * return: 1 if success, otherwise 0
     */
    virtual size_t write(const uint8_t byte);
    /*
     * Write the next bytes of an UploadObject message
     *
     * return: the number of bytes written, or 0 in case of error
     */
    virtual size_t write(const uint8_t *buffer, size_t size);
    /*
     * Flush the write buffer, that is, send the UploadObject message
     *
     * return: 0 if success or <0 in case of error
     */
    virtual int flushWriteBuffer();

};

#endif
