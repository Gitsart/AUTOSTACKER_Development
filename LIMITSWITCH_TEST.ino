void setup() {
  pinMode(14,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(A11,INPUT_PULLUP);
  pinMode(A10,INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  
  


  int a = digitalRead(9);
  Serial.print("EMG");Serial.println(a);
  int b = digitalRead(14);
  Serial.print("PB");Serial.println(b);

  int sen = digitalRead(A10);
  Serial.print("Sensor");Serial.println(sen);
  int limit = digitalRead(A11);
  Serial.print("LIMIT=");Serial.println(limit);
}
