#include <LiquidCrystal.h>

#define btnRIGHT 0  
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5
#define btnUNKNOWN 6

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


const char *button[7] ={"FAN              ", "LAMP            ", "DOOR LOCK       ", "SECURITY SYSTEM ", "", "", "??????"}; //MAIN MENU ITEMS ARRAY

const char *states_FAN[4]={"ON              ","AUTO            ","                ","OFF             "};  //STATES ARRAY FOR FAN CONTROL
const char *states_LAMP[4]={"ON              ","AUTO            ","                ","OFF             "}; //STATES ARRAY FOR LAMP CONTROL
const char *states_DOOR_LOCK[2]={"ON              ","OFF             "};  //STATES ARRAY FOR DOOR LOCK CONTROL
const char *states_SECURITY_SYSTEM[2]={"ON              ","OFF             "};  //STATES ARRAY FOR SECURITY SYSTEM CONTROL

//THIS FUNCTION CREATES WORD,"SELECTED" IN THE LCD

int readkeypad(){
      int adc_key_in = analogRead(0); 
      int ret_VALUE = btnUNKNOWN;

      if (adc_key_in < 50) ret_VALUE = btnRIGHT;
      if ((adc_key_in > 500) && (adc_key_in < 1150)) ret_VALUE = btnNONE;
      if ( (adc_key_in > 120) && (adc_key_in < 150) ) ret_VALUE = btnUP;
      if ( (adc_key_in > 250) && (adc_key_in < 350) ) ret_VALUE = btnDOWN;
      if ( (adc_key_in > 450) && (adc_key_in < 500) ) ret_VALUE = btnLEFT;
      if ( (adc_key_in > 700) && (adc_key_in < 750) ) ret_VALUE = btnSELECT;

      return ret_VALUE;
      }

