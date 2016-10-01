#include <IRremote.h> // Includes IR Remote Library
#include <Servo.h> 
 
Servo myservo;

int RECV_PIN = 2;

int pos = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(13, OUTPUT);
  myservo.attach(9);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  myservo.write(90);
}

void loop() {
  if (irrecv.decode(&results)) {  
    Serial.println(results.value, HEX);
    Serial.println(results.bits);
    if(results.value == 0x1B197C96) //If this code is recieved
    {                          //RUN THIS - PUT CODE TO EXECUTED ON 
                               //SHOT HERE
       digitalWrite(13, HIGH);
       myservo.write(0);
       delay(350);
       myservo.write(50);
       delay(70);
       myservo.write(55);
       delay(70);
       myservo.write(60);
       delay(70);
       myservo.write(70);
       delay(70);
       myservo.write(80);
       delay(50);
       myservo.write(81);
       delay(100);
       myservo.write(82);
       delay(100);
       myservo.write(83);
       delay(100);
       myservo.write(84);
       delay(100);
       myservo.write(85);
       delay(100);
       myservo.write(86);
       delay(200);
       myservo.write(87);
       delay(300);
       myservo.write(88);
       delay(300);
       myservo.write(89);
       delay(500);
       myservo.write(90);
       digitalWrite(13, LOW);
    }
    irrecv.resume(); //receive the next value
  }
}
