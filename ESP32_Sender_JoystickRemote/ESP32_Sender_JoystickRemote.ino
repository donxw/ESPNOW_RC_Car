/**
   ESP-NOW: ESP32 Broadcast with ESP-Now
   Use Get_MAC.ino to get the MAC address of the CPU to send the joystick data to
   ESP32 has a 12 bit ADC 0 to 4095 steps

   board:  ESP32 Dev Module

   Pin assignments:
    GPIO 32 - valY
    GPIO 33 - valX
    GPIO 27 - joystick button

*/
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

//ESP8266 Mac address (first peer)
//30:83:98:B1:DA:0D Red Car 1 NodeMCU MAC
uint8_t mac_peer1[] = {0x30, 0x83, 0x98, 0xB1, 0xDA, 0x0D};

esp_now_peer_info_t peer1;

// Pins
#define BTN 27
#define VRY 33
#define VRX 32

// Variables
int state = 0;
const int valX_center = 1860;  // from testing the joystick center value
const int valY_center = 1826;
const int deadBand = 20;
int deltaX = 0;
int deltaY = 0;
int prev_deltaX = 1000;
int prev_deltaY = 1000;

// Structured variable to be sent by ESPNOW
typedef struct message {
  int valX;  // left - right joystick
  int valY;  // fwd - back joystick
  bool button;  // button state
};
struct message myMessage;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // Get Mac Add
  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("ESP32 ESP-Now Broadcast");

  // Initializing the ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }

  memcpy(peer1.peer_addr, mac_peer1, 6);
  peer1.channel = 0;
  // Register the peer
  Serial.println("Registering a peer 1");
  if ( esp_now_add_peer(&peer1) == ESP_OK) {
    Serial.println("Peer 1 added");
  }

  esp_now_register_send_cb(OnDataSent);

  pinMode(BTN, INPUT_PULLUP);  // joystick button grounds the pin
}

void loop() {

  deltaY = abs(analogRead(VRY) - valY_center);
  deltaX = abs(analogRead(VRX) - valX_center);

  deltaY = deltaY < deadBand ? 0 : deltaY;  // if deltaY is less than deadband, set to zero, else no change
  deltaX = deltaX < deadBand ? 0 : deltaX;

  if (deltaY != prev_deltaY || deltaX != prev_deltaX ) {
    prev_deltaY = deltaY;
    prev_deltaX = deltaX;
    myMessage.valY = analogRead(VRY);
    myMessage.valX = analogRead(VRX);
    Serial.printf("valY: %i", myMessage.valY);
    Serial.printf(", valX: %i\n", myMessage.valX);
    state = digitalRead(BTN);
    myMessage.button = state;
    esp_now_send(NULL, (uint8_t *) &myMessage, sizeof(myMessage));
  }

  if (state != digitalRead(BTN)) {
    myMessage.valY = analogRead(VRY);
    myMessage.valX = analogRead(VRX);
    state = digitalRead(BTN);
    myMessage.button = state;
    esp_now_send(NULL, (uint8_t *) &myMessage, sizeof(myMessage));
  }

  delay(100);  // run at 10 Hz
}
