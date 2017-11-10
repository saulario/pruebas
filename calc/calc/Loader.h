#ifndef LOADER_H
#define LOADER_H

#include <tntdb/connection.h>
#include <tntdb/date.h>

#include "ParserTarifa.h"
#include "vwze_entity.h"

class Loader {
public:
    Loader(tntdb::Connection &);
    Loader(const Loader& orig);
    virtual ~Loader();

    void calcularAgregados(void);
    void cargarMaps(void);
    void reconstruirDocumentos(void);    

private:
    static log4cxx::LoggerPtr logger;
    tntdb::Connection con;
    
    std::map<std::string, vwze::entity::Kcc *> kccMap;
    std::map<std::string, vwze::entity::Zon *> zonMap;
    std::map<std::string, double> directosMap;
    
    
    unsigned long doccod;
    unsigned long dodcod;
    unsigned long doecod;
    
    void borrarDatos(void);
    
    void calcularAgregados(int);
    void calcularAgregadosWA1(void);
    void calcularAgregadosWA2(void);
    void calcularAgregadosWE1(void);
    void calcularAgregadosWE2(void);
    
    void calcularDirectosWA(void);
    void calcularDirectosWE(void);
      
    void procesarDocumentoWA(const vwze::entity::Doc *);
    void procesarDocumentoWE(const vwze::entity::Doc *);
       
    void insertarDirecto(const vwze::entity::Doc *, const std::string &, int);
    void insertarDocumentosWA(const vwze::entity::Doc *);
    void insertarDocumentosWE(const vwze::entity::Doc *);
    
    tntdb::Date parsearDate(const std::string &);
    double parsearDouble(const std::string &);
    
    std::string getCodigoWA(const vwze::entity::Doc *);
    std::string getCodigoWA(const vwze::entity::Dod *);
    std::string getCodigoWE(const vwze::entity::Doc *);
    std::string getCodigoWE(const vwze::entity::Dod *);
       
    vwze::entity::Dod * getInstance(const vwze::entity::Doc *);
    
    std::string getKccCodigo(const std::string &);
    std::string getKccDescripcion(const std::string &);    
    

};

#endif /* LOADER_H */

