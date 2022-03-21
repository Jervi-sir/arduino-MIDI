#include <Key.h>

#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'a', 'b', 'c', 'd'},
  {'e', 'f', 'g', 'h'},

};

byte rowPins[ROWS] = {7, 6, 9, 8}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

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


  
int ChartoInt (char number){

  for(int i = 0; i < ROWS;i++){
    for(int j = 0; j < COLS; j++){
      if(hexaKeys[i][j] == number) { return (((i+1)*COLS)-(COLS-j+1));  }
    }
  }
}
