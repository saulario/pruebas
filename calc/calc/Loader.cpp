
#include <fstream>
#include <iostream>
#include <log4cxx/logger.h>
#include <iostream>
#include <stdlib.h>

#include "Loader.h"

log4cxx::LoggerPtr Loader::logger = log4cxx::Logger::getLogger("Loader");

Loader::Loader() {
}

Loader::Loader(const Loader& orig) {
}

Loader::~Loader() {
}

int Loader::run(int argc, char ** argv) {
    LOG4CXX_INFO(logger, "-----> Inicio");

    std::string pwd(getenv("PWD"));
    LOG4CXX_DEBUG(logger, "PWD: " + pwd);

    std::ifstream infile("vwze.csv");

    std::string line = "";
    int count = 0;

    while (!infile.eof()) {
        std::getline(infile, line);
        if (!(++count % 1000)) {
            LOG4CXX_DEBUG(logger, line);
        }
    }


    infile.close();



    LOG4CXX_INFO(logger, "<----- Fin");
}

