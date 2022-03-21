#include <Key.h>
#include<MIDI.h>
#include <Keypad.h>

MIDI_CREATE_DEFAULT_INSTANCE();

/*---- pad ----*/
byte ccPad = 11;
const byte ROWS = 6; 
const byte COLS = 9; 
byte rowPins[ROWS] = {A5, A0, A1, A2, A3, A4}; 
byte colPins[COLS] = {13, 9, 8, 7, 6, 5, 4, 3, 2}; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '4', '5', '6', '7', '8', '9'},
  {':', ';', '<', '=', '>', '?', '@', 'A', 'B'},
  {'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'},
  {'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T'},
  {'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']'},
  {'^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f'}
};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

/*---- pot ----*/
int ccPot = 10;
#define Mux1 A6
#define S0 10
#define S1 11
#define S2 12
#define MaxPots 6
int oldPot[8] = {0};
int chPots[8] = {1, 2, 3, 4, 5, 6, 7, 8};

int sliderFromMap[] = {0, 420, 830, 950, 1020};
int sliderToMap[] = {0, 127};
byte sliderFromMapSize;
byte sliderToMapSize;


void setup(){
  MIDI.begin();
  Serial.begin(9600);
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
}
  
void loop(){
  /*---- Pad ----*/
  pad(ccPad);

  /*---- Pot ----*/
  //Pots_Sliders(ccPot);
}

/*************************************************/
/************ Functions *************************/
void pad(byte cc) {
  char customKey = customKeypad.getKey();
  if(customKey){ 
    MIDI.sendNoteOn((uint8_t)customKey, 127, cc);
    delay(10);
    MIDI.sendNoteOff((uint8_t)customKey, 127, cc);
  }
}
/*
void Pots_Sliders(byte ccPot) {
  for(int i = 0; i < MaxPots; i++)  {
    //for pots
    int tempPot = readMuxChannel(i,Mux1);      //reading from mux value 0-1023
    if(tempPot != oldPot[i])  {                 //if change happens
      oldPot[i] = tempPot;                    //saving the new temp
      
      if(chPots[i] == 5 || chPots[i] == 6) {
        //tempPot = multiMap(oldPot[i], sliderFromMap, sliderFromMapSize, sliderToMap, sliderToMapSize); 
        tempPot = map(oldPot[i], 0, 1000, 0, 127);
      } else {
        tempPot = map(oldPot[i], 0, 1000, 0, 127); //mapping for MIDI
      }
      
      MIDI.sendControlChange(chPots[i], tempPot, ccPot);    //sending mapped value
    }
  }
}
*/
/*
int readMuxChannel(int channel, int MUXpin) {
  //Select mux channel
    digitalWrite(S0, HIGH && (channel & B00000001));
    digitalWrite(S1, HIGH && (channel & B00000010));
    digitalWrite(S2, HIGH && (channel & B00000100));
  //Read mux output
  if( channel == 5 || channel == 4) {
    if(MUXpin == Mux1){return analogRead(MUXpin)/10*10;}
  } else {
    if(MUXpin == Mux1){return analogRead(MUXpin)/50*50;}
  }
    
}
*/
/*
int multiMap(int value, int fromMap[], int fromMapSize, int toMap[], int toMapSize)
{
  //Boundary cases
  if (value <= fromMap[0]) return toMap[0];
  if (value >= fromMap[fromMapSize - 1]) return toMap[toMapSize - 1];

  //Find the fromMap interval that value lies in
  byte fromInterval = 0;
  while (value > fromMap[fromInterval + 1])
    fromInterval++;

  //Find the percentage of the interval that value lies in
  float fromIntervalPercentage = (float)(value - fromMap[fromInterval]) / (fromMap[fromInterval + 1] - fromMap[fromInterval]);

  //Map it to the toMap interval and percentage of that interval
  float toIntervalPercentage = ((fromInterval + fromIntervalPercentage) / (fromMapSize - 1)) * (toMapSize - 1);
  byte toInterval = (byte)toIntervalPercentage;
  toIntervalPercentage = toIntervalPercentage - toInterval;

  //Linear interpolate
  return toMap[toInterval] + toIntervalPercentage * (toMap[toInterval + 1] - toMap[toInterval]);
}
*/
