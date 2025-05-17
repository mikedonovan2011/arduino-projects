#include "IRremote.h"

#define frontleft1 12
#define frontleft2 13
#define frontright1 43
#define frontright2 45
#define backleft1 11
#define backleft2 10
#define backright1 39
#define backright2 41

int receiver = A1; // Signal Pin of IR receiver to Arduino Digital Pin 11

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void setup() {
  pinMode(frontleft1, OUTPUT);
  pinMode(frontleft2, OUTPUT);
  pinMode(frontright1, OUTPUT);
  pinMode(frontright2, OUTPUT);
  pinMode(backleft1, OUTPUT);
  pinMode(backleft2, OUTPUT);
  pinMode(backright1, OUTPUT);
  pinMode(backright2, OUTPUT);

  //pinMode(receiver, INPUT);

  Serial.begin(9600);
  //Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
}

void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{
  switch(results.value)
  {
  case 0xFFA25D: 
  {
    //Serial.println("POWER"); 
    break;
  }
  case 0xFFE21D: 
  {
    //Serial.println("FUNC/STOP"); 
    break;
  }
  case 0xFF629D: 
  {
    //Serial.println("VOL+");
    moveForward(1000);
    break;
  }
  case 0xFF22DD:
  {
    //Serial.println("FAST BACK");
    turnLeft(1000);
    break;
  }
  case 0xFF02FD: 
  {
    //Serial.println("PAUSE");
    moveForward(1000);
    break;
  }
  case 0xFFC23D: 
  {
    //Serial.println("FAST FORWARD");
    turnRight(1000);
    break;
  }
  
  case 0xFFE01F: 
  {
    //Serial.println("DOWN");
    turnLeft(1000);
    break;
  }
  case 0xFFA857: 
  {
    //Serial.println("VOL-");
    moveBackward(1000);
    break;
  }
  case 0xFF906F: 
  {
    //Serial.println("UP");
    turnRight(1000);
    break;
  }
 
  case 0xFF9867: 
  {
    //Serial.println("EQ");
    moveBackward(1000);
    break;
  }
  case 0xFFB04F: 
  {
    //Serial.println("ST/REPT");    
    break;
  }
  case 0xFF6897: 
  {
    //Serial.println("0");    
    break;
  }
  case 0xFF30CF: 
  {
    //Serial.println("1");    
    break;
  }
  case 0xFF18E7: 
  {
    //Serial.println("2");
    moveForward(500);
    break;
  }
  case 0xFF7A85: 
  {
    //Serial.println("3");    
    break;
  }
  case 0xFF10EF: 
  {
    //Serial.println("4");
    turnLeft(500);
    break;
  }
  
  case 0xFF38C7: 
  {
    //Serial.println("5");    
    break;
  }
  case 0xFF5AA5: 
  {
    //Serial.println("6");
    turnRight(500);
    break;
  }
  case 0xFF42BD: 
  {
    //Serial.println("7");    
    break;
  }
  case 0xFF4AB5: 
  {
    //Serial.println("8");
    moveBackward(500);
    break;
  }
  case 0xFF52AD: 
  {
    //Serial.println("9");    
    break;
  }
  case 0xFFFFFFFF: 
  {
    //Serial.println(" REPEAT");
    break;
  }

  default: 
  {
    break;
  }


  }// End Case

  //delay(500); // Do not get immediate repeat


} //END translateIR

void turnWheels(int fl1, int fl2, int fr1, int fr2, int bl1, int bl2, int br1, int br2)
{
  digitalWrite(frontleft1, fl1);
  digitalWrite(frontleft2, fl2);
  
  digitalWrite(frontright1, fr1);
  digitalWrite(frontright2, fr2);
  
  digitalWrite(backleft1, bl1);
  digitalWrite(backleft2, bl2);
  
  digitalWrite(backright1, br1);
  digitalWrite(backright2, br2);
}

void stopWheels()
{
  turnWheels(0, 0, 0, 0, 0, 0, 0, 0);
  delay(300);
}

void moveForward(int timeMoving)
{
  turnWheels(0, 1, 0, 1, 0, 1, 0, 1);
  delay(timeMoving);
}

void moveBackward(int timeMoving)
{
  turnWheels(1, 0, 1, 0, 1, 0, 1, 0);
  delay(timeMoving);
}

void turnRight(int timeMoving)
{
  turnWheels(0, 1, 1, 0, 0, 1, 1, 0);
  delay(timeMoving);
}

void turnLeft(int timeMoving)
{
  turnWheels(1, 0, 0, 1, 1, 0, 0, 1);
  delay(timeMoving);
}

void loop() {

    if (irrecv.decode(&results)) // have we received an IR signal?
    {
      translateIR(); 
      irrecv.resume(); // receive the next value
    } 
    else
    {
      stopWheels();
    }
    
}
