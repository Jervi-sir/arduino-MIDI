/*-----------
 * S0: 2
 * S1: 3
 * S2: 4
 * Jog1: 5, 6
 * Jog2: 7, 8
 * Pad: 9, 10, 11, 12, A0, A1, A2, A3
 * Sliders: A5, A6, A7
 * Pots Mux: A4
 */

#include<MIDI.h>
#include <Keypad.h>

MIDI_CREATE_DEFAULT_INSTANCE();

/*---- Jog ----*/
byte ccJog11 = 1, ccJog12 = 2;
byte ccJog21 = 3, ccJog22 = 4;
#define outputA1 5
#define outputB1 6
#define outputA2 8
#define outputB2 7
int lastJog1, lastJog2;
int left = 64, right = 0;

/*---- Pad ----*/
byte ccPad = 5;
const byte ROWS = 4; 
const byte COLS = 4; 
byte rowPins[ROWS] = {12, 11, 10, 9}; 
byte colPins[COLS] = {A3, A2, A1, A0}; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', ':', ';', '<'},
  {'=', '>', '?', '@'}
};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

/*---- Pot ----*/
int ccPot = 6;
#define Mux1 A4
#define S0 2
#define S1 3
#define S2 4
#define MaxPots     8
int oldPot[8] = {0};
int chPots[8] = {8, 9, 10, 11, 12, 13, 14, 15};

/*---- Sliders -------*/
int ccSlide = 7;
byte slidePin[3] = {A7, A6, A5}; 
int oldSlide[3] = {0};
int chSlides[3] = {5, 6, 7};

void setup() {
  MIDI.begin();
  Serial.begin (9600);
  
  /*---- Jog ----*/
  pinMode (outputA1,INPUT);
  pinMode (outputB1,INPUT);
  pinMode (outputA2,INPUT);
  pinMode (outputB2,INPUT);
  lastJog1 = digitalRead(outputA1);
  lastJog2 = digitalRead(outputA2);

  /*---- Pad ----*/

  /*---- Pot ----*/
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
 
}
 
void loop() {
  /*---- Jog ----*/
  lastJog1 = jog(ccJog11, ccJog12, 1, outputA1, outputB1, lastJog1);
  lastJog2 = jog(ccJog21, ccJog22, 1, outputA2, outputB2, lastJog2);

  /*---- Pad ----*/
  pad(ccPad);

  /*---- Pot ----*/
  Pots(ccPot);

  Sliders();
}

/**************************************************************/
/*************** FUNCTIONS ************************************/
int jog(byte ccLeft, byte ccRight, byte ch, int outA, int outB, int lastState) {
  int aState = digitalRead(outA); 
    if (aState != lastState)
    {
      if (digitalRead(outB) != aState) { 
        MIDI.sendControlChange(ch, 66, ccRight);
      } 
      else {  
        MIDI.sendControlChange(ch, 66, ccLeft); 
      }
    }
  return aState; 
}

void pad(byte cc) {
  char customKey = customKeypad.getKey();
  if(customKey){ 
    MIDI.sendNoteOn((uint8_t)customKey, 127, cc);
    delay(10);
    MIDI.sendNoteOff((uint8_t)customKey, 127, cc);
  }
}

void Pots(byte ccPot) {
  for(int i = 0; i < 8; i++)  {
    //for pots
    int tempPot = readMuxChannel(i,Mux1);      //reading from mux value 0-1023
    if(tempPot != oldPot[i])  {                 //if change happens
      oldPot[i] = tempPot;                    //saving the new temp
      tempPot = map(oldPot[i], 0, 1020, 0, 127); //mapping for MIDI
      MIDI.sendControlChange(chPots[i], tempPot, ccPot);    //sending mapped value
    }
  }
}

void Sliders() {
  for(int i = 0; i < 3; i++) {
    int temp = analogRead(slidePin[i]) / 20 * 20;
    if(temp != oldSlide[i]) {
      oldSlide[i] = temp;
      temp = map(oldSlide[i], 0, 1020, 0, 127);
      MIDI.sendControlChange(chSlides[i], temp, ccSlide);
    }
  }
  
}

int readMuxChannel(int channel, int MUXpin) {
  //Select mux channel
    digitalWrite(S0, HIGH && (channel & B00000001));
    digitalWrite(S1, HIGH && (channel & B00000010));
    digitalWrite(S2, HIGH && (channel & B00000100));
  //Read mux output
    return analogRead(MUXpin) / 20 * 20;

}
