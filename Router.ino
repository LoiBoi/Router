//Router
#include <SoftwareSerial.h>

SoftwareSerial XBee(2, 3);

int flexSensorPinF1 = A0; //analog pin 0, first finger
int flexSensorPinF2 = A1; //analog pin 1, middle finger
int flexSensorPinF3 = A2; //analog pin 2, ring finger
int flexSensorPinF4 = A3; //analog pint 3, thumb
int valF1;
int valF2;
int valF3;
int valF4;

int led = 13;
int button = 12;
int buttonRead = LOW;
int count = 0;
char mode = 'd';

void setup()
{ 
  pinMode(button, INPUT); //Used to read the value of the button
  pinMode(led, OUTPUT); //Used to turn the LED on and off
  Serial.begin(9600);
  XBee.begin(9600); 
}

void loop()
{  
  buttonRead = digitalRead(button); 
  if (buttonRead == HIGH) //To keep track of when the button is pressed to swap between modes
  {
  count++;
  count = count%2; 
  }
  
  if (count == 0)
  {
    mode = 'd';
  }
  else if (count == 1)
  {
    mode = 'h';
  }
  
  //LED on when in 'Hand' mode
  if (count == 1)
  {
    digitalWrite(led, HIGH);  
  }
  if (count == 0)
  {
    digitalWrite(led, LOW);  
  }
  
  //Debugging
  //Serial.println(count); //Used too see if the button is working
  
  //Finger 1
  int flexSensorReadingF1 = analogRead(flexSensorPinF1); //Reads the value of the flex sensor 
  valF1 = map(flexSensorReadingF1, 360, 640, 0, 9); //Changes the finger values to a range of 0-9
  if (valF1 > 9) //Keeps values at or under 9 to help the XBee byte reading stay stable
  {
    valF1 = 9;
  }
  if (valF1 < 0) //Keeps values at or above 0 to help the XBee byte reading stay stable
  {
    valF1 = 0;
  }
  
  //Finger 2
  int flexSensorReadingF2 = analogRead(flexSensorPinF2);
  valF2 = map(flexSensorReadingF2, 300, 714, 0, 9);
  if (valF2 > 9)
  {
    valF2 = 9;
  }
  if (valF2 < 0)
  {
    valF2 = 0;
  }

  //Finger 3
  int flexSensorReadingF3 = analogRead(flexSensorPinF3);
  valF3 = map(flexSensorReadingF3, 441, 705, 0, 9);
  if (valF3 > 9)
  {
    valF3 = 9;
  }
  if (valF3 < 0)
  {
    valF3 = 0;
  }

  //Finger 4
  int flexSensorReadingF4 = analogRead(flexSensorPinF4);
  valF4 = map(flexSensorReadingF4, 220, 470, 0, 9);
  if (valF4 > 9)
  {
    valF4 = 9;
  }
  if (valF4 < 0)
  {
    valF4 = 0;
  }
  
  //Sending values
  XBee.print(mode);
  XBee.print(valF1); //First Finger
  XBee.print(valF2); //Middle Finger
  XBee.print(valF3); //Ring Finger
  XBee.print(valF4); //Thumb 
  
  //Debugging from analog readings
  //Serial.println(flexSensorReadingF1);
  //Serial.println(flexSensorReadingF2);
  
  //Debugging after remapping
  //Serial.println(valF1);
  //Serial.println(valF2);
  //Serial.println(valF3);
  //Serial.println(valF4);
  delay(200); 
 }
