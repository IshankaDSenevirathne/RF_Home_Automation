#include <LiquidCrystal.h>

#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5
#define btnUNKNOWN 6

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



char *button[] ={" Fan             ", " Lamp           ", " Door Lock      ", " Security System", "", "", "??????"};

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup(){
      lcd.begin(16, 2);
      }

void loop(){
      lcd.setCursor(0, 0);
      lcd.print("Select Option:");
      lcd.setCursor(0,1);
      int option=readkeypad();
      switch(option){
        case 0:
          lcd.print(button[option]);
          while(1){
            option=readkeypad();
            if(option==4){
              lcd.setCursor(0,1);
              lcd.print("SELECTED         ");
              option=32;
              delay(1000);
              break;
            }
            }
            if(option==32){
              lcd.setCursor(0,1);
              lcd.print("OPTIONS HERE    ");
            }
          break;
        case 1:
          lcd.print(button[option]);
          break;
        case 2:
          lcd.print(button[option]);
          break;
        case 3:
          lcd.print(button[option]);
          break;
        default :
          lcd.print("");
      }
      
}
      
