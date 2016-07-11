/*

hcsr04.cpp
Brian Gravelle
gravelle@cs.uoregon.edu

July 2016

library for ultrasonic distance sensor HC-SR04
Datasheet: http://www.micropik.com/PDF/HCSR04.pdf

heavily based on:
http://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/?ALLSTEPS


*/


#include "hcsr04.h"

hcsr04::hcsr04(int new_trig_pin, int new_echo_pin){
  trig_pin = new_trig_pin;
  echo_pin = new_echo_pin;
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  cm_div  = CM_DIV;
  in_div  = IN_DIV;
  pulse_T = PULSE_T;
}

long hcsr04::take_measurement(){
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  pulse_width = pulseIn(echo_pin, HIGH);

  return pulse_width;
}

void hcsr04::get_measurement(long &out_measurement){
  out_measurement = pulse_width;
}

long hcsr04::get_measurement(){
  return pulse_width;
}

long hcsr04::get_inches(){
  long distance;
  take_measurement();
  distance = pulse_width / in_div;
  return distance;
}

long hcsr04::get_cmeters(){
  long distance;
  take_measurement();
  distance = pulse_width / cm_div;
  return distance;
}

bool hcsr04::wait_above_threshold(long threshold, bool is_inches){
  long thresh;
  if(is_inches)
    thresh = threshold * in_div;
  else
    thresh = threshold * cm_div;
  
  while(take_measurement() > thresh)
    delay(pulse_T);

  return true;
}

bool hcsr04::wait_below_threshold(long threshold, bool is_inches){
  long thresh;
  if(is_inches)
    thresh = threshold * in_div;
  else
    thresh = threshold * cm_div;
  
  while(take_measurement() < thresh)
    delay(pulse_T);

  return true;
}

void hcsr04::set_pins(int new_trig_pin, int new_echo_pin){
  trig_pin = new_trig_pin;
  echo_pin = new_echo_pin;
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

void hcsr04::set_cm_div(long new_cm_div){
  cm_div = new_cm_div;
}

void hcsr04::set_in_div(long new_in_div){
  in_div = new_in_div;
}

void hcsr04::set_pulse_T(int new_pulse_T){
  pulse_T = new_pulse_T;
}

void hcsr04::get_cm_div(long &out_cm_div){
  out_cm_div = cm_div;
}

void hcsr04::get_in_div(long &out_in_div){
  out_in_div = in_div;
}

long hcsr04::get_cm_div(){
  return cm_div;
}

long hcsr04::get_in_div(){
  return in_div;
}

void hcsr04::get_pulse_T(int &out_pulse_T){
  out_pulse_T = pulse_T;
}

int hcsr04::get_pulse_T(){
  return pulse_T;
}