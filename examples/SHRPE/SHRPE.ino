/*
  Looping Write with SHRPE

  A simple example of how to use the 'write' and 'read' functionality
  with the SHRPE library. The program loops forever,
  continuously sending an array of 40 bytes, every 5th second 
  and waiting for a response message (ACK/NACK).
  If there is data available, it will read the data.

  Notice the shrpe.begin() call in the setup function.
  This function is necessary for the Shrpe object to function
  properly.

  Created 1 July 2015
  By Andreas Drotth & Soded Alatia
*/

#include <Shrpe.h>

Shrpe shrpe;
uint8_t counter = 0;
int result = 0;

void setup()
{
  shrpe.begin();
}

void loop()
{
  uint8_t array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                     11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                     21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
                     31, 32, 33, 34, 35, 36, 37, 38, 39, 40
                    };

  if (counter % 5 == 0) {
    result = shrpe.write(array, sizeof(array));
    //wait for ACK/NACK response from Radio.
    while(!shrpe.available());		
    uint8_t event_ack[2];		
    //MSG_TYPE: event_ack[0]
    //ACK RESULT: event_ack[1]  (0 if OK, 1 if NACK)
    int len = shrpe.read(event_ack, 2);
    if(event_ack[0] == MSG_UPLOAD_OBJECT) {
      int ack = event_ack[1];
    } else {
      //error.. it wasn't an upload_object msg
    }
  }
  
  if (shrpe.available()) {
    uint8_t incoming_data[38];
    int len;
    //len == length of incoming_data
    len = shrpe.read(incoming_data, 38);
  }
  counter++;
  delay(1000);
}
