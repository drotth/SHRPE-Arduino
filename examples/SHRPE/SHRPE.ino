//#include <Shrpe.h>

//Shrpe shrpe();
volatile uint8_t incoming = 0;
volatile uint8_t dataRecieved = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  digitalWrite(2, HIGH);
  attachInterrupt(0, irq_handler, FALLING);
  delay(7000); // fot the shield to boot up
}

void loop()
{
  Serial.write(19); //dummy to notice shield we're about to send
  delay(10);
  incoming = 0;
  
  //uint8_t array[10] = {9, 0,1,2,3,4,5,6,7,8};
  //Serial.write(array,10);
  Serial.write(9);
  
//  if (incoming == 1){
//    dataRecieved = Serial.read();
//    incoming = 0;
//  }
  
  Serial.write(dataRecieved);
  
  delay(10000); //wait then loop
  
}

void irq_handler(){
  incoming = 1;
  digitalWrite(13, !digitalRead(13));
  dataRecieved = Serial.read();
}


