/*

ultrasound.ino
Brian Gravelle

example for ultrasonic distance sensor HC-SR04
Datasheet: http://www.micropik.com/PDF/HCSR04.pdf

heavily based on:
http://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/?ALLSTEPS

*/

#include "hcsr04.h"

#define TRIG_PIN 13
#define ECHO_PIN 12

#define FAR_LED  10
#define NEAR_LED 11

hcsr04 usds(TRIG_PIN, ECHO_PIN);

void setup() {
  Serial.begin (9600);
  pinMode(FAR_LED, OUTPUT);
  pinMode(NEAR_LED, OUTPUT);
}

void loop() {
  long distance = usds.get_inches();
  double threshold = 8.5;

  if(distance > threshold) {
    usds.wait_above_threshold(threshold, true);
    digitalWrite(FAR_LED, HIGH);
    digitalWrite(NEAR_LED, LOW);
    usds.wait_below_threshold(threshold, true);
    digitalWrite(FAR_LED, LOW);
    digitalWrite(NEAR_LED, HIGH);
  } else {
    usds.wait_below_threshold(threshold, true);
    digitalWrite(FAR_LED, LOW);
    digitalWrite(NEAR_LED, HIGH);
    usds.wait_above_threshold(threshold, true);
    digitalWrite(FAR_LED, HIGH);
    digitalWrite(NEAR_LED, LOW);
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