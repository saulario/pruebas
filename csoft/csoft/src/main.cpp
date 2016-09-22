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
#define DBDIR "."
#endif
#ifndef SYSCONFDIR
#define SYSCONFDIR "."
#endif


void init_log(void) {
    
    std::string logger_ini(SYSCONFDIR);
    logger_ini += "/logger.ini";
    
    std::ifstream file(logger_ini, std::ifstream::in);
    boost::log::init_from_stream(file);    
    
//    boost::log::add_file_log(
//            boost::log::keywords::file_name = "/usr/local/log/csoft_%N.log",
//            boost::log::keywords::rotation_size = 1024 * 1024 * 10,
//            boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
//            boost::log::keywords::format = "[%TimeStamp%][%ThreadID%]: %Message%"
//            );
//    
//    boost::log::core::get()->set_filter(
//            boost::log::trivial::severity >= boost::log::trivial::info
//            );
//    
//    boost::shared_ptr<boost::log::core> core = boost::log::core::get();
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
   
    init_log();
    boost::log::add_common_attributes();
    

    
    BOOST_LOG_SEV(lg, boost::log::trivial::info) << __PRETTY_FUNCTION__ << "---> Begin";

    BOOST_LOG_SEV(lg, boost::log::trivial::trace) << "\ttrace";
    BOOST_LOG_SEV(lg, boost::log::trivial::debug) << "\tdebug";
    BOOST_LOG_SEV(lg, boost::log::trivial::info) << "\tinfo";
    BOOST_LOG_SEV(lg, boost::log::trivial::error) << "\terror";
    BOOST_LOG_SEV(lg, boost::log::trivial::fatal) << "\tfatal";


    if (signal(SIGHUP, signal_handler) == SIG_ERR) {
        printf("Registrando SIGHUP\n");
        return EXIT_FAILURE;
    }
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        printf("Registrando SIGINT\n");
        return EXIT_FAILURE;
    }
    /*
        if (signal(SIGKILL, signal_handler) == SIG_ERR) {
            printf("Registrando SIGKILL\n");
            return EXIT_FAILURE;
        }
     */
    if (signal(SIGTERM, signal_handler) == SIG_ERR) {
        printf("Registrando SIGTERM\n");
        return EXIT_FAILURE;
    }

    //    while(1) {
    //        sleep(1000);
    //        break;
    //    }


    csoft::Csoft csoft;
    int retval = csoft.doIt(argc, argv);

    BOOST_LOG_SEV(lg, boost::log::trivial::info) << "\t(HOME): " << getenv("HOME");



    BOOST_LOG_SEV(lg, boost::log::trivial::info) << __PRETTY_FUNCTION__ << "<--- End (retval): " << retval;
    boost::log::core::get()->remove_all_sinks();
    return retval;
}

