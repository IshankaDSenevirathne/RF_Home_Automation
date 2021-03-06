#include <RCSwitch.h>
#include <Servo.h>
#include <SimpleDHT.h>

#define pirInputPin  8 
#define fanInputPin  3
#define lampInputPin  5
#define servoPin 10
#define buzzerPin 12


Servo myservo;  
RCSwitch mySwitch = RCSwitch();


int pinDHT11 = 4;
SimpleDHT11 dht11(pinDHT11);

char recieved_DATA; //to fetch RF data incoming
int pirState = LOW; // initiate from no motion detected
int pirVal = 0; // for reading the pin status

void init_FAN_ON(){
  digitalWrite(fanInputPin,HIGH);
}
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
  myservo.write(80); // sets the servo position to close the lock
}
void init_DOORLOCK_OFF(){
//  digitalWrite(doorlockInputPin,LOW);
  pirVal = digitalRead(pirInputPin);
  if(pirVal==LOW){
  myservo.write(80); 
  }
  if(pirVal==HIGH){
  myservo.write(0);
  }
}
void init_SECURITY_ON(){
  init_DOORLOCK_ON();
  pirVal = digitalRead(pirInputPin);
  if(pirVal==HIGH){
    digitalWrite(buzzerPin,HIGH);
    delay(100);
    digitalWrite(buzzerPin,LOW);
  }else if(pirVal==LOW){
    digitalWrite(buzzerPin,LOW);  
  }
  //alarm settings here
}
void init_SECURITY_OFF(){
//  digitalWrite(securityInputPin,LOW);
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
    if(recieved_DATA=='c'){
        while(recieved_DATA!='a'|| recieved_DATA!='b'){
              byte temperature =0;
              byte humidity = 0;
              recieved_DATA=char(mySwitch.getReceivedValue());
              int err = SimpleDHTErrSuccess;
              if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
                Serial.print("Read DHT11 failed, err="); Serial.println(err);
                return;
              }
              
              
            //  Serial.print((int)temperature); Serial.print(" *C, "); 
            //  Serial.print((int)humidity); Serial.println(" H");
              int dht_temp = (int)temperature;
              int temp_mapped = map(dht_temp, 25,40, 0,255);
            //  Serial.print(temp_mapped);
              analogWrite(fanInputPin, temp_mapped);
              //Serial.print(temp_mapped);
              //delay(500);
              mySwitch.resetAvailable();
              control_FLOW();
        }
    }
    else if(recieved_DATA=='d'){
      init_LAMP_ON();
    }
    else if(recieved_DATA=='e'){
      init_LAMP_OFF();
    }
    else if(recieved_DATA=='f'){
      //constantly check for motion
        pirVal = digitalRead(pirInputPin);  // read input value
        if (pirVal == HIGH) {            // check if the input is HIGH 
              Serial.println("Motion detected!");
              pirState = HIGH;
              int ldr_val = analogRead(A0);
              Serial.println(ldr_val);
              int pwm_LAMP = map(ldr_val, 0, 850, 0,255);
              //Serial.println(pwm_LAMP);
              analogWrite(lampInputPin, 255-pwm_LAMP);
        }
         else if(pirVal == LOW){
          analogWrite(lampInputPin, 0); 
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
  pinMode(buzzerPin,OUTPUT);
  pinMode(fanInputPin,OUTPUT);
  pinMode(lampInputPin,OUTPUT);
//  pinMode(doorlockInputPin,OUTPUT);
//  pinMode(securityInputPin,OUTPUT);
  myservo.attach(servoPin);  //Attach Servo to servoPin
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 pin 2
}

void loop() {
  control_FLOW();
}
