/*
    Board:  NodeMCU 1.0 (ESP-12E Module)

    Wire Motor A to left motor
    Wire Motor B to right motor
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>

// Ultrasonic Sensor
#include <HCSR04.h>
// Initialize sensor to use digital pins 9 and 10.
int triggerPin = 10;
int echoPin = 9;
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);

// Define User Types below here or use a .h file
//
#define DIRA 0  //D3
#define PWMA 5  //D1
#define DIRB 2  //D4
#define PWMB 4  //D2
#define CW 0
#define CCW 1

#define maxSpeed 255   // Max motor speed
#define deadBand 20   // Safe range to ignore round midpoint of joystick readings...
#define FORWARD 1
#define BACKWARD 2
#define LEDPIN BUILTIN_LED
// #define DEBUG

//  Global Variables
//
int dirMotorL = FORWARD;
int dirMotorR = FORWARD;
int motorSpeedL = 0;
int motorSpeedR = 0;
int speedDiff = 0;
const int valX_center = 1830;  // from testing the joystick center value
const int valY_center = 1830;
int full_range = 4095;  // full Joystick range from ESP32

typedef struct message {
  int valX;
  int valY;
  int button;
} message;

message myMessage;
bool newMessage = false;

// Define Functions below here or use other .ino or cpp files
//
void playmelody();

void onDataReceiver(uint8_t* mac, uint8_t* incomingData, uint8_t len) {
  //Serial.println("Message received.");
  newMessage = true;
  // Transform the incoming data into our message structure
  memcpy(&myMessage, incomingData, sizeof(myMessage));
}

// The setup() function runs once each time the micro-controller starts
void setup()
{
  Serial.begin(115200);

  // Setup ESPNOW
  WiFi.disconnect();
  ESP.eraseConfig();

  // Wifi STA Mode
  WiFi.mode(WIFI_STA);

  // Get Mac Add  uncomment for debug
  Serial.print("\n");
  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("\nESP-Now Receiver");

  // Initializing the ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }

  // Intialize ESPNow message
  myMessage.valX = valX_center;
  myMessage.valY = valY_center;
  myMessage.button = true;

  // Set ESPNow Role
  //esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  //
  // Register the receiver callback function
  esp_now_register_recv_cb(onDataReceiver);

  // Setup Motor Sheild Pins
  pinMode(DIRA, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(PWMB, OUTPUT);

  // Play tone on power up
  playmelody();

  // turn on built in LED
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
    
#ifdef DEBUG
  // plotter logo
  Serial.print(" ValY ValX Button ");
#endif // DEBUG
    
  //test ESPNOW messaging
  //myMessage.valY = 3000;
}

// Add the main program code into the continuous loop() function
void loop()
{
  // ultrasonic sensor
  double distance = distanceSensor.measureDistanceCm();
  // send sensor readings to serial port 
  //Serial.print("Distance (cm):  "); Serial.println(distance);
  
  // take action if object is detected  
  if (distance <= 20) {
    if (distance != -1) {  // ignore bad readings

      // move backward 1 sec
      digitalWrite(DIRA, CW);  //Left Motor CW for Reverse
      analogWrite(PWMA, maxSpeed);
      digitalWrite(DIRB, CCW);  //Right Motor CCW for Reverse
      analogWrite(PWMB, maxSpeed);
      delay(1000);

      // turn 0.7 sec
      digitalWrite(DIRA, CW);  //Left Motor CW for Reverse
      analogWrite(PWMA, maxSpeed);
      digitalWrite(DIRB, CW);  //Right Motor CCW for Reverse
      analogWrite(PWMB, maxSpeed);
      delay(700);  // adjust until ~180 turn is achieved
    }
  }

  // uncomment define DEBUG to run
#ifdef DEBUG
  if (newMessage == true) {
    Serial.print(myMessage.valY); Serial.print(" ");
    Serial.print(myMessage.valX); Serial.print(" ");
    Serial.print(myMessage.button * 1000); Serial.print("\n");
    newMessage = false;
  }
#endif // DEBUG
    
  // map joystick Y-axis to motor speed (deadband may not be needed since accounted for in sender)
  motorSpeedL = motorSpeedR = 0;
  if (myMessage.valY < (valY_center - deadBand)) {
    motorSpeedL = map(myMessage.valY, 0, valY_center, -maxSpeed, 0);
    motorSpeedR = motorSpeedL;
  }
  else if (myMessage.valY > (valY_center + deadBand)) {
    motorSpeedL = map(myMessage.valY, valY_center, full_range, 0, maxSpeed);
    motorSpeedR = motorSpeedL;
  }

  // determine speed difference in motors from joystick X-axis value
  speedDiff = 0;
  if (myMessage.valX < valX_center - deadBand) {
    speedDiff = map(myMessage.valX, 0, valX_center, -maxSpeed, 0);
  }
  else if (myMessage.valX > valX_center + deadBand) {
    speedDiff = map(myMessage.valX, valX_center, full_range, 0, maxSpeed);
  }

  // set Motor Speeds
  motorSpeedL += speedDiff;
  motorSpeedR -= speedDiff;

  dirMotorL = motorSpeedL < 0 ? BACKWARD : FORWARD;  //LEFT MOTOR_CH_A CCW IS FORWARD
  dirMotorR = motorSpeedR < 0 ? BACKWARD : FORWARD;  //RIGHT MOTOR_CH_B CW IS FORWARD

  // limit Motor Speeds to max value allowed
  motorSpeedL = abs(motorSpeedL);
  motorSpeedR = abs(motorSpeedR);
  if (motorSpeedL > maxSpeed) motorSpeedL = maxSpeed;
  if (motorSpeedR > maxSpeed) motorSpeedR = maxSpeed;

  // set Left motor speed & direction
  //dirMotorL == FORWARD ? M1.setmotor(_CCW, motorSpeedL) : M1.setmotor(_CW, motorSpeedL);
  if (dirMotorL == FORWARD) {
    digitalWrite(DIRA, CCW);  //Left Motor CCW for Forward
    analogWrite(PWMA, motorSpeedL);
  }
  else {
    digitalWrite(DIRA, CW);  //Left Motor CW for Reverse
    analogWrite(PWMA, motorSpeedL);
  }

  // set Right motor speed & direction
  //dirMotorR == FORWARD ? M2.setmotor(_CW, motorSpeedR) : M2.setmotor(_CCW, motorSpeedR);
  if (dirMotorR == FORWARD) {
    digitalWrite(DIRB, CW);  //Right Motor CW for Forward
    analogWrite(PWMB, motorSpeedR);
  }
  else {
    digitalWrite(DIRB, CCW);  //Right Motor CCW for Reverse
    analogWrite(PWMB, motorSpeedR);
  }

  // beep on button push
  if (myMessage.button == false) {
    playmelody();
    Serial.println("beep beep");
    myMessage.button = true;
  }

  delay(100); //update @ 20Hz

}
