#include <AFMotor.h>

#define trigPin 9
#define echoPin 14
AF_DCMotor motora(1, MOTOR12_64KHZ);
AF_DCMotor motorb(2, MOTOR12_64KHZ);
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = A4; // analog pin connected to X output
const int Y_pin = A5; // analog pin connected to Y output
int startcar = 0;
int backward = 0;
 


 void setup() {
  // put your setup code here, to run once:
//Calls pins on the motor shield 

Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  
 
  

}

void loop() {
  // put your main code here, to run repeatedly:
  //Toggles on/off
  if (digitalRead(SW_pin) == 0 && startcar == 0) {
      while(digitalRead(SW_pin) == 0) {}
      startcar = 1 ; 
      delay(100); 
    }
      if (digitalRead(SW_pin) == 0 && startcar == 1) {
      startcar = 0 ; 
      delay(100); 
      }
  if (startcar == 1) {
    if (backward == 0) {
    motora.run(FORWARD);
    motorb.run(BACKWARD);
    Serial.print("Starting");
    }
   else {
    motora.run(BACKWARD);
    motorb.run(FORWARD);
   }
    
  }
   else if (startcar == 0) {
    motora.run(RELEASE);
    motorb.run(RELEASE);}
 
  if (analogRead(X_pin) < 1000 && analogRead(X_pin) > 600 && startcar == 1) {
      motora.setSpeed(100);    
      motorb.setSpeed(100);
      backward = 0;
      Serial.println("Slow");
    }
  
   if (analogRead(X_pin) < 600 && analogRead(X_pin) > 450 && (analogRead(Y_pin) < 600 && analogRead(Y_pin) > 450 && startcar == 1)) {
      motora.setSpeed(0);    
      motorb.setSpeed(0);
      Serial.println("Stop");
    }
    if (analogRead(X_pin) > 1000 && startcar == 1) {
      motora.setSpeed(255);    
      motorb.setSpeed(255);
      backward = 0;
      Serial.println("Fast");
    }
  if (analogRead(X_pin) < 450 && analogRead(X_pin) > 20 && startcar == 1) {
      motora.setSpeed(100);    
      motorb.setSpeed(100);
      backward = 1;
      Serial.println("Backwards Slow");
  }
   if (analogRead(X_pin) < 20 && startcar == 1) {
      motora.setSpeed(255);    
      motorb.setSpeed(255);
      backward = 1;
      Serial.println("Backwards Fast");
   }
   if (analogRead(y_pin) < 450 && > 20 && startcar == 1) {
      motora.setSpeed(0);    
      motorb.setSpeed(100);
      turning = 1;
      Serial.println("Left Slow");
   }
   if (analogRead(y_pin) < 20 && startcar == 1) {
      motora.setSpeed(0);    
      motorb.setSpeed(255);
      turning = 1;
      Serial.println("Left Fast");
   }
   
   
   
   float duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  
  if (distance >= 400 || distance <= 2){
    Serial.print("Distance = ");
    Serial.println("Out of range");
  }
  else {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);
  }
  delay(500);
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");
  delay(500);

}
