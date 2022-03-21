#include<MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define Mux1 A0
#define Mux2 A1
#define S0 10
#define S1 11
#define S2 12

#define MaxPots 8

int Mux1_State[8] = {0};

int potFromMap[] = {0, 256, 512, 767, 1023}, potToMap[] = {0, 127};
int sliderFromMap[] = {0, 420, 830, 950, 1023}, sliderToMap[] = {0, 127};
byte potFromMapSize, potToMapSize;
byte sliderFromMapSize, sliderToMapSize;
int oldPot[8] = {0}, oldSlide[8] = {0};
int ccPots[8] = {1, 2, 3, 4, 5, 6, 7, 8}, ccSlides[8] = {13, 0, 0, 0, 9, 10, 11, 12};


void setup() {
  MIDI.begin();
  Serial.begin(9600);
 
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  //pinMode(pin_In_Mux1, INPUT);

}

void loop() {
  Pots_Sliders();
  
}

/************ Pots ************/
void Pots_Sliders() {
  for(int i = 0; i < MaxPots; i++)  {
    //for pots
    
    int tempPot = readMuxChannel(i,Mux1);      //reading from mux value 0-1023
    if(tempPot != oldPot[i])  {                 //if change happens
      oldPot[i] = tempPot;                    //saving the new temp
      tempPot = map(oldPot[i], 0, 1020, 0, 127); //mapping for MIDI
      MIDI.sendControlChange(2, tempPot, ccPots[i]);    //sending mapped value
    }
    
    //for sliders
    if(i == 1 || i == 2 || i ==3) {continue;} //to ignore unused mux input
    int tempSlide = readMuxChannel(i,Mux2);
    if(tempSlide != oldSlide[i]) {
      oldSlide[i] = tempSlide;
      tempSlide = map(oldSlide[i], 0, 1020, 0, 127);
      MIDI.sendControlChange(3, tempSlide, ccSlides[i]);
    }
    
  }
}

/************ readMuxChannel ************/
int readMuxChannel(int channel, int MUXpin) {
  //Select mux channel
    digitalWrite(S0, HIGH && (channel & B00000001));
    digitalWrite(S1, HIGH && (channel & B00000010));
    digitalWrite(S2, HIGH && (channel & B00000100));
  //Read mux output
    if(MUXpin == Mux1){return analogRead(MUXpin)/10*10;}
    if(MUXpin == Mux2){return analogRead(MUXpin)/10*10;}
}
