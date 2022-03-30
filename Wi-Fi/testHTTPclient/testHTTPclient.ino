/*
  Test HTTP Client 
  Context: Arduino, with WINC1500 module
*/
// include required libraries and config files
#include <SPI.h>
//#include <WiFi101.h>
//#include <ESP8266WiFi.h>    // use this instead of WiFi101 for ESP8266 modules
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include "config.h"

WiFiClient netSocket;               // network socket to server
const char server[] = "https://working-maroon-tibia.glitch.me";  // server name
String route = "/api/route";              // API route

void setup() {
  Serial.begin(9600);    // initialize serial communication
  while(!Serial);

  // while you're not connected to a WiFi AP,
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);           // print the network name (SSID)
    WiFi.begin(ssid, pass);         // try to connect
    delay(2000);
  }

  // When you're connected, print out the device's network status:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
  HttpClient http(netSocket, 80);      // make an HTTP client
  http.get(route);  // make a GET request

  while (http.connected()) {       // while connected to the server,
    if (http.available()) {        // if there is a response from the server,
      String result = http.readString();  // read it
      Serial.print(result);               // and print it
    }
  }
  // when there's nothing left to the response,
  http.stop();                     // close the request
  delay(5000);                    // wait 10 seconds
}
