/*

ultrasound.ino
Brian Gravelle

example for ultrasonic distance sensor HC-SR04
Datasheet: http://www.micropik.com/PDF/HCSR04.pdf

heavily based on:
http://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/?ALLSTEPS

*/

#include "hcsr04.h"

#define TRIG_PIN 2
#define ECHO_PIN 4

#define FAR_LED  10
#define NEAR_LED 11

hcsr04 usds(TRIG_PIN, ECHO_PIN);

void setup() {
  Serial.begin (9600);
  pinMode(FAR_LED, OUTPUT);
  pinMode(NEAR_LED, OUTPUT);
}


void loop() {
  long distance;
  long threshold = 8;

  Serial.println("reset distance");
  digitalWrite(FAR_LED, HIGH);
  digitalWrite(NEAR_LED, HIGH);
  delay(2000);
  digitalWrite(FAR_LED, LOW);
  digitalWrite(NEAR_LED, LOW);
  delay(2000);

  Serial.println("taking measurement");
  distance = usds.get_inches();
  if(distance > threshold) {
    digitalWrite(FAR_LED, HIGH);
    digitalWrite(NEAR_LED, LOW);
    usds.wait_above_threshold(threshold, true);
    digitalWrite(FAR_LED, LOW);
    digitalWrite(NEAR_LED, HIGH);
    usds.wait_below_threshold(threshold, true);
  } else {
    digitalWrite(FAR_LED, LOW);
    digitalWrite(NEAR_LED, HIGH);
    usds.wait_below_threshold(threshold, true);
    digitalWrite(FAR_LED, HIGH);
    digitalWrite(NEAR_LED, LOW);
    usds.wait_above_threshold(threshold, true);
  } 
  
  delay(500);
}







/*************************** Original Example *************************************/

// /*

// From:
// http://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/?ALLSTEPS

// */

// /*
// HC-SR04 Ping distance sensor]
// VCC to arduino 5v GND to arduino GND
// Echo to Arduino pin 13 Trig to Arduino pin 12
// Red POS to Arduino pin 11
// Green POS to Arduino pin 10
// 560 ohm resistor to both LED NEG and GRD power rail
// More info at: http://goo.gl/kJ8Gl
// Original code improvements to the Ping sketch sourced from Trollmaker.com
// Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
// */

// #define trigPin 3
// #define echoPin 4
// #define led 11
// #define led2 10

// void setup() {
//   Serial.begin (9600);
//   pinMode(trigPin, OUTPUT);
//   pinMode(echoPin, INPUT);
//   pinMode(led, OUTPUT);
//   pinMode(led2, OUTPUT);
// }

// void loop() {
//   long duration, distance;
//   digitalWrite(led,HIGH);
//   digitalWrite(led2,HIGH);
//   digitalWrite(trigPin, LOW);  // Added this line
//   delayMicroseconds(2); // Added this line
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(1000); // Removed this line
//   // delayMicroseconds(10); // Added this line
//   digitalWrite(trigPin, LOW);
//   duration = pulseIn(echoPin, HIGH);
//   distance = (duration/2) / 29.1;
//   if (distance < 4) {  // This is where the LED On/Off happens
//     digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
//   digitalWrite(led2,LOW);
// }
//   else {
//     digitalWrite(led,LOW);
//     digitalWrite(led2,HIGH);
//   }
//   if (distance >= 200 || distance <= 0){
//     Serial.print("Out of range; distance = ");
//     Serial.println(distance);
//   }
//   else {
//     Serial.print(distance);
//     Serial.println(" cm");
//   }
//   delay(500);
// }