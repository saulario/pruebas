#ifndef Clase1_h
#define Clase1_h

#include <ProcessScheduler.h>
#include "Contexto.h"

 class Clase1 : public Process {
  public:
    Clase1(Scheduler &manager, ProcPriority pr, unsigned int period, unsigned int iterations)
        : Process(manager, pr, period, iterations) {}

    void setContexto(const Contexto &);

  protected:
    virtual void service(void);

  private:
    Contexto contexto;
        
 };

 #endif
