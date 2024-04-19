#include <ESP8266WiFi.h>

int port = 5055;
WiFiServer server(port);

const char *ssid = "OPTIMAROBOTICS2023";
const char *password = "3202SCITOBORAMITPO";

void setup() {
  Serial.begin(9600);
  Serial.println();
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  Serial.println("Connecting to WiFi.....");
  while(WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
  delay(500);
  }
  
  Serial.println("");
  Serial.print("Connected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  
  Serial.print("Open Telnet and connect to IP:");
  Serial.print(WiFi.localIP());
  Serial.print(" on port ");
  Serial.println(port);

}

void loop() {

  WiFiClient client = server.available();
  
  if (client) {
    if(client.connected()){
    
//      Serial.println("Client Connected");
    }
    
    while(client.connected()){
      
      while(client.available() > 0){
        Serial.print(client.readStringUntil('\n'));
      }
      
      while(Serial.available() > 0 ){
        client.print(Serial.readStringUntil('\n'));
      }
    }
    client.stop();
//    Serial.println("Client disconnected");
  }

}
