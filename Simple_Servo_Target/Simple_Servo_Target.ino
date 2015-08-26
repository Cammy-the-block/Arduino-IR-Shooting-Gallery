#include <IRremote.h> // Includes IR Remote Library
#include <Servo.h> 
 
Servo myservo;

int RECV_PIN = 2;
int pos = 0;
int startpos = 93;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  myservo.attach(9);
  myservo.write(startpos);
}

void loop() {
  if (irrecv.decode(&results)) {  
    Serial.println(results.value, HEX);
    Serial.println(results.bits);
    if(results.value == 0xC90) //If this code is recieved
    {                          //RUN THIS - PUT CODE TO EXECUTED ON 
                               //SHOT HERE
       digitalWrite(13, HIGH); 
       
       for(pos = startpos; pos >= 0; pos -= 1) // goes from 0 degrees to 180 degrees 
        {                                  // in steps of 1 degree 
          myservo.write(pos);              // tell servo to go to position in variable 'pos' 
          delay(5);                       // waits 15ms for the servo to reach the position 
        } 
        delay(2000);   
        for(pos = 0; pos<=startpos; pos+=1)     // goes from 180 degrees to 0 degrees 
        {                                
          myservo.write(pos);              // tell servo to go to position in variable 'pos' 
          delay(10);                       // waits 15ms for the servo to reach the position 
        } 
        
        digitalWrite(13, LOW);
    }
    irrecv.resume(); //receive the next value
  }
}
