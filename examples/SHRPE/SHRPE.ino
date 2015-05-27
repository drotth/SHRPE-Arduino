#include <Shrpe.h>

Shrpe shrpe;
uint8_t array[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
uint8_t array2[] = {7,8,9};
char incomingByte = 0;
//char buffer[3];

void setup()
{
  shrpe.begin();
}

void loop()
{
  //if (shrpe.getData()){
    //shrpe.uploadObject(array, sizeof(array));
  //}
  //delay(2000); //wait then loop
  
//  if (Serial.available() > 0) {
//                // read the incoming byte:
//                incomingByte = Serial.read();
//                //Serial.readBytes(buffer, Serial.available());
//
//                // say what you got:
//                Serial.print("I received: ");
//                Serial.println(incomingByte);
//                //Serial.println(buffer);
//        }
}
