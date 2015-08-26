



#include <IRremote.h>
IRsend irsend;

const int buttonPin = 2;
const int INTERVAL = 500; //Millisecond interval between shots fired

unsigned long timeClicked = 0;
int buttonState = 0;  

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && timeClicked + INTERVAL < millis()) {    
    Serial.println("hey");
    irsend.sendSony(0xC90, 12); // Sent code 0xC90
    timeClicked = millis();
  }
}
