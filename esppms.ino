#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>
#include <MFRC522.h>
#include <NewPing.h>


const char* ssid = "Realme GT Master Edition";//include ssid
const char* password = "12345678";//include password
//WiFiClient client;
char server[] = "192.168.246.246";   //include local ip eg: 192.168.0.222

const int triggerPin = D0; // Replace with your GPIO pin numbers
const int echoPins[] = {D1, D2, D3, D4};    // Replace with your GPIO pin numbers
const int maxDistance = 200; // Maximum distance in cm

NewPing sonars[] = {
  NewPing(triggerPin, echoPins[0], maxDistance),
  NewPing(triggerPin, echoPins[1], maxDistance),
  NewPing(triggerPin, echoPins[2], maxDistance),
  NewPing(triggerPin, echoPins[3], maxDistance), 
};

WiFiClient client;    


void setup()
{
 Serial.begin(9600);
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
//  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
  delay(1000);
  Serial.println("connecting...");
 }
void loop()
{ 
  for (int i = 0; i < 4; i++) {
    delay(500); // Wait for a while to avoid spamming the database

    // Measure distance using each HC-SR04 sensor
    int distance = sonars[i].ping_cm();

    if (distance != 0) {
      // Send the distance data to MySQL database
      int state = 0;
      if(distance<10){
        state=1;
      }
      SendData(state,i+1);
    } 
    else {
      Serial.println("Error measuring distance.");
    }
  }
 }

 void SendData(int state,int s_no)   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET /ultra/sense.php?state=");
    client.print("GET /ultra/sense.php?state=");     //YOUR URL
    Serial.print(state);
    client.print(state);
    client.print("&s_no=");
    Serial.print("&s_no=");
    client.print(s_no);
    Serial.println(s_no);
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 192.168.246.246");//Include LOCAL IP
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }