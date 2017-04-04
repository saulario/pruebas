#include "Constantemente.h"

void Constantemente::restart(void) {
  contador = 0;
}

void Constantemente::setContexto(const Contexto & c) {
  contexto = c;
}

void Constantemente::service(void) {
  Serial.println(++contador);      
}

