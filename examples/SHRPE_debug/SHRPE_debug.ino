/*
  Looping Write with SHRPE

  A simple example of how to use the 'write' and 'read' functionality
  with the SHRPE library. The program loops forever,
  continuously sending an array of 40 bytes, every 5th second.
  If there is data available (sent from the gateway), it will read 
  the data and send it back.

  Notice the shrpe.begin() call in the setup function.
  This function is necessary for the Shrpe object to function
  properly.

  Created 30 June 2015
  By Andreas Drotth & Soded Alatia
*/

#include <Shrpe.h>
#include <SoftwareSerial.h>

Shrpe shrpe;
SoftwareSerial mySerial(10, 11); // RX, TX
uint8_t counter = 0;
int result = 0;

void setup()
{
  shrpe.begin();
  mySerial.begin(115200);
}

void loop()
{
  uint8_t array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                     11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                     21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
                     31, 32, 33, 34, 35, 36, 37, 38, 39, 40
                    };

  if (counter % 5 == 0) {
    mySerial.println("\nUploading 1 object: 40 bytes");
    result = shrpe.write(array, sizeof(array));		
    mySerial.print("write result of first object: ");		
    mySerial.println(result);		
    while(!shrpe.available());		
    uint8_t event_ack[2];		
    int len = shrpe.read(event_ack, 2);		
    mySerial.print("Length of event_ack: ");		
    mySerial.println(len);		
    mySerial.print("MSG TYPE: ");		
    mySerial.println(event_ack[0]);	
    mySerial.print("ACK RESULT: ");		
    mySerial.println(event_ack[1]);
    /*result = shrpe.write(array, sizeof(array));		
    mySerial.print("write result of second object: ");		
    mySerial.println(result);
    if(result == 1) {		
      delay(100);		
      mySerial.println("waiting 100ms before i send again...");		
      result = shrpe.write(array, sizeof(array));		
      mySerial.print("writing the result of the second retry: ");		
      mySerial.println(result);		
    } else {		
      result = shrpe.write(array, sizeof(array));		
      mySerial.println("It was OK to send again");		
      mySerial.print("Result of last write: ");		
      mySerial.println(result);		
    }		
    */
  }
  
  if (shrpe.available()) {
    uint8_t incoming_data[38];
    int len;
    len = shrpe.read(incoming_data, 38);
    mySerial.print("downloading object of length: ");
    mySerial.println(len);
  }
  counter++;
  delay(1000);
}
