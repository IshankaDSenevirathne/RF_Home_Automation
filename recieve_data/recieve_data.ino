#include <RCSwitch.h>

#define pirInputPin  8 
#define fanInputPin  3
#define lampInputPin_one  5
#define lampInputPin_two  9
#define doorlockInputPin  6
#define securityInputPin  7


RCSwitch mySwitch = RCSwitch();

char recieved_DATA; //to fetch RF data incoming
int pirState = LOW; // initiate from no motion detected
int pirVal = 0; // for reading the pin status

//double temp_DATA(){
//  float val;
//  int tempPin = A3;
//  val = analogRead(tempPin);
//  float mv = ( val/1024.0)*5000;
//  Serial.print(mv);
//  Serial.println();
//  return mv;
//}

void adaptiveBrightness(){
  
}

void init_FAN_ON(){
  digitalWrite(fanInputPin,HIGH);
}
//void init_FAN_AUTO(){
//  while()
//  float mv=temp_Data();
// 
//}
void init_FAN_OFF(){
  digitalWrite(fanInputPin,LOW);
}
void init_LAMP_ON(){
  digitalWrite(lampInputPin_one,HIGH);
  digitalWrite(lampInputPin_two,HIGH);
}
void init_LAMP_OFF(){
  digitalWrite(lampInputPin_one,LOW);
  digitalWrite(lampInputPin_two,LOW);
}
void init_DOORLOCK_ON(){
  digitalWrite(doorlockInputPin,HIGH);
}
void init_DOORLOCK_OFF(){
  digitalWrite(doorlockInputPin,LOW);
}
void init_SECURITY_ON(){
  digitalWrite(7,HIGH);
}
void init_SECURITY_OFF(){
  digitalWrite(securityInputPin,LOW);
}
void control_FLOW(){
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
//      init_FAN_AUTO(temp_DATA());
//    }
    else if(recieved_DATA=='d'){
      init_LAMP_ON();
    }
    else if(recieved_DATA=='e'){
      init_LAMP_OFF();
    }
    if(recieved_DATA=='f'){
      //constantly check for motion
      while(recieved_DATA!='d'||recieved_DATA!='e'){
        pirVal = digitalRead(pirInputPin);  // read input value
        if (pirVal == HIGH) {            // check if the input is HIGH
          if (pirState == LOW) {  
            Serial.println("Motion detected!");
            digitalWrite(lampInputPin_one,LOW);
            digitalWrite(lampInputPin_two,HIGH);
            pirState = HIGH;
          }
        } else {
          if (pirState == HIGH){
            Serial.println("Motion ended!");
            digitalWrite(lampInputPin_one,LOW);
            digitalWrite(lampInputPin_two,LOW);
            pirState = LOW;
          }
        }
        mySwitch.resetAvailable();
        control_FLOW();
      }
    }
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

void setup() {
  Serial.begin(9600);
  pinMode(pirInputPin, INPUT);
  pinMode(fanInputPin,OUTPUT);
  pinMode(lampInputPin_one,OUTPUT);
  pinMode(lampInputPin_two,OUTPUT);
  pinMode(doorlockInputPin,OUTPUT);
  pinMode(securityInputPin,OUTPUT);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 pin 2
}

void loop() {
  control_FLOW();
}
