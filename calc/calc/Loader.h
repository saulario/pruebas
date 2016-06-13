#ifndef LOADER_H
#define LOADER_H

#include <tntdb/connection.h>
#include <tntdb/date.h>

class Aviso {
public:
    std::string relevancia;
    std::string expedicion;
    tntdb::Date fecha;
    std::string org_zona;
    std::string org_poblacion;
    std::string des_zona;
    std::string des_poblacion;
    std::string flujo;
    std::string fabrica;
    std::string duns;
    std::string proveedor;
    double peso;
    double volumen;

    Aviso() {
        relevancia = "";
        expedicion = "";
        fecha = tntdb::Date(1, 1, 1);
        org_zona = "";
        org_poblacion = "";
        des_zona = "";
        des_poblacion = "";
        flujo = "";
        fabrica = "";
        duns = "";
        proveedor = "";
        peso = 0.0;
        volumen = 0.0;
    }
};

class Loader {
public:
    Loader(tntdb::Connection &);
    Loader(const Loader& orig);
    virtual ~Loader();

    int run(int, char **);

private:
    static log4cxx::LoggerPtr logger;
    tntdb::Connection con;

    void borrarDatos(void);
    Aviso * parsearLinea(const std::string &);
    tntdb::Date parsearDate(const std::string &);

};

#endif /* LOADER_H */

