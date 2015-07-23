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
                     31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41
                    };
uint8_t receiveBuffer[38];

void setup() {
  //init shield and serialport
  int state = shrpe.begin();
  mySerial.begin(115200);
  mySerial.println("\nStarting SHRPE demo example");
  mySerial.print("Current state: ");
  mySerial.println(state);

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

  uint8_t ack_res[2];
  size_t buf_len = 2;
  int ack_len;
  if (isSending) {
    ack_len = shrpe.receiveUploadObjectAck(ack_res, buf_len);
    if(ack_len == 1) {
      mySerial.print("ack received?: ");
      mySerial.println(ack_res[0]);
      
      if(ack_res[0] == 1) {
        mySerial.print("ack result: ");
        mySerial.println(ack_res[1]);
        
        if (ack_res[1] == 0) {
          isSending = false;
          
          //setContacts after an ack has been received
          static uint8_t contacts = 0;
          //alternate between 0 and 2
          contacts = (contacts ^ 0x02);
          int result = shrpe.setContacts(contacts);
          mySerial.print("setContacts result: ");
          mySerial.println(result);
        }
      }    
    }
  } else {
    //time to send?
    int result;
    if (++loopCounter % 5 == 0) {
      result = shrpe.sendUploadObject(upl_obj, sizeof(upl_obj));
      mySerial.print("Sent upload object with result: ");
      mySerial.println(result);
      //result = (sizeof(upl_obj) < 40) ?  sizeof(upl_obj) : 40;
      if (result == sizeof(upl_obj) || result == 40) {
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
  delay(1000);
}
