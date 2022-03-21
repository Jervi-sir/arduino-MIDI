#define outputA 8
#define outputB 7
 
int counter = 0;
int aState;
int aLastState;
 
void setup() {
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
   
  Serial.begin (9600);
  
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);
 
}
 
void loop() {
aState = digitalRead(outputA); 
  if (aState != aLastState)
  {
    if (digitalRead(outputB) != aState) {
    counter ++;
  } 
  else 
  {
    counter --;
  }
  Serial.print("Position: ");
  Serial.println(counter);
 
}
aLastState = aState; // Updates the previous state of the outputA with the current state
 
}
