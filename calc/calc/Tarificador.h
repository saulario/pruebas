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
    tntdb::Statement stmtRegla;

    std::map<std::string, vwze::entity::Elt *> eltMap;
    std::map<unsigned long, vwze::entity::Rfc *> rfcMap;
    std::map<std::string, vwze::entity::Zon *> zonMap;

    void borrarImportes(int);
    void cargarEntorno(void);
    
    std::string componerRegla(vwze::entity::Doe *);
    vwze::entity::Rfd * localizarRegla(vwze::entity::Doe *);
    
    void tarificarCC(void);
    void tarificarTipo(int tipo);

};

#endif /* TARIFICADOR_H */

