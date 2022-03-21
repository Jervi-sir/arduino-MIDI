#include<MIDI.h>
#include <Keypad.h>

MIDI_CREATE_DEFAULT_INSTANCE();

/*---- Jog ----*/
byte ccJog11 = 1, ccJog12 = 2;
byte ccJog21 = 3, ccJog22 = 4;
#define outputA1 A5
#define outputB1 A4
#define outputA2 A3
#define outputB2 A2
int lastJog1, lastJog2;
int left = 64, right = 0;

/*---- Pad ----*/
byte ccPad = 5;
const byte ROWS = 4; 
const byte COLS = 4; 
byte rowPins[ROWS] = {7, 6, 9, 8}; 
byte colPins[COLS] = {5, 4, 3, 2}; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', ':', ';', '<'},
  {'=', '>', '?', '@'}
};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

/*---- Pot ----*/
int ccPot = 6, ccSlide = 7;
#define Mux1 A0
#define Mux2 A1
#define S0 10
#define S1 11
#define S2 12
#define MaxPots     8
int oldPot[8] = {0}, oldSlide[8] = {0};
int chPots[8] = {8, 9, 10, 11, 12, 13, 14, 15}, chSlides[8] = {16, 0, 0, 0, 17, 18, 19, 20};

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
  Pots_Sliders(ccPot, ccSlide);
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

void Pots_Sliders(byte ccPot, byte ccSlide) {
  for(int i = 0; i < 8; i++)  {
    //for pots
    int tempPot = readMuxChannel(i,Mux1);      //reading from mux value 0-1023
    if(tempPot != oldPot[i])  {                 //if change happens
      oldPot[i] = tempPot;                    //saving the new temp
      tempPot = map(oldPot[i], 0, 1020, 0, 127); //mapping for MIDI
      MIDI.sendControlChange(chPots[i], tempPot, ccPot);    //sending mapped value
    }
    
    //for sliders
    if(i == 1 || i == 2 || i ==3) {continue;} //to ignore unused mux input
    int tempSlide = readMuxChannel(i,Mux2);
    if(tempSlide != oldSlide[i]) {
      oldSlide[i] = tempSlide;
      tempSlide = map(oldSlide[i], 0, 1000, 0, 127);
      
      
      MIDI.sendControlChange(chSlides[i], tempSlide, ccSlide);
    }
  }
}

int readMuxChannel(int channel, int MUXpin) {
  //Select mux channel
    digitalWrite(S0, HIGH && (channel & B00000001));
    digitalWrite(S1, HIGH && (channel & B00000010));
    digitalWrite(S2, HIGH && (channel & B00000100));
  //Read mux output
    if(MUXpin == Mux1){return analogRead(MUXpin)/20*20;}
    if(MUXpin == Mux2){return analogRead(MUXpin)/50*50;}
}
