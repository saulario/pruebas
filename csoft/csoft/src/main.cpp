#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <fstream>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "Csoft.h"

#ifndef DBDIR
#define DBDIR "./"
#endif
#ifndef SYSCONFDIR
#define SYSCONFDIR "./"
#endif


void init_log(void) {
    std::string logger_ini(SYSCONFDIR);
    logger_ini += "/logger.ini";
    
    std::ifstream file(logger_ini, std::ifstream::in);
    boost::log::init_from_stream(file);    
    boost::log::add_common_attributes();

}

bool environment_ok() {
    std::cerr << "csoft:\tchecking environment" << std::endl;
    
    std::cerr << "\tLogger configuration...";
    
    init_log();    
    std::cerr << "OK" << std::endl;
    
    std::cerr << "\tDatabase storage...";
    
    std::cerr << "OK" << std::endl;
    
    return true;
}

boost::log::sources::severity_logger<boost::log::trivial::severity_level> lg;

void signal_handler(int signo) {
    BOOST_LOG_SEV(lg, boost::log::trivial::trace) << ">>>" << __PRETTY_FUNCTION__;
    BOOST_LOG_SEV(lg, boost::log::trivial::trace) << "\t(signo): " << signo;
    printf("Signal %d pulsada", signo);
    exit(signo);
    BOOST_LOG_SEV(lg, boost::log::trivial::trace) << "<<<" << __PRETTY_FUNCTION__;
}

int main(int argc, char **argv) {
    
    if (!environment_ok()) {
        return EXIT_FAILURE;
    }
    
    BOOST_LOG_SEV(lg, boost::log::trivial::info) << __PRETTY_FUNCTION__ << "---> Begin";

    if (signal(SIGHUP, signal_handler) == SIG_ERR) {
        printf("Registrando SIGHUP\n");
        return EXIT_FAILURE;
    }
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        printf("Registrando SIGINT\n");
        return EXIT_FAILURE;
    }
    if (signal(SIGTERM, signal_handler) == SIG_ERR) {
        printf("Registrando SIGTERM\n");
        return EXIT_FAILURE;
    }

    csoft::Csoft csoft;
    int retval = csoft.doIt(argc, argv);

    BOOST_LOG_SEV(lg, boost::log::trivial::info) << __PRETTY_FUNCTION__ << "<--- End (retval): " << retval;
    boost::log::core::get()->remove_all_sinks();
    return retval;
}

