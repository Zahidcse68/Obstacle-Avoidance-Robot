//if u need any help reach me insta @xaidu_uu
// youtube  https://www.youtube.com/@techzaiduu

#include "AFMotor.h"
#include <Servo.h>

#define echopin A0 // echo pin
#define trigpin A1 // Trigger pin

Servo myservo;

const int MOTOR_1 = 1; 
const int MOTOR_2 = 2; 
const int MOTOR_3 = 3; 
const int MOTOR_4 = 4; 

AF_DCMotor motor1(MOTOR_1, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor2(MOTOR_2, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor3(MOTOR_3, MOTOR12_64KHZ); // create motor object, 64KHz pwm
AF_DCMotor motor4(MOTOR_4, MOTOR12_64KHZ); // create motor object, 64KHz pwm
//===============================================================================
//  Initialization
//===============================================================================

int distance_L, distance_F, distance_R;
long distance;

int set = 10;

 
void setup() {
  Serial.begin(9600);           // Initialize serial port
  Serial.println("Start");

  myservo.attach(10);
  myservo.write(90);

  pinMode (trigpin, OUTPUT);
  pinMode (echopin, INPUT );
  
  motor1.setSpeed(150);          // set the motor speed to 0-255
  motor2.setSpeed(150);
  motor3.setSpeed(150);
  motor4.setSpeed(150);
}
//===============================================================================
//  Main
//=============================================================================== 
void loop() {
 distance_F = data();
 Serial.print(distance_F);
 Serial.print("S=");
 Serial.println(distance_F);
 myservo.write(170);
 delay(5000);
 myservo.write(-170);
  delay(5000);
  if (distance_F > set){
   Serial.println("Forward");
  motor1.run(FORWARD);         // turn it on going forward
  motor2.run(FORWARD); 
  motor3.run(FORWARD); 
  motor4.run(FORWARD);
    }
    else{hc_sr4();}
}


long data(){
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  long duration = pulseIn (echopin, HIGH);
   int distance = duration * 0.034 / 2;
  return distance;
}


void compareDistance(){
   
  if (distance_L > distance_R){
    motor1.run(FORWARD);  // the other right
  motor2.run(FORWARD); 
  motor3.run(BACKWARD); 
  motor4.run(BACKWARD);
   delay(350);
  }
  else if (distance_R > distance_L){
  motor1.run(BACKWARD);   // turn it on going left
  motor2.run(BACKWARD);
  motor3.run(FORWARD); 
  motor4.run(FORWARD); 
   
    delay(350);
  }
  else{
  motor1.run(BACKWARD);  // the other way
  motor2.run(BACKWARD);
  motor3.run(BACKWARD); 
  motor4.run(BACKWARD); 
   delay(300);
  motor1.run(BACKWARD);   // turn it on going left
  motor2.run(BACKWARD);
  motor3.run(FORWARD); 
  motor4.run(FORWARD); 
    delay(500);
  }
}

void hc_sr4(){
    Serial.println("Stop");
    motor1.run(RELEASE);         // stopped
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
   
    myservo.write(0);
    delay(3000);
    distance_R = data();
    delay(1000);
    myservo.write(170);
    delay(5000);
    distance_L = data();
    delay(1000);
    myservo.write(90);
    delay(3000);
    compareDistance();
}
