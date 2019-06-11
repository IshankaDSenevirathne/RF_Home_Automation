#include <RCSwitch.h>
#include <Servo.h>

#define pirInputPin  8 
#define fanInputPin  3
#define lampInputPin  5
#define doorlockInputPin  6
#define securityInputPin  7
#define servoPin 10

Servo myservo;  
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
  digitalWrite(lampInputPin,HIGH);
}
void init_LAMP_OFF(){
  digitalWrite(lampInputPin,LOW);
}
void init_DOORLOCK_ON(){
  digitalWrite(doorlockInputPin,HIGH);
  //servo control here
  myservo.write(0); // sets the servo position to close the lock
  delay(15); // waits for the servo to get there
}
void init_DOORLOCK_OFF(){
  digitalWrite(doorlockInputPin,LOW);
  myservo.write(90); // sets the servo position to open the lock
  delay(15); // waits for the servo to get there
}
void init_SECURITY_ON(){
  digitalWrite(7,HIGH);
  init_DOORLOCK_ON();
  //alarm settings here
  
}
void init_SECURITY_OFF(){
  digitalWrite(securityInputPin,LOW);
  //alarm settings here
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
            digitalWrite(lampInputPin,HIGH);
            pirState = HIGH;
          }
        } else {
          if (pirState == HIGH){
            Serial.println("Motion ended!");
            digitalWrite(lampInputPin,LOW);
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
  pinMode(lampInputPin,OUTPUT);
  pinMode(doorlockInputPin,OUTPUT);
  pinMode(securityInputPin,OUTPUT);
  myservo.attach(servoPin);  //Attach Servo to servoPin
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 pin 2
}

void loop() {
  control_FLOW();
}
