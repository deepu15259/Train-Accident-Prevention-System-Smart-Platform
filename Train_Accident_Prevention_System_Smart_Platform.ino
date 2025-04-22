#include <Servo.h> 
// Pin assignments 
const int irSensorPin = 8; 
const int servoPin1 = 9; 
const int servoPin2 = 10; 
const int leftTrigPin = 2; 
const int leftEchoPin = 3; 
const int rightTrigPin = 4; 
const int rightEchoPin = 5; 
// Variables 
unsigned long startTime = 0; 
unsigned long endTime = 0; 
float distanceBetweenSensors = 100.0; 
Servo servo1; 
Servo servo2; 
int initialPosition1 = 90;  
int initialPosition2 = 90;   
void setup() 
{ 
Serial.begin(9600); 
pinMode(leftTrigPin, OUTPUT); 
pinMode(leftEchoPin, INPUT); 
pinMode(rightTrigPin, OUTPUT); 
pinMode(rightEchoPin, INPUT); 
27 
pinMode(irSensorPin, INPUT); 
servo1.attach(servoPin1); 
servo2.attach(servoPin2); 
// Set initial positions for the servo motors 
servo1.write(initialPosition1); 
servo2.write(initialPosition2); 
Serial.println("Welcome to Railway Station"); 
} 
void loop() 
{ 
// Read IR sensor state 
int irSensorState = digitalRead(irSensorPin); 
leftDistance = measureDistance(leftTrigPin, leftEchoPin, leftDuration); 
long rightDuration, rightDistance; 
rightDistance = measureDistance(rightTrigPin, rightEchoPin,    rightDuration); 
// If a train is detected by the IR sensor 
if (irSensorState == HIGH && startTime == 0) 
{ 
startTime = millis(); 
} else if (irSensorState == LOW && startTime != 0)  
{ 
endTime = millis(); 
float timeDifference = (endTime - startTime) / 1000.0; 
float speed = distanceBetweenSensors / timeDifference; 
startTime = 0; 
endTime = 0; 
// If train speed is below 100 and detected by left sensor only 
if(speed < 100 && (leftDistance < 20 && rightDistance > 20))  
{ 
} 
{ 
} 
Serial.println("Train Arrived"); 
servo1.write(90); 
servo2.write(90); 
} 
{ 
} 
// If train speed is below 100 and detected by right sensor only 
else if(speed < 100 && (rightDistance < 20 && leftDistance > 20))  
Serial.println("Train Arrived"); 
servo1.write(90); 
servo2.write(90); 
// If no train is detected by either sensor 
else if (leftDistance > 20 && rightDistance > 20); 
Serial.println("No Train Detected"); 
servo1.write(180); 
servo2.write(0); 
delay(1500);  
} 
// Function to measure distance using ultrasonic sensors 
long measureDistance(int trigPin, int echoPin, long &duration) 
{ 
digitalWrite(trigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH); 
delayMicroseconds(10); 
digitalWrite(trigPin, LOW); 
pinMode(echoPin, INPUT); 
duration = pulseIn(echoPin, HIGH); 
return (duration * 0.034 / 2); 
} 
