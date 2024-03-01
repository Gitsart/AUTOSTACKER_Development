void setup() {
  pinMode(15,OUTPUT);
  pinMode(14,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
  pinMode(A10,INPUT_PULLUP);
  pinMode(A11,INPUT_PULLUP);
  Serial.begin(9600);

}


void buzzer() {
  digitalWrite(15,HIGH);
  delay(10000);
  digitalWrite(15,LOW);
  delay(1000);
}

void loop() {


  int sen = digitalRead(A10);
  Serial.print("Sensor");Serial.println(sen);

  int lim = digitalRead(A11);
  Serial.print("LIMIT:");Serial.println(lim);

  
}
