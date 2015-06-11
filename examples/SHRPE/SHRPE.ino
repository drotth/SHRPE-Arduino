/*
  Looping Write with SHRPE

  A simple example of how to use the 'write' functionality
  with the SHRPE library. The program loops forever,
  continuously sending an array of 40 bytes, every third second.

  Notice the shrpe.begin() call in the setup function.
  This function is necessary for the Shrpe object to function
  properly.

  Created 28 May 2015
  By Andreas Drotth & Soded Alatia
*/

#include <Shrpe.h>

Shrpe shrpe;
uint8_t counter = 0;
boolean ul_obj = false;
boolean dl_obj = false;

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
    shrpe.write(array, sizeof(array));
  }
  if (shrpe.available()) {
    uint8_t incoming_data[38];
    int len;
    len = shrpe.downloadObject(incoming_data, 38);
    shrpe.write(incoming_data, len);
  }
  counter++;
  delay(1000);
}
