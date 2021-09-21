/*
author: Wanderson Hermirio dos Santos
describe: programa para clonar codigo dos controle
version: 0.1
*/

#include <IRremote.h>

int IRpin = 13;
int pinLed = 12;
IRrecv irrecv(IRpin);
decode_results results;
int statusLed = 0;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(pinLed, OUTPUT);
}

void loop() 
{
  if (irrecv.decode(&results)) 
    {
      Serial.println(results.value); // Print the Serial 'results.value'
      irrecv.resume();   // Receive the next value
      if(results.value == 16751205)
      {
        statusLed = 1-statusLed;
        digitalWrite(pinLed,statusLed);
      }
      
    }
  
  
}
