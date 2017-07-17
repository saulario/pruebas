#include <Ethernet.h>
#include <SD.h>
#include <SPI.h>

const int ethPin = 10;
const int sdPin = 4;

void setup() {

  Serial.begin(9600);
  Serial.println("Inicializando...");

  // establece ethernet
  pinMode(ethPin, OUTPUT);
  digitalWrite(ethPin, HIGH);

  // establece SD
  pinMode(sdPin, OUTPUT);
  digitalWrite(sdPin, LOW);
  
  SD.begin(sdPin);
  File root = SD.open("/");
  

  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  
  byte ip[] = { 192, 168, 1, 33 };    
  byte gateway[] = { 192, 168, 1, 1 };
  byte subnet[] = { 255, 255, 255, 0 };

  Ethernet.begin(mac, ip, gateway, subnet);
  Serial.print("\tIP local: "); Serial.println(Ethernet.localIP());



}

void loop() {

}
