#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <RCSwitch.h>
#include <Keypad.h>


RCSwitch mySwitch = RCSwitch();

#define I2C_ADDR  0x3F 
#define BACKLIGHT_PIN  3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
#define btnRIGHT 0  
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5
#define btnUNKNOWN 6
#define btnBACK 7

#define Password_Length 7


LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

char keymap[numRows][numCols]=
{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

byte rowPins[numRows] = {9, 8, 7, 6}; //Rows 0 to 3
byte colPins[numCols]= {5, 4, 3, 2}; //Columns 0 to 3

Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

const char *button[4] ={"FAN              ", "LAMP            ", "DOOR LOCK       ", "SECURITY SYSTEM "}; //MAIN MENU ITEMS ARRAY

const char *states_FAN[4]={"ON              ","AUTO            ","                ","OFF             "};  //STATES ARRAY FOR FAN CONTROL
const char *states_LAMP[4]={"ON              ","AUTO            ","                ","OFF             "}; //STATES ARRAY FOR LAMP CONTROL
const char *states_DOOR_LOCK[4]={"ON              ","UNKNOWN         ","UNKNOWN         ","OFF             "};  //STATES ARRAY FOR DOOR LOCK CONTROL
const char *states_SECURITY_SYSTEM[4]={"ON              ","UNKNOWN         ","UNKNOWN         ","OFF             "};  //STATES ARRAY FOR SECURITY SYSTEM CONTROL

char Data[Password_Length];
char Master[Password_Length] = "123456"; 
byte data_count = 0, master_count = 0;
char customKey;

//THIS FUNCTION READS KEYPAD VALUE AND INITIALIZES THEIR RELEVENT FUNCTIONALITIES
int readkeypad(){
      //int adc_key_in = analogRead(0); 
      int ret_VALUE = btnUNKNOWN;
      char keypressed = myKeypad.getKey();
      Serial.print(keypressed);

      if (keypressed == 'A') ret_VALUE = btnUP;
      if (keypressed == 'B') ret_VALUE = btnRIGHT;
      if (keypressed == 'C') ret_VALUE = btnDOWN;
      if (keypressed == 'D') ret_VALUE = btnLEFT;
      if (keypressed == '*') ret_VALUE = btnSELECT;
      if (keypressed == '#') ret_VALUE = btnBACK;

      return ret_VALUE;
      }

//NAVIGATION MENU FOR-FAN/LAMP/DOOR LOCK/SECURITY SYSTEM
void navigator(){
      lcd.setCursor(0, 0);
      lcd.print("SELECT OPTION: ");
      int option=readkeypad();
      switch(option){
        case 0: //CASE 0 HANDLES FAN CUSTOMIZATIONS
          lcd.clear();        
          lcd.setCursor(0,0);
          lcd.print(button[option]);
          lcd.setCursor(0,1);
          lcd.print("<-            ->");
          while(1){
            option=readkeypad();
            if(option==4){
              lcd.setCursor(0,1);
              lcd.print("SELECTED         ");
              option=32;
              delay(1000);
              break;
            }else if(option==7){
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
              delay(1000);
           //function here
              setSTATE_FAN(5);
            }
          break;
        case 1: // CASE 1 HANDLES THE LAMP
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(button[option]);
          lcd.setCursor(0,1);
          lcd.print("<-            ->");
          while(1){
            option=readkeypad();
            if(option==4){
              lcd.setCursor(0,1);
              lcd.print("SELECTED         ");
              option=32;
              delay(1000);
              break;
            }else if(option==7){
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
              delay(1000);
              setSTATE_LAMP(5);
            }
          break;
        case 2:
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(button[option]);
          lcd.setCursor(0,1);
          lcd.print("<-            ->");
          while(1){
            option=readkeypad();
            if(option==4){
              lcd.setCursor(0,1);
              lcd.print("SELECTED         ");
              option=32;
              delay(1000);
              break;
            }else if(option==7){
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
              delay(1000);
              setSTATE_DOOR_LOCK(5);
            }
          break;
        case 3:
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(button[option]);
          lcd.setCursor(0,1);
          lcd.print("<-            ->");
          while(1){
            option=readkeypad();
            if(option==4){
              lcd.setCursor(0,1);
              lcd.print("SELECTED         ");
              option=32;
              delay(1000);
              break;
            }else if(option==7){
              while(1){
                navigator();
              }
            }
          }
            if(option==32){
              lcd.setCursor(0,0);
              lcd.print("OPTIONS:        ");
              lcd.setCursor(0,1);
              lcd.print("SECURITY SYSTEM ");
              delay(1000);
              lcd.setCursor(0,0);
              lcd.print("ENTER PASSWORD  ");
              lcd.setCursor(0,1);
              lcd.print("                 ");
              bool validity=validate_PASSWORD();
              if(validity){
                lcd.setCursor(0,1);
                lcd.print("CONFIRMED");
                delay(1000);
                lcd.clear();
                setSTATE_SECURITY_SYSTEM(5);
              }else{
                lcd.setCursor(0,1);
                lcd.print("INVALID");
                delay(1000);
                lcd.clear();
                while(1){
                  navigator();
                }
              }
            }
          break;
        default :
          lcd.setCursor(0,1);
          lcd.print("................");
      }
}
void setSTATE_FAN(int option){
  while(1){
            lcd.setCursor(0,0);
            lcd.print("SET STATE:       ");
            switch(option){
              case 0: //ON MODE
                while(1){
                  mySwitch.send('a', 8); 
                  lcd.setCursor(0,1);
                  option=readkeypad();
                  lcd.print(states_FAN[0]);
                  Serial.print("ON");
                  if(option == 1 || option == 3 || option == 7){
                    while(1){
                      setSTATE_FAN(option);
                    }
                    break;
                  }
                }
                break;
              case 1: //AUTOMATIC MODE
                while(1){
                  mySwitch.send('c', 8);
                  lcd.setCursor(0,1);
                  option=readkeypad();
                  lcd.print(states_FAN[1]);
                  Serial.print("AUTO");
                  if(option==0 || option == 3 || option==7){
                    while(1){
                      setSTATE_FAN(option);
                    }
                    break;
                  }
                }
                break;
              case 3: //OFF MODE
                while(1){
                  mySwitch.send('b', 8);
                  lcd.setCursor(0,1);
                  option=readkeypad();
                  lcd.print(states_FAN[3]);
                  Serial.print("OFF");
                  if(option==0 || option == 1 || option==7){
                    while(1){
                      setSTATE_FAN(option);
                    }
                    break;
                  }
                }
                break;
              case 7:
                  lcd.clear();
                  while(1){
                    navigator();
                  }
                  break;
              case 5: //DEFAULT/INITIAL MODE
                while(1){
                  mySwitch.send('c', 8);
                  option=readkeypad();
                  lcd.setCursor(0,1);
                  lcd.print(states_FAN[1]);
                  Serial.print("AUTO");
                  if(option==0 || option == 1 || option == 3 || option==7){
                    while(1){
                      setSTATE_FAN(option);
                    }
                    break;
                  }
                }
                break;
          }
        }
      }
      
void setSTATE_LAMP(int option){
        while(1){
          lcd.setCursor(0,0);
          lcd.print("SET STATE:       ");
           switch(option){
            case 0: //ON MODE 
              while(1){
                mySwitch.send('d', 24);
                lcd.setCursor(0,1);
                option=readkeypad();
                lcd.print(states_LAMP[0]);
                Serial.print("ON");
                if(option == 1 || option == 3 || option == 7){
                    while(1){
                      setSTATE_LAMP(option);
                    }
                    break;
                }
              }
              break;
            case 1: //AUTOMATIC MODE
              
              while(1){
                mySwitch.send('f', 24);
                lcd.setCursor(0,1);
                option=readkeypad();
                lcd.print(states_LAMP[1]);
                Serial.print("AUTO");
                if(option==0 || option == 3 || option==7){
                  while(1){
                    setSTATE_LAMP(option);
                  }
                 break;
                }
              }
              break;
            case 7:
              while(1){
                navigator();
              }
              break;
            case 3: //OFF MODE
              
              while(1){
                mySwitch.send('e', 24);
                lcd.setCursor(0,1);
                option=readkeypad();
                lcd.print(states_LAMP[3]);
                Serial.print("OFF");
                if(option==0 || option == 1 || option==7){
                  while(1){
                    setSTATE_LAMP(option);
                  }
                 break;
                }
              }
              break;
            case 5: //DEFAULT/INITIAL MODE
              
              while(1){
                mySwitch.send('f', 24);
                option=readkeypad();
                lcd.setCursor(0,1);
                lcd.print(states_LAMP[1]);
                Serial.print("AUTO");
                if(option==0 || option == 1 || option == 3 || option==7){
                  while(1){
                    setSTATE_LAMP(option);
                  }
                 break;
                }
              }
              break;
          }
       }
    }
void setSTATE_DOOR_LOCK(int option){
  while(1){
        lcd.setCursor(0,0);
        lcd.print("SET STATE:       ");
        switch(option){
          case 0: //ON MODE 
            
            while(1){
              mySwitch.send('g', 24);
              lcd.setCursor(0,1);
              option=readkeypad();
              lcd.print(states_DOOR_LOCK[0]);
              Serial.print("ON");
              if(option == 1 || option == 3 || option == 7){
                while(1){
                    setSTATE_DOOR_LOCK(option);
                  }
                 break;
              }
            }
            break;
          case 1: //AUTOMATIC MODE
            while(1){
              lcd.setCursor(0,1);
              option=readkeypad();
              lcd.print(states_DOOR_LOCK[1]);
              Serial.print("UNKNOWN");
              if(option==0 || option == 3 || option==7){
                break;
              }
            }
            break;
          case 3: //OFF MODE
            
            while(1){
              mySwitch.send('h', 24);
              lcd.setCursor(0,1);
              option=readkeypad();
              lcd.print(states_DOOR_LOCK[3]);
              Serial.print("OFF");
              if(option==0 || option == 1 || option==7){
                while(1){
                    setSTATE_DOOR_LOCK(option);
                  }
                 break;
              }
            }
            break;
          case 7:
              lcd.clear();
              while(1){
                navigator();
              }
              break;
          case 5: //DEFAULT/INITIAL MODE
            
            while(1){
              mySwitch.send('h', 24);
              option=readkeypad();
              lcd.setCursor(0,1);
              lcd.print(states_DOOR_LOCK[3]);
              Serial.print("OFF");
              if(option==0 || option == 1 || option == 3 || option==7){
                while(1){
                    setSTATE_DOOR_LOCK(option);
                  }
                 break;
              }
            }
            break;
          }
      }
  }
void setSTATE_SECURITY_SYSTEM(int option){
  while(1){
        lcd.setCursor(0,0);
        lcd.print("SET STATE:       ");
        switch(option){
          case 0: //ON MODE
            
            while(1){
              mySwitch.send('i', 24); 
              lcd.setCursor(0,1);
              option=readkeypad();
              lcd.print(states_SECURITY_SYSTEM[0]);
              Serial.print("ON");
              if(option == 1 || option == 3 || option == 7){
                 while(1){
                    setSTATE_SECURITY_SYSTEM(option);
                  }
                 break;
              }
            }
            break;
          case 1: //AUTOMATIC MODE
            while(1){
              lcd.setCursor(0,1);
              option=readkeypad();
              lcd.print(states_SECURITY_SYSTEM[1]);
              Serial.print("UNKNOWN");
              if(option==0 || option == 3 || option==7){
                 while(1){
                    setSTATE_SECURITY_SYSTEM(option);
                  }
                 break;
              }
            }
            break;
          case 3: //OFF MODE
            
            while(1){
              mySwitch.send('j', 24);
              lcd.setCursor(0,1);
              option=readkeypad();
              lcd.print(states_SECURITY_SYSTEM[3]);
              Serial.print("OFF");
              if(option==0 || option == 1 || option==7){
                 while(1){
                    setSTATE_SECURITY_SYSTEM(option);
                  }
                 break;
              }
            }
            break;
          case 7:
              lcd.clear();
              while(1){
                navigator();
              }
              break;
          case 5: //DEFAULT/INITIAL MODE
            
            while(1){
              mySwitch.send('i', 24);
              option=readkeypad();
              lcd.setCursor(0,1);
              lcd.print(states_SECURITY_SYSTEM[3]);
              Serial.print("OFF");
              if(option==0 || option == 1 || option == 3 || option==7){
                 while(1){
                    setSTATE_SECURITY_SYSTEM(option);
                  }
                 break;
              }
            }
            break;
        }
    }
}

void clearData()
{
  while(data_count !=0)
  {
    Data[data_count--] = 0;
  }
  return;
}


bool validate_PASSWORD(){
 while(1)
  {
    lcd.setCursor(0,1);
  
    customKey = myKeypad.getKey();
    if (customKey)
    {
      Data[data_count] = customKey;
      lcd.setCursor(data_count,1);
      lcd.print("*");
      data_count++;
    }
  
    if(data_count == Password_Length-1)
    {
      if(!strcmp(Data, Master)){
        clearData();
        return true;
      }
      else
        return false;
    } 
  }
}
void setup(){
      Serial.begin(9600);
      lcd.begin (16,2);
      lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
      lcd.setBacklight(HIGH);
      mySwitch.enableTransmit(11);  // Transmitter is connected to Arduino Pin #11  
      }

void loop(){
  navigator(); 
}
      
