/*

hcsr04.h
Brian Gravelle
gravelle@cs.uoregon.edu

July 2016

library for ultrasonic distance sensor HC-SR04
Datasheet: http://www.micropik.com/PDF/HCSR04.pdf

heavily based on:
http://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/?ALLSTEPS

*/

#ifndef HCSR04_H
#define HCSR04_H

#include "Arduino.h"

//defaults
#define CM_DIV   58   
#define IN_DIV   148  
#define PULSE_T  500  // in millis sec

class hcsr04
{
public:
  hcsr04(int new_trig_pin, int new_echo_pin);
  //~hcsr04();

  long   take_measurement();
  void   get_measurement(long &out_measurement);
  long   get_measurement();
  double get_inches();
  double get_cmeters();
  bool   wait_above_threshold(double threshold, bool is_inches);
  bool   wait_below_threshold(double threshold, bool is_inches);

  void   set_pins(int new_trig_pin, int new_echo_pin);
  void   set_cm_div(double new_cm_div);
  void   set_in_div(double new_in_div);
  void   set_pulse_T(int new_pulse_T);
  void   get_cm_div(double &out_cm_div);
  double get_cm_div();
  void   get_in_div(double &out_in_div);
  double get_in_div();
  void   get_pulse_T(int &out_pulse_T);
  int    get_pulse_T();

private:
  int    trig_pin, echo_pin; // pins
  double cm_div, in_div;     // divisors to get real units
  int    pulse_T;            // period for measurements
  //double max_dist;           // maximum distance

  long pulse_width; // result of measurement
};


#endif