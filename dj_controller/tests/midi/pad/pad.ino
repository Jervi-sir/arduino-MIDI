#include <Key.h>
#include<MIDI.h>
#include <Keypad.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', ':', ';', '<'},
  {'=', '>', '?', '@'}
};

byte rowPins[ROWS] = {7, 6, 9, 8}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  MIDI.begin();
  Serial.begin(9600);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  if(customKey){ 
    MIDI.sendNoteOn((uint8_t)customKey, 127,2);
    delay(10);
    MIDI.sendNoteOff((uint8_t)customKey, 127,2);
  }
}
