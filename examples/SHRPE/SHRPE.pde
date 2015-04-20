#include <Shrpe.h>

Shrpe shrpe();

void setup()
{
  shrpe.logIn();
}

void loop()
{
  shrpe.sendData();
  delay(3000);
}

