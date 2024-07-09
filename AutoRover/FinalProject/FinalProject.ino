#include <Ultrasonic.h>
#include <Servo.h>
#include <L298N.h>

// object for ultrasinic sensor
Ultrasonic u = Ultrasonic(3, 4);  //trig, echo

// object for Servo Motor
Servo s = Servo();

// object for motors(L298N)
L298N m1 = L298N(5, 6, 7);     //(ena, in1,in2) // if the motor not working properly we should change the in1 and in2 setp1: 5,6,7//  step: 5,7,6;
L298N m2 = L298N(11, 13, 12);  //(enb, in3,in4)

void setup() {
  pinMode(8, OUTPUT);
  s.attach(2);

  m1.setSpeed(200);
  m2.setSpeed(200);

  Serial.begin(9600);
}

void loop() {
  int x = Serial.read();
  int d = u.read();

  if (d < 15) {
    m1.stop();
    m2.stop();
  }

  if (x == '1') {  // Forward
    if (d > 15) {
      m1.forward();
      m2.forward();
    }
  }
  if (x == '2') {  // Backward
    m1.backward();
    m2.backward();
  }
  if (x == '0') {  // Stop
    m1.stop();
    m2.stop();
  }
  
  if (x == '3') {  // Turn Left
    s.write(150);
    delay(1000);
    int d1 = u.read();
    if (d1 > 15) {
      m1.forward();
      m2.backward();
      delay(300);
      m1.stop();
      m2.stop();
    }
    s.write(90);
    delay(1000);
  }

  if (x == '4') {  // Turn Right
    s.write(30);
    delay(1000);
    int d2 = u.read();
    if (d2 > 15) {
      m1.backward();
      m2.forward();
      delay(300);
      m1.stop();
      m2.stop();
    }
    s.write(90);
    delay(1000);
  }

  if(x == '5'){
    digitalWrite(8, LOW);
  }
  if(x == '6'){
    digitalWrite(8, HIGH);
  }
  delay(200);
}
