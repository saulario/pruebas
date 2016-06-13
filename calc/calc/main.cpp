#include <cstdlib>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <tntdb/connect.h>
#include <tntdb/connection.h>

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

    tntdb::Connection con = tntdb::connect("mysql:db=vwze;user=vwze;passwd=vwzexx");

    try {
        Loader l(con);
        rv = l.run(argc, argv);
    } catch (std::exception e) {
        LOG4CXX_ERROR(logger, std::string(e.what()));
        rv = 1;
    }

    con.close();
    LOG4CXX_INFO(logger, "<----- Fin");

    return rv;
}

