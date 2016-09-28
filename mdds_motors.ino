#include "Wire.h"   
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "gpio.h"

#include "Globals.h"
#include "Output.h"

void      initWifi();

#define SerialDebug true  // set to true to get Serial output for debugging
#define myLed 5

Output *output;

//IPAddress ip = IPAddress();
//ESP8266WebServer server(ip.fromString("192.168.1.199"), 80);
ESP8266WebServer server(80);

Motor_data up_data, down_data, right_data, left_data, front_data, back_data;
 
void handle_root() {
  server.send(200, "text/plain", "Hello from the ESP8285!");
}

void parse_motor_data(String s, Motor_data * m_data){
  m_data->state = (uint8_t)atoi(&s[0]);
  m_data->intensity = (uint16_t)s.substring(2).toInt();
}


void update_motors() 
{
  if (!((server.hasArg("up") && server.arg("up").length() >= 2) &&
        (server.hasArg("down") && server.arg("down").length() >= 2) &&
        (server.hasArg("left") && server.arg("left").length() >= 2) &&
        (server.hasArg("right") && server.arg("right").length() >= 2) &&
        (server.hasArg("front") && server.arg("front").length() >= 2) &&
        (server.hasArg("back") && server.arg("back").length() >= 2)))
        {
          server.send(401, "text/plain", "Error:  All motors not defined or length <= 2");
        }

  parse_motor_data(server.arg("up"), &up_data); 
  parse_motor_data(server.arg("down"), &down_data);
  parse_motor_data(server.arg("right"), &right_data);
  parse_motor_data(server.arg("left"), &left_data);
  parse_motor_data(server.arg("front"), &front_data);
  parse_motor_data(server.arg("back"), &back_data);

  output->writeMotors();
  
  String webstring = "up state: " + String(up_data.state) + " : " + String(up_data.intensity) +
                      "down state: " + String(down_data.state) + " : " + String(down_data.intensity) +
                      "left state: " + String(left_data.state) + " : " + String(left_data.intensity) +
                      "right state: " + String(right_data.state) + " : " + String(right_data.intensity) +
                      "front state: " + String(front_data.state) + " : " + String(front_data.intensity) +
                      "back state: " + String(back_data.state) + " : " + String(back_data.intensity);
  server.send(200, "text/plain", webstring); 
    
  
}

void setup()
{

  Serial.begin(115200);

  pinMode(myLed, OUTPUT);
  digitalWrite(myLed, LOW);
  
  Wire.begin(0,2); // SDA (0), SCL (2) on ESP8285
  Wire.setClock(400000); // choose 400 kHz I2C rate
  
  // Instantiate output class
  output = new Output();
  output->initOutput();
 
  initWifi();

  server.on("/test", [](){
  
  server.send(200, "text/html", "<html><body>Test Test</body></html>");               // send to someone's browser when asked
  });

  server.on("/", handle_root);
  server.on("/motor_update", HTTP_GET, update_motors);
  
  server.begin();
  Serial.println("HTTP server started");
  
}
 

void loop()
{      
  server.handleClient(); // serve data to web server site 
  delay(10);
}

//===================================================================================================================
//====== Set of useful function to access acceleration, gyroscope, magnetometer, and temperature data
//===================================================================================================================
void initWifi() 
{
  const char* ssid     = "DACGO";
  const char* password = "1f900ba235";
 // Connect to WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

 // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("ESP8285 Environmental Data Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
