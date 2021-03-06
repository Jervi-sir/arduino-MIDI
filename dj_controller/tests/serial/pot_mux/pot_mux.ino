int pin_Out_S0 = 2;
int pin_Out_S1 = 3;
int pin_Out_S2 = 4;
int pin_In_Mux1 = A2;
int Mux1_State[8] = {0};

void setup() {
  pinMode(pin_Out_S0, OUTPUT);
  pinMode(pin_Out_S1, OUTPUT);
  pinMode(pin_Out_S2, OUTPUT);
  //pinMode(pin_In_Mux1, INPUT);
  Serial.begin(9600);
}

void loop() {
  updateMux1();
  for(int i = 0; i < 8; i ++) {
    //if(i == 1 || i == 2 || i == 3) {continue;}
    if(i == 7) {
      Serial.println(Mux1_State[i]);
    } else {
      Serial.print(Mux1_State[i]);
      Serial.print("\t");
    }
  }
}

void updateMux1 () {
  for (int i = 0; i < 8; i++){
    digitalWrite(pin_Out_S0, HIGH && (i & B00000001));
    digitalWrite(pin_Out_S1, HIGH && (i & B00000010));
    digitalWrite(pin_Out_S2, HIGH && (i & B00000100));
    Mux1_State[i] = analogRead(pin_In_Mux1);
  }
}
