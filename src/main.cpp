#include <Arduino.h>
#include "math.h"
const int PinA = 26;
const int PinB = 27;
const int PinSW = 14;

int lastCount = 50;
volatile int virtualPosition = 50;

void isr(){

    static unsigned long lastInterruptTime = 0;
    unsigned long interruptTime = millis();

    if(interruptTime - lastInterruptTime > 5){
      
      if(digitalRead(PinB) == LOW) { virtualPosition--;}
      else { virtualPosition++;}

      virtualPosition = min(100, max(0, (int)virtualPosition));
      lastInterruptTime = interruptTime;
    }
}
// put function declarations here:


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PinA, INPUT);
  pinMode(PinB, INPUT);

  pinMode(PinSW, INPUT_PULLUP);

  Serial.println(digitalRead(PinA));
  Serial.println(digitalRead(PinB));
  Serial.println(digitalRead(PinSW));

  attachInterrupt(digitalPinToInterrupt(PinA), isr, HIGH);

  Serial.println("Start");
  
}

void loop() {
  // put your main code here, to run repeatedly:
if ((!digitalRead(PinSW))) {
    virtualPosition = 0;
    while (!digitalRead(PinSW))
      delay(10);
    Serial.println("Reset");
  }

  // If the current rotary switch position has changed then update everything
  if (virtualPosition != lastCount) {

    // Write out to serial monitor the value and direction
    Serial.print(virtualPosition > lastCount ? "Up  :" : "Down:");
    Serial.println(virtualPosition);
    
    // Keep track of this new value
    lastCount = virtualPosition ;
  }

}

// put function definitions here:
