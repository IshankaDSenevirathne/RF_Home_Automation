#include <RCSwitch.h>
int key = 4452;
RCSwitch mySwitch = RCSwitch();
boolean button[] = {false, false, false, false, false};
void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
}

void loop() {
  if (mySwitch.available()) {
    int value = mySwitch.getReceivedValue() - key;
    if (value > -1 && value < 11) {
      int index = (value / 2);//0
      int state = value - (index * 2);//1
      if (button[index] != state) {
        button[index] = state;
        Serial.print("*");
        Serial.print(index);
        Serial.println(state);
      }
    }
  }
  mySwitch.resetAvailable();
}

