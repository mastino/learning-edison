/*

ultrasound.ino
Brian Gravelle

example for ultrasonic distance sensor HC-SR04
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

void USDS_init(int trig_pin, int echo_pin){
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

 long USDS_take_measurement(){
  unsigned long pulse_width;

  digitalWrite(TRIG_PIN, LOW);
  // delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  // delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  pulse_width = pulseIn(ECHO_PIN, HIGH);

  return pulse_width;
}

double USDS_get_inches(long pulse_width){
   double distance;
  distance = ( double)pulse_width / IN_DIV;
  return distance;
}

double USDS_get_cmeters(long pulse_width){
   double distance;
  distance = (double)pulse_width / CM_DIV;
  return distance;
}

void setup() {
  Serial.begin (9600);
  USDS_init(TRIG_PIN, ECHO_PIN);
  pinMode(FAR_LED, OUTPUT);
  pinMode(NEAR_LED, OUTPUT);
}

void loop() {
  unsigned long duration, distance;
  duration = USDS_take_measurement();
  distance = USDS_get_inches(duration);
  if (distance < 8.5) {  // This is where the LED On/Off happens
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