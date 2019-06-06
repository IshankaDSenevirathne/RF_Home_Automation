#include <RCSwitch.h>
int key = 4452;
RCSwitch mySwitch = RCSwitch();

void setup() {
  mySwitch.enableTransmit(10);  // Using Pin #10
  Serial.begin(9600);
}

int pins[] = {A1, A4, A3, A2, A0};
int values[] = {0, 0, 0, 0, 0,};

void loop() {
    for (int i = 0; i < 5; i++) {
      int val = analogRead(pins[i]);
      if (val > 1000) {
        if (values[i] == 0) {
          values[i] = 1;
          sendButton((i * 2) + 1);//i=1:val=3
        }
      } else {
        if (values[i] > 0) {
          values[i] = 0;
          sendButton((i * 2));//i=1;val=2
        }
      }
    }
}

void sendButton(int b) {
  sendData(b, key);
}
void sendData(int b, int k) {
  Serial.println(b);
  int sendint = b + key;
  String sendbinary = String(sendint, BIN);
  char charBuf[24];
  sendbinary.toCharArray(charBuf, 24) ;
  mySwitch.send(charBuf);
}