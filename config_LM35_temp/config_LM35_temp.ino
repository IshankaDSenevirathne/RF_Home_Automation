float val;
int tempPin = A4;

void setup()
{
Serial.begin(9600);
}
void loop()
{
val = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
float cel = mv/10;

//Serial.print("TEMPRATURE = ");
Serial.print(mv);
//Serial.print("*C");
Serial.println();
delay(100);
}
