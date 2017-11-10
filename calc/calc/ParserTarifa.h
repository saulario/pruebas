#ifndef PARSERTARIFA_H
#define PARSERTARIFA_H
#include <tntdb/connection.h>

class ParserTarifa {
public:
    ParserTarifa(tntdb::Connection &);
    
    void cargarTarifaArrastres(const std::string &);
    void cargarTarifaCapilar(const std::string &);
    void cargarTarifaDirectos(const std::string &);
    
//    void borrarTarifas(void);

//    void insertarReglaPlanta(const std::string &);
//    void insertarReglaProveedor(const std::string &);
    
private:
    static log4cxx::LoggerPtr logger;    
    tntdb::Connection con;
    
//    int getIntervaloProveedor(const int);
//    
//    std::string getReglaPlanta(const std::vector<std::string> &);
//    std::string getReglaProveedor(const std::vector<std::string> &);
    
    double round(const double, const unsigned int);
    double parse(const std::string &);
    
//    std::string texto2zona(const std::string &);
//    std::string zona2texto(const std::string &);


    void borrarTarifas(const std::string &);
    void establecerNumeradores(void);    
    
    unsigned long rfccod;
    unsigned long rfdcod;

};

#endif /* PARSERTARIFA_H */

