#include <IRremote.h> // Includes IR Remote Library

int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {  
    Serial.println(results.value, HEX);
    Serial.println(results.bits);
    if(results.value == 0xC90) //If this code is recieved
    {                          //RUN THIS - PUT CODE TO EXECUTED ON 
                               //SHOT HERE
       digitalWrite(13, HIGH);
       delay(1000);
       digitalWrite(13, LOW);
    }
    irrecv.resume(); //receive the next value
  }
}
