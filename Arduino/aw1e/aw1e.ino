#include <DallasTemperature.h>
#include <OneWire.h>
#include <ProcessScheduler.h>

#include "Clase1.h"
#include "Constantemente.h"
#include "Contexto.h"

/**
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * One Wire:
 *          PIN: 2
 * 
 * 
 * 
 * 
 * Distancia: SRF05
 * 
 * Temperatura: DS18B20
 *          Interface: One Wire
 * 
 * 
 * 
 */



 class Clase2 : public Process {
  public:
    Clase2(Scheduler &manager, ProcPriority pr, unsigned int period, unsigned int iterations)
        : Process(manager, pr, period, iterations) {}

  protected:
    virtual void service() {
      Serial.println("clase2");  
    }
 };




const int PIN_ONE_WIRE_BUS = 2;

const int PIN_TRIGGER = 12;
const int PIN_ECHO = 13;


const int LED_GREEN = 3;
const int LED_RED = 4;

// Bus One Wire
OneWire oneWire(PIN_ONE_WIRE_BUS);

DallasTemperature sensoresTE(&oneWire);
DeviceAddress device;

Scheduler scheduler;

Contexto contexto;

Clase1 clase1(scheduler, HIGH_PRIORITY, 1000, RUNTIME_FOREVER);
Clase2 clase2(scheduler, HIGH_PRIORITY, 5000, RUNTIME_FOREVER);
Constantemente constantemente(scheduler, HIGH_PRIORITY, SERVICE_CONSTANTLY, RUNTIME_FOREVER);

/**
 * Configuración
 */
void setup() {
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("\nInitializing timer...");
  

  Serial.println("\nInitializing temperature sensors...");
  sensoresTE.begin();
  
  Serial.print("\nInitializing distance sensors...");
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // sensor de distancia
  pinMode(PIN_TRIGGER,OUTPUT);
  pinMode(PIN_ECHO,INPUT);  

  if (!sensoresTE.getAddress(device, 0)) {
    Serial.println("Error obteniendo la dirección del sensor");
  }

  clase1.setContexto(contexto);
  clase1.add(true);
  clase2.add(true);
  constantemente.setContexto(contexto);
  constantemente.add(true);
  
}



void loop(void) {
  scheduler.run();
}


/**
 * Bucle principal
 */
void loop1(void) {

  long duration;  
  double distanceCm;

  sensoresTE.requestTemperatures();

  double t0 = sensoresTE.getTempCByIndex(0);
  double t1 = sensoresTE.getTempCByIndex(1);

  Serial.print("T0: "); Serial.println(t0);


  // distancia
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(PIN_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIGGER, LOW);
  duration = pulseIn(PIN_ECHO,HIGH);  

  // convert the time into a distance
  distanceCm = duration / 29.1 / 2 ;

  if (distanceCm <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print("D0: ");Serial.println(distanceCm);
    
  }  

  if (distanceCm < 60) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
  } else {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
  }

  //delay(10);


}
