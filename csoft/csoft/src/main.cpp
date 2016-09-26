/*
 * csoft (csoft)
 * Copyright (C) 2016..  Saul Correas Subias 
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/log/core.hpp>
//#include <boost/log/expressions.hpp>
//#include <boost/log/sinks/text_file_backend.hpp>
//#include <boost/log/sources/record_ostream.hpp>
//#include <boost/log/sources/severity_logger.hpp>
//#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
//#include <boost/log/utility/setup/file.hpp>
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
#ifndef LOGDIR
#define LOGDIR "./"
#endif
#ifndef SYSCONFDIR
#define SYSCONFDIR "./"
#endif

void check_log() {
    
    static const char * cdn = R"(
# Core section
[Core]
DisableLogging=false
#Filter="%Severity% >= 0"

#[Sinks.CONSOLE]
#Destination=Console
#Asinchronous=true
#AutoFlush=true
#Format="[%TimeStamp%][%ThreadID%]: %Message%"
#Filter="%Severity% >= 0"

[Sinks.FILE]
Destination=TextFile
Asinchronous=true
AutoFlush=true
FileName="LOGDIR/csoft_%N.log"
#Target="LOGDIR"
Format="[%TimeStamp%][%ThreadID%]: %Message%"
RotationSize="10485760"
RotationTimePoint="00:00:01"
#Filter="%Severity% >= trace"

)";
    
    boost::filesystem::path p(SYSCONFDIR);
    if (!boost::filesystem::exists(p)) {
        std::cerr << "\t\tcreating etc directory..." << std::endl;
        boost::filesystem::create_directory(p);
    }
    
    std::string logger_ini(SYSCONFDIR);
    logger_ini += "/logger.ini";
    boost::filesystem::path p1(logger_ini);
    if (!boost::filesystem::exists(p1)) {
        std::cerr << "\t\tcreating basic logger configuration" << std::endl;
        std::string str = cdn;
        boost::replace_all(str, "LOGDIR", LOGDIR);
        boost::filesystem::ofstream of(p1);
        of << str;
        of.close();
    }    

}

void check_db() {
    
    boost::filesystem::path p(DBDIR);
    if (!boost::filesystem::exists(p)) {
        std::cerr << "\t\tcreating db directory" << std::endl;
        boost::filesystem::create_directory(p);
    }

}
    
void init_log(void) {
    std::string logger_ini(SYSCONFDIR);
    logger_ini += "/logger.ini";

    std::ifstream file(logger_ini, std::ifstream::in);
    boost::log::init_from_stream(file);
    boost::log::add_common_attributes();

}

bool environment_ok() {
    std::cerr << "csoft:\tchecking environment" << std::endl;

    std::cerr << "\tLogger configuration..." << std::endl;
    check_log();
    init_log();

    std::cerr << "\tDatabase storage..." << std::endl;
    check_db();

    return true;
}

boost::log::sources::severity_logger<boost::log::trivial::severity_level> lg;

void signal_handler(int signo) {
    BOOST_LOG_SEV(lg, boost::log::trivial::trace) << ">>>" << __PRETTY_FUNCTION__;
    BOOST_LOG_SEV(lg, boost::log::trivial::trace) << "\t(signo): " << signo;
    exit(signo);
    BOOST_LOG_SEV(lg, boost::log::trivial::trace) << "<<<" << __PRETTY_FUNCTION__;
}

int main(int argc, char **argv) {

    if (!environment_ok()) {
        return EXIT_FAILURE;
    }

    BOOST_LOG_SEV(lg, boost::log::trivial::info) << "---> " << __PRETTY_FUNCTION__;

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

    BOOST_LOG_SEV(lg, boost::log::trivial::info) << "<--- " << __PRETTY_FUNCTION__ << " (retval): " << retval;
    boost::log::core::get()->remove_all_sinks();
    return retval;
}

