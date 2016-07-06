/*

ultrasound.ino
Brian Gravelle

library for ultrasonic distance sensor HC-SR04
Datasheet: http://www.micropik.com/PDF/HCSR04.pdf

heavily based on:
http://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/?ALLSTEPS

*/


#define TRIG_PIN 13
#define ECHO_PIN 12
#define CM_DIV   58   // divisor to get cm
#define IN_DIV   148  // divisor to get inches
#define PULSE_T  500  // period for measurements

#define FAR_LED  11
#define NEAR_LED 10

void distance_init(int trig_pin, int echo_pin){
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}



void setup() {
  Serial.begin (9600);
  distance_init(TRIG_PIN, ECHO_PIN);
  pinMode(FAR_LED, OUTPUT);
  pinMode(NEAR_LED, OUTPUT);
}

void loop() {
  unsigned long duration, distance;
  digitalWrite(TRIG_PIN, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 4) {  // This is where the LED On/Off happens
    digitalWrite(FAR_LED,HIGH); // When the Red condition is met, the Green LED should turn off
    digitalWrite(NEAR_LED,LOW);
  }
  else {
    digitalWrite(FAR_LED,LOW);
    digitalWrite(NEAR_LED,HIGH);
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}