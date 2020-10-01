#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int result = 0;
void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(11);
}

void loop() {
  result = mySwitch.send('a', 24);
  delay(1000);   
  if(result == 0){
    Serial.println("Transmit succesfully");
  }else{
    Serial.printin("Something wrong");
  }
  
}
