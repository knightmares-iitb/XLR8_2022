#include "WiFi.h"                             // including the Wifi library
#include "ESPAsyncWebServer.h"                  // including the Web server library

/*
 * Here we declare the ssid (the name of the hotspot created by ESP32) and it's password.
 * Make sure to set the ssid as something unique for your team.
 */
const char* ssid = "Knightmares";
const char* password = "3.1415926535";

AsyncWebServer server(80); 

// ledPin refers to ESP32 GPIO 23
const int ENA = 21;
const int IN1 = 18;
const int IN2 = 19;
const int ENB = 25;
const int IN3 = 26;
const int IN4 = 27;
int spd;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin ledPin as an output.
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  WiFi.softAP(ssid, password);                // creates a WiFi hotspot on ESP32
  
  /*
   * After this we can start adding some code to control the ESP32.
   * We can make requests to the server through a webpage and make it perform different tasks.
   */

  server.on("/F", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    
    DFORWARD();
    request->send_P(200, "text/plain", "");   
  });

  server.on("/B", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we recieve a "turn-off" request from the webpage
    
    DBACKWARD();
    request->send_P(200, "text/plain", "");
  });

  server.on("/R", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we recieve a "turn-off" request from the webpage
    
    DRIGHT(); //Opposite for now coz thats what works correctly
    request->send_P(200, "text/plain", "");
  });

  server.on("/L", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we recieve a "turn-off" request from the webpage
    
    DLEFT();//Opposite for now coz thats what works correctly
    request->send_P(200, "text/plain", "");
  });
  server.on("/S", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    STOP();
    request->send_P(200, "text/plain", "");   
  });
  server.on("/1", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(1, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/2", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(2, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/3", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(3, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/4", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(4, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/5", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(5, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/6", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(6, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/7", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(7, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/8", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(8, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/9", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(9, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });
  server.on("/10", HTTP_GET, [](AsyncWebServerRequest *request){
    // the following code runs whenever we receive a "turn-on" request from the webpage
    spd = map(10, 1, 10, 100, 250);
    request->send_P(200, "text/plain", "");   
  });

  server.begin(); 
}

// M1 = left motor, ENA,IN1,IN2
//M2 = right motor, enB,IN3,IN4

//functino for forward
void M1DF(int spd){ // motor 1 digital forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA,spd);
}

void M2DF(int spd){ // motor 2 digital forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB,spd);
}

void M1DB(int spd){ // motor 1 digital backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA,spd);
}

void M2DB(int spd){ // motor 2 digital backward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB,spd);
}

void DFORWARD(){
  M1DF(spd);
  M2DF(spd);
}

void DBACKWARD(){
  M1DB(spd);
  M2DB(spd);
}

void DLEFT(){
  M1DB(100);
  M2DF(100);
}

void DRIGHT(){
  M1DF(100);
  M2DB(100);
}

void STOP(){
  M1DF(0);
  M2DF(0);
}

// the loop function runs over and over again forever
void loop() {                      // starts the web server
}   
