#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

char recieved_DATA;

void init_FAN_ON(){
  digitalWrite(3,HIGH);
}
void init_FAN_AUTO(){
  
}
void init_FAN_OFF(){
  digitalWrite(3,LOW);
}
void init_LAMP_ON(){
  digitalWrite(5,HIGH);
}
void init_LAMP_AUTO(){
  
}
void init_LAMP_OFF(){
  digitalWrite(5,LOW);
}
void init_DOORLOCK_ON(){
  digitalWrite(6,HIGH);
}
void init_DOORLOCK_OFF(){
  digitalWrite(6,LOW);
}
void init_SECURITY_ON(){
  digitalWrite(7,HIGH);
}
void init_SECURITY_OFF(){
  digitalWrite(7,LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}

void loop() {
  if (mySwitch.available()) {
    
    Serial.print("Received: ");
    recieved_DATA=char(mySwitch.getReceivedValue());
    Serial.println(recieved_DATA);
    if(recieved_DATA=='a'){
      init_FAN_ON();
    }
    else if(recieved_DATA=='b'){
      init_FAN_OFF();
    }
//    if(recieved_DATA=='c'){
//      init_FAN_AUTO();
//    }
    else if(recieved_DATA=='d'){
      init_LAMP_ON();
    }
    else if(recieved_DATA=='e'){
      init_LAMP_OFF();
    }
//    if(recieved_DATA=='f'){
//      init_LAMP_AUTO();
//    }
    else if(recieved_DATA=='g'){
      init_DOORLOCK_ON();
    }
    else if(recieved_DATA=='h'){
      init_DOORLOCK_OFF();
    }
    else if(recieved_DATA=='i'){
      init_SECURITY_ON();
    }
    else if(recieved_DATA=='j'){
      init_SECURITY_OFF();
    }
   }
   mySwitch.resetAvailable();
}
