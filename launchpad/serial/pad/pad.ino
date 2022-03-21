#include <Keypad.h>

const byte ROWS = 6; 
const byte COLS = 9; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '4', '5', '6', '7', '8', '9'},
  {':', ';', '<', '=', '>', '?', '@', 'A', 'B'},
  {'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'},
  {'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T'},
  {'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']'},
  {'^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f'}

};

byte rowPins[ROWS] = {A5, A0, A1, A2, A3, A4}; 
byte colPins[COLS] = {13, 9, 8, 7, 6, 5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  if(customKey){
       
    Serial.println((uint8_t)customKey);
  }

}
