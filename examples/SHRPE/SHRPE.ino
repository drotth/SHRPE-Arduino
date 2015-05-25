#include <Shrpe.h>

Shrpe shrpe;

void setup()
{
  shrpe.begin();
}

void loop()
{
  uint8_t array[] = "hejhej";
  //uint8_t array[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  //shrpe.uploadObject(array, sizeof(array));
  
  uint8_t testbyte = 5;
  shrpe.uploadObject(testbyte);
  
  delay(10000); //wait then loop
}
