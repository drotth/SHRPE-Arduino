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

  Created 10 June 2015
  By Andreas Drotth & Soded Alatia
*/

#include <Shrpe.h>
#include <SoftwareSerial.h>

Shrpe shrpe;
SoftwareSerial mySerial(10, 11); // RX, TX
uint8_t counter = 0;
boolean ul_obj = false;
boolean dl_obj = false;

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
    int result = shrpe.write(array, sizeof(array));
    int result2 = shrpe.write(array, sizeof(array));
    mySerial.println("Uploading object: 40 bytes");
    mySerial.print("write result: ");
    mySerial.println(result);
    mySerial.print("write the second result: ");
    mySerial.println(result2);
    if(result2 == 1) {
      delay(100);
      mySerial.println("waiting 100ms before i send again...");
      result2 = shrpe.write(array, sizeof(array));
      mySerial.print("writing the result of the second retry: ");
      mySerial.println(result2);
      mySerial.println();
    } else {
      result = shrpe.write(array, sizeof(array));
      mySerial.println("It was OK to send again");
    }

  }
  if (shrpe.available()) {
    uint8_t incoming_data[38];
    int len;
    len = shrpe.read(incoming_data, 38);
    mySerial.print("downloading object of length: ");
    mySerial.println(len);
    shrpe.write(incoming_data, len);
  }
  counter++;
  delay(1000);
}
