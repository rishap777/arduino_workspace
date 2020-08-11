/* This Project is to Receive the Data From Mobile Phone In form Of UDP packets.
 * This Received data is then decoded into actual requied data.
 * The required received data is transfer via UART Interface at BAUD=115200.
 */

//#include <SPI.h>
//#include <WiFi.h>
#include<SoftwareSerial.h> //Included SoftwareSerial Library
/*ESP8266WiFi.h is required for basic interface to interact with ESP8266 module*/
#include <ESP8266WiFi.h>
/*WiFiUdp.h is required for UDP related system APIs*/
#include <WiFiUdp.h>


#define UART_BAUDRATE 9600U
#define LOCAL_PORT_UDP 4522

IPAddress ip(192, 168, 1, 22); //Static IP address for Esp8266 
IPAddress gateway(192,168,1,1);   
IPAddress subnet(255,255,255,0);   

WiFiUDP Udp;

SoftwareSerial uart(12,14); //SoftwareSerial uart(RX pin,TX pin);

bool wifioff = true;
bool persistent = false;
char *ssid = "Pacific";    
char *pass = "anuj1105"; 
char incomingPacket[255];  // buffer for incoming packets

void setup() {
  
  
  Serial.begin(115200);
  uart.begin(115200);
  
  WiFi.softAPdisconnect(wifioff);
  Serial.print("Connecting to SSID:");
  Serial.println(ssid);
  WiFi.config(ip,gateway,subnet);
  delay(5000);
  WiFi.begin(ssid,pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  
  Udp.begin(LOCAL_PORT_UDP);
  //Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(),LOCAL_PORT_UDP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);
    uart.print("S");
    uart.println(incomingPacket);
  }
  //Serial.print("~!~");
  delay(5);

}
