#include <Servo.h>

Servo myservo;

int pos = 0;

int pin1=12;
int pin2=11;

void setup(){
 pinMode(pin1,OUTPUT);
 pinMode(pin2,OUTPUT);
 myservo.attach(9);
 
  
 }
void loop()
{
  digitalWrite(pin1,HIGH);
  digitalWrite(pin2,LOW);
  for (pos = 0; pos <= 70; pos += 1)
  {
    myservo.write(pos);
    delay(5);
  }
  delay(300);
  for (pos = 70; pos >= 0; pos -= 1)
  {
    myservo.write(pos);
    delay(5);
  }
  delay(300);
}


