#include <Shrpe_newlib.h>
#include <SoftwareSerial.h>

Shrpe shrpe;
SoftwareSerial mySerial(10, 11); // RX, TX
shrpe_state_t currentState;
uint8_t loopCounter = 0;
bool isSending = false;

uint8_t upl_obj[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                     11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                     21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
                     31, 32, 33, 34, 35, 36, 37, 38, 39, 40
                    };
uint8_t receiveBuffer[38];

void setup() {
  //init shield and serialport
  shrpe.begin();
  mySerial.begin(115200);
  mySerial.println("\nStarting SHRPE demo example");
}

void loop() {
  // this loop executes approx once a second.

  //let shield lib execute
  shrpe.loop();

  if (currentState == SHRPE_STATE_CONNECTED) {
    int ack_res;
    if (isSending) {
      ack_res = shrpe.receiveUploadObjectAck();
      mySerial.print("Received upload object ack: ");
      mySerial.println(ack_res);
      if (ack_res == 0) {
        isSending = false;
      }
    } else {
      //time to send?
      int result;
      if (++loopCounter % 5 == 0) {
        result = shrpe.sendUploadObject(upl_obj, sizeof(upl_obj));
        mySerial.print("Sent upload object with result: ");
        mySerial.println(result);
        if (result == sizeof(upl_obj)) {
          isSending = true;
        }
      }
    }
    // download an object if any
    int result = shrpe.receiveDownloadObject(receiveBuffer, sizeof(receiveBuffer));
    if (result > 0) {
      // if object received
      mySerial.print("\nReceived download object of length: ");    
      mySerial.println(result);
    }
  } else {
      //check shield state
      currentState = shrpe.getState();
      mySerial.print("currentState: ");
      mySerial.println(currentState);
  }
  delay(1000);
}
