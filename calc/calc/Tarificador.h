#ifndef TARIFICADOR_H
#define TARIFICADOR_H

#include <map>
#include <tntdb/connection.h>

#include "vwze_entity.h"

class Tarificador {
public:
    Tarificador(tntdb::Connection &);
    virtual ~Tarificador();
    
    void tarificar(void);
    
private:
    static log4cxx::LoggerPtr logger;    
    tntdb::Connection con;    

    std::map<std::string, vwze::entity::Zon *> zonMap;
    
    void borrarImportes(int);
    void cargarMaps(void);
    
    void tarificarCC(void);
    void tarificarWA1(void);
    void tarificarWA2(void);
    void tarificarWE1(void);
    void tarificarWE2(void);

};

#endif /* TARIFICADOR_H */

