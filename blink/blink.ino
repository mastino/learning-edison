/*

Blink
Super basic example for Intel Edison with arduino

*/

int led = 13;

void setup()  {
  pinMode(led,OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}