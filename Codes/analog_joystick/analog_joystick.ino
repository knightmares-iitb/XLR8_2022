/*
    This code is written for Esp32 DEVKIT V1 which has inbuilt Wifi Module
    You need 2 analog Joysticks 
    Could work on 1 but 2 will feel better and give better control due to cliping
    You need to download these libraries from the net. 
    (just google them you'll find a github  repo just copy it in your library folder of arduino IDE)
    Also Change the MAC address of the reciever (your bot) {again google on how to find MAC Address}
*/

// Include Libraries
#include <esp_now.h>
#include <WiFi.h>

// Variables for test data
int JoyStick_X = 35; // Analog Pin  X
int JoyStick_Y = 34; // // Analog Pin  Y
int SpeedPin = 32 ; 
// MAC Address of responder - edit as required
uint8_t broadcastAddress[] = {0x0C, 0xB8, 0x15, 0xF5, 0x9F, 0xD4};

// Define a data structure
typedef struct struct_message {

  int x,y,cmd;
  int spid;

} struct_message;

// Create a structured object
struct_message myData;

// Peer info
esp_now_peer_info_t peerInfo;

// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  
  // Set up Serial Monitor
  Serial.begin(115200);

  pinMode(JoyStick_X,INPUT);
  pinMode(JoyStick_Y,INPUT);
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {

  // Create test data
  int x = analogRead(JoyStick_X); //  X
  int y = analogRead(JoyStick_Y); //  Y
  int speedraw = analogRead(SpeedPin); 

  
  // Format structured data
  myData.x = x;
  myData.y = y;
  myData.cmd = cmd();
  myData.spid=map(speedraw,0,4095,0,5);;
  Serial.println(myData.cmd);
  Serial.println(myData.spid);
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sending confirmed");
  }
  else {
    Serial.println("Sending error");
  }
  delay(50);
}
int cmd()
{
  int valX=digi(analogRead(34));
  int valY = digi(analogRead(35));
  // put your main code here, to run repeatedly:
  Serial.print("X: ");
  Serial.print(valX);
  Serial.print(" Y: ");
  Serial.print(valY);
  Serial.println();
  if ((valX==1)and (valY==1)){
      return 0;
    }
  if ((valX==1)and (valY==2)){
      return 1;
    }
  if ((valX==2)and (valY==2)){
      return 2;
    }
  if ((valX==2)and (valY==1)){
      return 3;
    }
  if ((valX==2)and (valY==0)){
      return 4;
    }
  if ((valX==1)and (valY==0)){
      return 5;
    }
  if ((valX==0)and (valY==0)){
      return 6;
    }
  if ((valX==0)and (valY==1)){
      return 7;
    }
  if ((valX==0)and (valY==2)){
      return 8;
    }
 
}
int digi(int analval){
    if ( analval < 200)  return 0;
    if((analval  >1500)and (analval<2000))  return 1;
    if (analval >3800) return 2;
    else return 3;
}
