//
// Meeeno DS18B20 Digital Temperature Sensor Module

#include <DallasTemperature.h>
#include <OneWire.h>

const int OURWIRE_PIN = 2;

const int GREEN_LED = 3;
const int RED_LED = 4;

const int TRIG_PIN = 12;
const int ECHO_PIN = 13;



OneWire ourWire(OURWIRE_PIN);
DallasTemperature sensores(&ourWire);
DeviceAddress device;

void setup() {
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("\nInitializing ...");
  sensores.begin();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // sensor de distancia
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);  

  //if (!sensores.getAddress(device, 0)) {
  //  Serial.println("Error obteniendo la dirección del sensor");
  //}
  
}


void loop(void) {

  long duration;  
  double distanceCm;

  sensores.requestTemperatures();

  //Serial.print(sensores.getTempCByIndex(0)); 
  //Serial.println(" grados cent. ");

  // distancia
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  //delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN,HIGH);  

  // convert the time into a distance
  distanceCm = duration / 29.1 / 2 ;

  if (distanceCm <= 0){
    Serial.println("Out of range");
  }
  else {
    //Serial.print(distanceCm);
    //Serial.print(" centímetros");
    //Serial.println();
  }  

  if (distanceCm < 60) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  } else {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }

  //delay(10);


}
