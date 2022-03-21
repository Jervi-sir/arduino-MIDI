#include<MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define outputA1 A5
#define outputB1 A4

#define outputA2 A3
#define outputB2 A2

int lastJog1, lastJog2;
 
void setup() {
  MIDI.begin();
  pinMode (outputA1,INPUT);
  pinMode (outputB1,INPUT);
  pinMode (outputA2,INPUT);
  pinMode (outputB2,INPUT);
  Serial.begin (9600);
  
  // Reads the initial state of the outputA
  lastJog1 = digitalRead(outputA1);
  lastJog2 = digitalRead(outputA2);
 
}
 
void loop() {
  lastJog1 = jog(1, 1, outputA1, outputB1, lastJog1);
  lastJog2 = jog(1, 2, outputA2, outputB2, lastJog2);
  
}

int jog(byte cc, byte ch, int outA, int outB, int lastState) {
  int aState = digitalRead(outA); 
    if (aState != lastState)
    {
      if (digitalRead(outB) != aState) { MIDI.sendControlChange(cc, 65, ch);} 
      else { MIDI.sendControlChange(cc, 63, ch); }
    }
  return aState; 
}
