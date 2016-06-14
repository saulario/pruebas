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

    int run(int, char **);

private:
    static log4cxx::LoggerPtr logger;
    tntdb::Connection con;
    
    std::map<std::string, vwze::entity::Pro *> proMap;
    
    void borrarDatos(void);
    vwze::entity::Doc * parsearLinea(const std::string &);
    tntdb::Date parsearDate(const std::string &);

};

#endif /* LOADER_H */

