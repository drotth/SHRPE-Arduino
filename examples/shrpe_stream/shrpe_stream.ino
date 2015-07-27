#include <Shrpe.h>
#include <SoftwareSerial.h>

Shrpe shrpe;
SoftwareSerial mySerial(10, 11); // RX, TX
shrpe_state_t currentState;
uint8_t loopCounter = 0;
bool isSending = false;

uint8_t upl_obj[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                     11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                     21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
                     31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41
                    };
uint8_t receiveBuffer[38];
uint8_t oneByte = 5;

void setup() {
  //init shield and serialport
  shrpe.begin();
  mySerial.begin(115200);
  mySerial.println("\nStarting SHRPE demo example");

  // get current state
  currentState = shrpe.getState();
}

void loop() {
  // this loop executes approx once a second.

  //let shield lib execute
  shrpe.loop();

  // check shield state
  shrpe_state_t newState;
  newState = shrpe.getState();
  if (newState != currentState) {
    Serial.print("New shield state: ");
    Serial.println(newState);
    currentState = newState;
  }

  //time to send?
  int resultWrite;
  if (++loopCounter % 5 == 0) {
    //resultWrite = shrpe.write(oneByte);
    resultWrite = shrpe.write(upl_obj, 41);
    if (resultWrite == sizeof(upl_obj) || 40) {
      int flushResult = shrpe.flushWriteBuffer();
      if (flushResult < 0) {
        mySerial.print("failed to flushWriteBuffer(), result: ");
        mySerial.println(flushResult);
      }
    }
    mySerial.print("wrote with result: ");
    mySerial.println(resultWrite);
  }
  // download an object if any
  int result;
  while (shrpe.available()) {
    mySerial.print(shrpe.read());
    if (shrpe.available() >= 1) {
      mySerial.print(", ");
    } else {
      mySerial.println();
      mySerial.println();
    }
  }
  //shrpe.flush();
  if (result > 0) {
    // if object received
    mySerial.print("\nReceived download object of length: ");
    mySerial.println(result);
  }
  delay(1000);
}
