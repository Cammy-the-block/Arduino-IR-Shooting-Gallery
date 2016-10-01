//
//
// NOTE: This requires a modified version of IR Remote (https://github.com/etix/Arduino-IRremote ) forked by Github User etix.
//
//
//


#include <IRremote.h> 
#include <Servo.h> 
 
Servo myservo_left;
Servo myservo_center;
Servo myservo_right;

int RECV_PIN_left = 2;
int RECV_PIN_center = 3;
int RECV_PIN_right = 4;

int pos_left = 0;
int pos_center = 0;
int pos_right = 0;

int startPos_left = 80;
int startPos_center = 180;
int startPos_right = 180;

int endPos_left = 170;
int endPos_center = 110;
int endPos_right = 110;

long long lastShot = 0;

IRrecv irrecv_left(RECV_PIN_left);
IRrecv irrecv_center(RECV_PIN_center);
IRrecv irrecv_right(RECV_PIN_right);

decode_results results;

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
  irrecv_left.enableIRIn(); // Start the receiver
  irrecv_center.enableIRIn();
  irrecv_right.enableIRIn();
  
  myservo_left.attach(9);
  myservo_center.attach(10);
  myservo_right.attach(11);
 
  myservo_left.write(startPos_left);
  myservo_center.write(startPos_center);
  myservo_right.write(startPos_right);
  
}

void loop() {
  if (irrecv_left.decode(&results)) {  
    Serial.println(results.value, HEX);
    Serial.println(results.bits);
    if(results.value == 0x1B197C96  && lastShot + 250 < millis()) //If this code is recieved
    {                          //RUN THIS - PUT CODE TO EXECUTED ON 
                               //SHOT HERE
       activateBottle();
       digitalWrite(13, HIGH); 
    }
    irrecv_left.resume(); //receive the next 0x1B197C96 
  }
  delay(12);
  if (irrecv_center.decode(&results)) {  
    Serial.println(results.value, HEX);
    Serial.println(results.bits);
    if(results.value == 0x1B197C96  && lastShot + 250 < millis()) //If this code is recieved
    {                          //RUN THIS - PUT CODE TO EXECUTED ON 
                               //SHOT HERE
       digitalWrite(13, HIGH); 
       activateBottle();
    }
    irrecv_center.resume(); //receive the next 0x1B197C96 
  }
  delay(12);
  if (irrecv_right.decode(&results)) {  
    Serial.println(results.value, HEX);
    Serial.println(results.bits);
    if(results.value == 0x1B197C96  && lastShot + 250 < millis()) //If this code is recieved
    {                          //RUN THIS - PUT CODE TO EXECUTED ON 
                               //SHOT HERE
       digitalWrite(13, HIGH); 
       activateBottle();
    }
    irrecv_right.resume(); //receive the next 0x1B197C96 
  }
  
  if (pos_left == endPos_left & pos_center == endPos_center && pos_right == endPos_right){
    delay(3000);   
    for(int pos = 0; pos<=100; pos+=1)     // goes from 180 degrees to 0 degrees 
      {   
        pos_left = map(pos, 0, 100, endPos_left, startPos_left);
        myservo_left.write(pos_left);      
        pos_center = map(pos, 0, 100, endPos_center, startPos_center);
        myservo_center.write(pos_center);
        pos_right = map(pos, 0, 100, endPos_right, startPos_right);
        myservo_right.write(pos_right);
        
        delay(8);                       // waits 15ms for the servo to reach the position 
      } 
    lastShot = millis();
    digitalWrite(13, LOW);
  }
  
  if(lastShot + 15000 < millis()){
    Serial.println("heyyyy");
    boolean resetLeft = false;
    boolean resetCenter = false;
    boolean resetRight = false;
    
    if (pos_left == endPos_left){
      resetLeft = true;
    }
    if (pos_center == endPos_center){
      resetCenter = true;
    }
    if (pos_right == endPos_right){
      resetRight = true;
    }
    
    if(resetLeft || resetCenter || resetRight){
      for(int pos = 0; pos<=100; pos+=1)     // goes from 180 degrees to 0 degrees 
      {   
        if(resetLeft){
          pos_left = map(pos, 0, 100, endPos_left, startPos_left);
          myservo_left.write(pos_left);      
        }
        if(resetCenter){
          pos_center = map(pos, 0, 100, endPos_center, startPos_center);
          myservo_center.write(pos_center);
        }
        if(resetRight){
          pos_right = map(pos, 0, 100, endPos_right, startPos_right);
          myservo_right.write(pos_right);
        }
        delay(8);                       // waits 15ms for the servo to reach the position 
      } 
    }
    lastShot = millis();
  }
   Serial.println(millis() % 8000);
  delay(12);
}

void activateBottle(){
  Serial.println("howdy");
  boolean bottleActivated = false;
  int bottle = random(0,3);
  if (bottle == 0 && pos_left != endPos_left){
    for(pos_left = startPos_left; pos_left < endPos_left; pos_left += 1) // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo_left.write(pos_left);              // tell servo to go to position in variable 'pos' 
      delay(1);                       // waits 15ms for the servo to reach the position 
    } 
        
    lastShot = millis();  
    bottleActivated = true;
  }
  else if (bottle == 1 && pos_center != endPos_center){
    for(pos_center = startPos_center; pos_center > endPos_center; pos_center -= 1) // goes from 0 degrees to 180 degrees 
        {                                  // in steps of 1 degree 
          myservo_center.write(pos_center);              // tell servo to go to position in variable 'pos' 
          delay(1);                       // waits 15ms for the servo to reach the position 
        } 
        
        lastShot = millis();
        bottleActivated = true;
  }
  else if (bottle == 2 && pos_right != endPos_right){
    
       for(pos_right = startPos_right; pos_right > endPos_right; pos_right -= 1) // goes from 0 degrees to 180 degrees 
        {                                  // in steps of 1 degree 
          myservo_right.write(pos_right);              // tell servo to go to position in variable 'pos' 
          delay(1);                       // waits 15ms for the servo to reach the position 
        } 
        
        lastShot = millis();
        bottleActivated = true;
  }
  if (!bottleActivated){
    activateBottle();
  }
}
