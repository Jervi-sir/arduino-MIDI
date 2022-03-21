
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int T1 = analogRead(A7);
  int T2 = analogRead(A6);
  int T3 = analogRead(A5);

  
  // print out the value you read:
  Serial.print(T1);
  Serial.print('\t');
  Serial.print(T2);
  Serial.print('\t');

  Serial.println(T3);
  
  delay(1);        // delay in between reads for stability
}
