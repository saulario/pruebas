#ifndef LOADER_H
#define LOADER_H

#include <tntdb/connection.h>
#include <tntdb/date.h>

#include "vwze_entity.h"

class Loader {
public:
    Loader(tntdb::Connection &);
    Loader(const Loader& orig);
    virtual ~Loader();

    void cargarExpediciones(void);
    void calcularAgregados(void);

private:
    static log4cxx::LoggerPtr logger;
    tntdb::Connection con;
    
    std::map<std::string, vwze::entity::Pro *> proMap;
    std::map<std::string, vwze::entity::Zon *> zonMap;
    
    unsigned long doccod;
    unsigned long dodcod;
    unsigned long doecod;
    
    void borrarDatos(void);
    void calcularAgregadosWA1(void);
    void calcularAgregadosWA2(void);
    void calcularAgregadosWE1(void);
    void calcularAgregadosWE2(void);
    void calcularManipulaciones(void);
    
    void cargarDatos(void);
    void insertarDocumento(vwze::entity::Doc *);
    void insertarDocumentosWA(vwze::entity::Doc *);
    void insertarDocumentosWE(vwze::entity::Doc *);
    vwze::entity::Doc * parsearLinea(const std::string &);
    tntdb::Date parsearDate(const std::string &);
    double parsearDouble(const std::string &);
    
    std::string getKccCodigo(const std::string &);
    std::string getKccDescripcion(const std::string &);

};

#endif /* LOADER_H */

