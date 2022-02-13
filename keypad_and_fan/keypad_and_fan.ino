
// Feb 5, 2022: Mike Donovan - keypad turning on a dc motor for some number of seconds.
// 2016.12.9 - www.elegoo.com
// Alexander Brevig, alexanderbrevig@gmail.com - alexanderbrevig@gmail.com

#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

String input_password;
const String password = "7"; // change your password here
const int delayTime = 5; // How many seconds to keep the fan on when the password is correct

#define ENABLE 12
#define DIRA 10
#define DIRB 11

void setup(){
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);

  // set the fan up to turn but disable it
  digitalWrite(ENABLE,LOW);
  digitalWrite(DIRA,HIGH);
  digitalWrite(DIRB,LOW);
}
  
void loop(){
  digitalWrite(ENABLE,LOW);
  char key = keypad.getKey();

  if (key){
    Serial.println(key);

    if(key == '*') {
      input_password = ""; // clear input password
    } else if(key == '#') {
      if(password == input_password) {
        Serial.println("password is correct");
        digitalWrite(ENABLE,HIGH);
        Serial.println("Fan on");

        int i;
        
        Serial.println(delayTime);
        for (i=delayTime; i>0; i--) {
          delay(1000);
          Serial.println(i-1);
        }
        digitalWrite(ENABLE,LOW);
        Serial.println("Fan off");
        
      } else {
        Serial.println("password is incorrect, try again");
      }

      input_password = ""; // clear input password
      
    } else {
      input_password += key; // append new character to input password string
    }
  }
}
