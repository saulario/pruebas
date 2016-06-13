#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include <fstream>
#include <iostream>
#include <log4cxx/logger.h>
#include <iostream>
#include <stdlib.h>

#include "Loader.h"

log4cxx::LoggerPtr Loader::logger = log4cxx::Logger::getLogger("Loader");

Loader::Loader(tntdb::Connection & con_) : con(con_) {
}

Loader::Loader(const Loader& orig) {
}

Loader::~Loader() {
}

int Loader::run(int argc, char ** argv) {
    LOG4CXX_INFO(logger, "-----> Inicio");

    std::ifstream infile("vwze.csv");

    std::string line = "";
    int count = 0;

    std::getline(infile, line); // descarta textos
    std::getline(infile, line);
    while (!infile.eof()) {
        ++count;
        Aviso * a = parsearLinea(line);

        if (a) delete a;

        std::getline(infile, line);
        break;
    }

    std::cerr << count << std::endl;
    infile.close();

    LOG4CXX_INFO(logger, "<----- Fin");
}

void Loader::borrarDatos(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");
    
    con.prepare("delete from doc").execute();
    
    con.prepare("delete from pro").execute();
    

    LOG4CXX_TRACE(logger, "<----- Fin");
}

tntdb::Date Loader::parsearDate(const std::string & p) {
    LOG4CXX_TRACE(logger, "-----> Inicio");
    LOG4CXX_TRACE(logger, "\t(p): " + p);
    tntdb::Date d;

    std::vector<std::string> fields;
    boost::algorithm::split(fields, p, boost::algorithm::is_any_of("."));



    LOG4CXX_TRACE(logger, "<----- Fin");
    return d;
}

Aviso * Loader::parsearLinea(const std::string & linea) {
    LOG4CXX_TRACE(logger, "-----> Inicio");
    Aviso * a = NULL;

    std::vector<std::string> fields;
    boost::algorithm::split(fields, linea, boost::algorithm::is_any_of(";"));

    a->relevancia = fields[0];
    a->expedicion = fields[1];



    LOG4CXX_TRACE(logger, "<----- Fin");
    return a;
}