//NAVIGATION MENU FOR-FAN/LAMP/DOOR LOCK/SECURITY SYSTEM
void navigator(){
      lcd.setCursor(0, 0);
      lcd.print("SELECT OPTION:");
      lcd.setCursor(0,1);
      int option=readkeypad();
      switch(option){
        case 0: //CASE 0 HANDLES FAN CUSTOMIZATIONS
          lcd.print(button[option]);
          while(1){
            option=readkeypad();
            if(option==4){
              lcd.setCursor(0,1);
              lcd.print("SELECTED         ");
              option=32;
              delay(1000);
              break;
            }else if(option==1||option==2||option==3){
              while(1){
                navigator();
              }
            }
          }
            if(option==32){
              lcd.setCursor(0,0);
              lcd.print("OPTIONS:FAN      ");
              lcd.setCursor(0,1);
              lcd.print("                 ");
              delay(2000);
              while(1){
                lcd.setCursor(0,0);
                lcd.print("SET STATE:       ");
                option=readkeypad();
                switch(option){
                  case 0: //ON MODE 
                    while(1){
                      lcd.setCursor(0,1);
                      option=readkeypad();
                      lcd.print(states_FAN[option]);
                      Serial.print("ON");
                      if(option == 1 || option == 3 || option == 2){
                        break;
                      }
                      //ON MODE FUNCTION HERE
                    }
                    break;
                  case 1: //AUTOMATIC MODE
                    while(1){
                      lcd.setCursor(0,1);
                      option=readkeypad();
                      lcd.print(states_FAN[option]);
                      Serial.print("AUTO");
                      if(option==0 || option == 3 || option==2){
                        break;
                      }
                      //AUTOMATIC MODE FUNCTION HERE
                    }
                    break;
                  case 3: //OFF MODE
                    while(1){
                      lcd.setCursor(0,1);
                      option=readkeypad();
                      lcd.print(states_FAN[option]);
                      Serial.print("OFF");
                      if(option==0 || option == 1 || option==2){
                        break;
                      }
                      //OFF MODE FUNCTION HERE
                    }
                    break;
                  case 2:
                      lcd.clear();
                      while(1){
                        navigator();
                      }
                      break;
                  case 5: //DEFAULT/INITIAL MODE
                    while(1){
                      option=readkeypad();
                      lcd.setCursor(0,1);
                      lcd.print(states_FAN[1]);
                      Serial.print("AUTO");
                      //DEFAULT MODE FUNCTION HERE
                      if(option==0 || option == 1 || option == 3 || option==2){
                        break;
                      }
                    }
                    break;
            }
            }
            }
          break;
        case 1: // CASE 1 HANDLES THE LAMP
          lcd.print(button[option]);
          while(1){
            option=readkeypad();
            if(option==4){
              lcd.setCursor(0,1);
              lcd.print("SELECTED         ");
              option=32;
              delay(1000);
              break;
            }else if(option==0||option==2||option==3){
              while(1){
                navigator();
              }
            }
          }
          if(option==32){
              lcd.setCursor(0,0);
              lcd.print("OPTIONS:LAMP      ");
              lcd.setCursor(0,1);
              lcd.print("                 ");
              delay(2000);
              while(1){
                lcd.setCursor(0,0);
                lcd.print("SET STATE:       ");
                option=readkeypad();
                 switch(option){
                  case 0: //ON MODE 
                    while(1){
                      lcd.setCursor(0,1);
                      option=readkeypad();
                      lcd.print(states_LAMP[option]);
                      Serial.print("ON");
                      if(option == 1 || option == 3 || option == 2){
                        break;
                      }
                      //ON MODE FUNCTION HERE
                    }
                    break;
                  case 1: //AUTOMATIC MODE
                    while(1){
                      lcd.setCursor(0,1);
                      option=readkeypad();
                      lcd.print(states_LAMP[option]);
                      //AUTOMATIC MODE FUNCTION HERE
                      Serial.print("AUTO");
                      if(option==0 || option == 3 || option==2){
                        break;
                      }
                    }
                    break;
                  case 2:
                    while(1){
                      navigator();
                    }
                    break;
                  case 3: //OFF MODE
                    while(1){
                      lcd.setCursor(0,1);
                      option=readkeypad();
                      lcd.print(states_LAMP[option]);
                      Serial.print("OFF");
                      if(option==0 || option == 1 || option==2){
                        break;
                      }
                      //OFF MODE FUNCTION HERE
                    }
                    break;
                  case 5: //DEFAULT/INITIAL MODE
                    while(1){
                      option=readkeypad();
                      lcd.setCursor(0,1);
                      lcd.print(states_LAMP[1]);
                      Serial.print("AUTO");
                      //DEFAULT MODE FUNCTION HERE
                      if(option==0 || option == 1 || option == 3 || option==2){
                        break;
                      }
                    }
                    break;
            }
            }
            }
          break;
        case 2:
          lcd.print(button[option]);
          while(1){
            option=readkeypad();
            if(option==4){
              lcd.setCursor(0,1);
              lcd.print("SELECTED         ");
              option=32;
              delay(1000);
              break;
            }else if(option==0||option==1||option==3){
              while(1){
                navigator();
              }
            }
          }
            if(option==32){
              lcd.setCursor(0,0);
              lcd.print("OPTIONS:DOORLOCK");
              lcd.setCursor(0,1);
              lcd.print("                 ");
              delay(2000);
              while(1){
                lcd.setCursor(0,0);
                lcd.print("SET STATE:       ");
                option=readkeypad();
                switch(option){
                  case 0: //ON MODE 
                    while(1){
                      lcd.setCursor(0,1);
                      option=readkeypad();
                      lcd.print(states_FAN[option]);
                      Serial.print("ON");
                      if(option == 1 || option == 3 || option == 2){
                        break;
                      }
                      //ON MODE FUNCTION HERE
                    }
                    break;
                  case 1: //AUTOMATIC MODE
                    while(1){
                      lcd.setCursor(0,1);
                      option=readkeypad();
                      lcd.print(states_FAN[option]);
                      Serial.print("AUTO");
                      if(option==0 || option == 3 || option==2){
                        break;
                      }
                      //AUTOMATIC MODE FUNCTION HERE
                    }
                    break;
                  case 3: //OFF MODE
                    while(1){
                      lcd.setCursor(0,1);
                      option=readkeypad();
                      lcd.print(states_FAN[option]);
                      Serial.print("OFF");
                      if(option==0 || option == 1 || option==2){
                        break;
                      }
                      //OFF MODE FUNCTION HERE
                    }
                    break;
                  case 2:
                      lcd.clear();
                      while(1){
                        navigator();
                      }
                      break;
                  case 5: //DEFAULT/INITIAL MODE
                    while(1){
                      option=readkeypad();
                      lcd.setCursor(0,1);
                      lcd.print(states_FAN[1]);
                      Serial.print("AUTO");
                      //DEFAULT MODE FUNCTION HERE
                      if(option==0 || option == 1 || option == 3 || option==2){
                        break;
                      }
                    }
                    break;
            }
            }
            }
          break;
        case 3:
          lcd.print(button[option]);
          while(1){
            option=readkeypad();
            if(option==4){
              lcd.setCursor(0,1);
              lcd.print("SELECTED         ");
              option=32;
              delay(1000);
              break;
            }else if(option==1||option==2||option==3){
              while(1){
                navigator();
              }
            }
          }
            if(option==32){
              lcd.setCursor(0,0);
              lcd.print("OPTIONS:FAN      ");
              lcd.setCursor(0,1);
              lcd.print("                 ");
              delay(2000);
              while(1){
                lcd.setCursor(0,0);
                lcd.print("SET STATE:       ");
                option=readkeypad();
                switch(option){
                  case 0: //ON MODE 
                    while(1){
                      lcd.setCursor(0,1);
                      option=readkeypad();
                      lcd.print(states_FAN[option]);
                      Serial.print("ON");
                      if(option == 1 || option == 3 || option == 2){
                        break;
                      }
                      //ON MODE FUNCTION HERE
                    }
                    break;
                  case 1: //AUTOMATIC MODE
                    while(1){
                      lcd.setCursor(0,1);
                      option=readkeypad();
                      lcd.print(states_FAN[option]);
                      Serial.print("AUTO");
                      if(option==0 || option == 3 || option==2){
                        break;
                      }
                      //AUTOMATIC MODE FUNCTION HERE
                    }
                    break;
                  case 3: //OFF MODE
                    while(1){
                      lcd.setCursor(0,1);
                      option=readkeypad();
                      lcd.print(states_FAN[option]);
                      Serial.print("OFF");
                      if(option==0 || option == 1 || option==2){
                        break;
                      }
                      //OFF MODE FUNCTION HERE
                    }
                    break;
                  case 2:
                      lcd.clear();
                      while(1){
                        navigator();
                      }
                      break;
                  case 5: //DEFAULT/INITIAL MODE
                    while(1){
                      option=readkeypad();
                      lcd.setCursor(0,1);
                      lcd.print(states_FAN[1]);
                      Serial.print("AUTO");
                      //DEFAULT MODE FUNCTION HERE
                      if(option==0 || option == 1 || option == 3 || option==2){
                        break;
                      }
                    }
                    break;
            }
            }
            }
          break;
        default :
          lcd.print("");
      }
}
      
void setup(){
      Serial.begin(9600);
      lcd.begin(16, 2);
      }

void loop(){
  navigator();
}
      
