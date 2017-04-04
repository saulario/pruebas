#include "Clase1.h"

void Clase1::setContexto(const Contexto & c) {
  contexto = c;
}

void Clase1::service(void) {
  contexto.holaMundo();    
}

