#ifndef LOADER_H
#define LOADER_H

#include <boost/date_time/gregorian/gregorian.hpp>

class Aviso {
public:
    std::string relevancia;
    std::string expedicion;
    boost::gregorian::date fecha;
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
        fecha = boost::gregorian::date(1, 1, 1);
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
    Loader();
    Loader(const Loader& orig);
    virtual ~Loader();

    int run(int, char **);

private:
    static log4cxx::LoggerPtr logger;
};

#endif /* LOADER_H */

