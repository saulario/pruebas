#include <cstdlib>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

#include "Loader.h"

using namespace std;

static log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger("main");

/*
 * 
 */
int main(int argc, char** argv) {
    int rv = EXIT_SUCCESS;

    log4cxx::PropertyConfigurator::configure("log4cxx.properties");

    LOG4CXX_INFO(logger, "-----> Inicio");

    try {
        Loader l;
        rv = l.run(argc, argv);
    } catch(std::exception e) {
        LOG4CXX_ERROR(logger, std::string(e.what()));
        rv = 1;
    }

    LOG4CXX_INFO(logger, "<----- Fin");

    return rv;
}

