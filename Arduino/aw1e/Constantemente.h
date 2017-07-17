#ifndef Constantemente_h
#define Constantemente_h

#include <ProcessScheduler.h>

#include "Contexto.h"

class Constantemente : public Process {
  public:
    Constantemente(Scheduler &manager, ProcPriority pr, unsigned int period, unsigned int iterations)
        : Process(manager, pr, period, iterations)  {
          contador = 0;
    }

  void restart(void);  
  void setContexto(const Contexto &);      

  protected:
    virtual void service(void);  

  private:
    int contador;
    Contexto contexto;
};

#endif
