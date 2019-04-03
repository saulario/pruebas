#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/math/special_functions/round.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <log4cxx/logger.h>
#include <tntdb/result.h>
#include <tntdb/row.h>


#include "ParserTarifa.h"
#include "vwze_entity.h"
#include "vwze_dao.h"

log4cxx::LoggerPtr ParserTarifa::logger = log4cxx::Logger::getLogger("ParserTarifa");

ParserTarifa::ParserTarifa(tntdb::Connection & con_) : con(con_), rfccod(0L), rfdcod(0L) {
    establecerNumeradores();
}

/**
 * Borrado de tarifas en función de una parte de la regla
 * 
 * @param pattern
 */
void ParserTarifa::borrarTarifas(const std::string & pattern) {
    LOG4CXX_INFO(logger, "-----> Inicio");
    LOG4CXX_INFO(logger, "\t(fichero): " + pattern);

    con.prepare("delete from rfd where rfdrfccod in"
            " (select rfccod from rfc where rfcrul like :rfcrul)")
            .setString("rfcrul", pattern)
            .execute();

    con.prepare("delete from rfc where rfcrul like :rfcrul")
            .setString("rfcrul", pattern)
            .execute();

    LOG4CXX_INFO(logger, "<----- Fin");
}

/**
 * Carga el formato estandarizado de tarifa de arrastres
 * 
 * @param fichero
 */
void ParserTarifa::cargarTarifaArrastres(const std::string & fichero) {
    LOG4CXX_INFO(logger, "-----> Inicio");
    LOG4CXX_INFO(logger, "\t(fichero): " + fichero);

    //    borrarTarifas("2:%");
    //    borrarTarifas("-2:%");



    LOG4CXX_INFO(logger, "<----- Fin");
}

/**
 * Carga el formato estandarizado de tarifa de capilar
 * 
 * @param fichero
 */
void ParserTarifa::cargarTarifaCapilar(const std::string & fichero) {
    LOG4CXX_INFO(logger, "-----> Inicio");
    LOG4CXX_INFO(logger, "\t(fichero): " + fichero);

//    borrarTarifas("1:%");
//    borrarTarifas("-1:%");


    std::ifstream infile(fichero);

    std::vector<std::string> linea1;
    std::vector<std::string> linea2;
    std::string linea = "";
    
    rfccod = 50000;
    rfdcod = 50000;

    std::getline(infile, linea);
    boost::algorithm::split(linea1, linea, boost::algorithm::is_any_of(";"));

    std::getline(infile, linea);
    while (!infile.eof()) {
        boost::algorithm::split(linea2, linea, boost::algorithm::is_any_of(";"));

        vwze::entity::Rfc * rfc = new vwze::entity::Rfc;
        rfc->rfccod = ++rfccod;
        rfc->rfcrul = linea2[0];
        rfc->rfcmin = parse(linea2[1]);
        vwze::dao::RfcDAO::getInstance()->insert(con, rfc);

        double mef = 0;
        for (int i = 17; i >= 2; i--) {
            vwze::entity::Rfd * rfd = new vwze::entity::Rfd;
            rfd->rfdcod = ++rfdcod;
            rfd->rfdrfccod = rfc->rfccod;
            rfd->rfdmin = parse(linea1[i]);
            rfd->rfdpun = parse(linea2[i]);
            rfd->rfdmef = mef;
            vwze::dao::RfdDAO::getInstance()->insert(con, rfd);
            
            mef = round(rfd->rfdmin * rfd->rfdpun / 100, 2);
            delete rfd;
        }

        delete rfc;

        LOG4CXX_INFO(logger, "\t\t(line): " + linea);
        std::getline(infile, linea);
    }

    infile.close();

    LOG4CXX_INFO(logger, "<----- Fin");
}

/**
 * Carga el formato estandarizado de tarifa de directos
 * 
 * @param fichero
 */
void ParserTarifa::cargarTarifaDirectos(const std::string & fichero) {
    LOG4CXX_INFO(logger, "-----> Inicio");
    LOG4CXX_INFO(logger, "\t(fichero): " + fichero);

//    borrarTarifas("3:%");
//    borrarTarifas("-3:%");


    std::ifstream infile(fichero);

    std::vector<std::string> linea1;
    std::vector<std::string> linea2;
    std::string linea = "";

    std::getline(infile, linea);
    boost::algorithm::split(linea1, linea, boost::algorithm::is_any_of(";"));
    
    rfdcod = 5000; // ojo con esto

    std::getline(infile, linea);
    while (!infile.eof()) {
        boost::algorithm::split(linea2, linea, boost::algorithm::is_any_of(";"));

        vwze::entity::Rfc * rfc = new vwze::entity::Rfc;
        rfc->rfccod = ++rfccod;
        rfc->rfcrul = linea2[0];
        rfc->rfcmin = 0;            // no hay mínimo, se supone que siempre > 8000
//        vwze::dao::RfcDAO::getInstance()->insert(con, rfc);

        double mef = 0;
        for (int i = 9; i >= 1; i--) {
            vwze::entity::Rfd * rfd = new vwze::entity::Rfd;
            rfd->rfdcod = ++rfdcod;
            rfd->rfdrfccod = boost::lexical_cast<int, std::string>(linea2[0]);
            rfd->rfdmin = parse(linea1[i]);
            rfd->rfdpun = parse(linea2[i]);
            rfd->rfdmef = mef;
            vwze::dao::RfdDAO::getInstance()->insert(con, rfd);
            
            mef = round(rfd->rfdmin * rfd->rfdpun / 100, 2);
            delete rfd;
        }

        delete rfc;

        LOG4CXX_INFO(logger, "\t\t(line): " + linea);
        std::getline(infile, linea);
    }

    infile.close();

    LOG4CXX_INFO(logger, "<----- Fin");
}

/**
 * 
 */
void ParserTarifa::establecerNumeradores(void) {
    LOG4CXX_INFO(logger, "-----> Inicio");

    rfccod = 0;
    tntdb::Result result = con.prepare("select max(rfccod) rfccod from rfc").select();
    for (tntdb::Row r : result) {
        rfccod = r.getUnsignedLong("rfccod");
    }

    rfdcod = 0;
    result = con.prepare("select max(rfdcod) rfdcod from rfd").select();
    for (tntdb::Row r : result) {
        rfdcod = r.getUnsignedLong("rfdcod");
    }

    LOG4CXX_INFO(logger, "<----- Fin");
}

//void ParserTarifa::insertarReglaPlanta(const std::string & linea) {
//    LOG4CXX_INFO(logger, "-----> Inicio");
//
//    std::vector<std::string> fields;
//    boost::algorithm::split(fields, linea, boost::algorithm::is_any_of(";"));
//
//    vwze::entity::Rfc * rfc = new vwze::entity::Rfc;
//    rfc->rfcrul = getReglaPlanta(fields);
//    rfc->rfccod = ++rfccod;
//    vwze::dao::RfcDAO::getInstance()->insert(con, rfc);
//
//    vwze::entity::Rfd * rfd = new vwze::entity::Rfd;
//    rfd->rfdrfccod = rfc->rfccod;
//    rfd->rfdmin = 0;
//    rfd->rfdpun = boost::lexical_cast<double, std::string>(boost::replace_all_copy(fields[4], ",", "."));
//    rfd->rfdcod = ++rfdcod;
//    vwze::dao::RfdDAO::getInstance()->insert(con, rfd);
//    
//    delete rfd;
//    delete rfc;
//    
//    LOG4CXX_INFO(logger, "<----- Fin");
//}

//void ParserTarifa::insertarReglaProveedor(const std::string & linea) {
//    LOG4CXX_INFO(logger, "-----> Inicio");
//
//    std::vector<std::string> fields;
//    boost::algorithm::split(fields, linea, boost::algorithm::is_any_of(";"));
//
//    vwze::entity::Rfc * rfc = new vwze::entity::Rfc;
//
//    rfc->rfcrul = getReglaProveedor(fields);
//    try {
//        rfc->rfcmin = boost::lexical_cast<double, std::string>(boost::replace_all_copy(fields[6], ",", "."));
//    } catch (boost::bad_lexical_cast) {
//        rfc->rfcmin = 0;
//    }
//    try {
//        rfc->rfckmt = boost::lexical_cast<double, std::string>(boost::replace_all_copy(fields[4], ",", "."));
//    } catch (boost::bad_lexical_cast) {
//        rfc->rfckmt = 0;
//    }
//    rfc->rfczon = boost::trim_copy(fields[5]);
//
//    rfc->rfccod = ++rfccod;
//    vwze::dao::RfcDAO::getInstance()->insert(con, rfc);
//
//    vwze::entity::Rfd * rfdAnt = NULL;
//
//    for (int i = 7; i <= 40; i++) {
//        vwze::entity::Rfd * rfd = new vwze::entity::Rfd;
//        rfd->rfdrfccod = rfc->rfccod;
//        rfd->rfdmin = getIntervaloProveedor(i);
//        try {
//            rfd->rfdpun = boost::lexical_cast<double, std::string>(boost::replace_all_copy(fields[i], ",", "."));
//        } catch (boost::bad_lexical_cast) {
//            rfd->rfdpun = 0;
//        }
//        rfd->rfdpun = round(rfd->rfdpun, 2);
//        rfd->rfdcod = ++rfdcod;
//        vwze::dao::RfdDAO::getInstance()->insert(con, rfd);
//
//        if (rfdAnt) {
//            rfdAnt->rfdmef = round(rfd->rfdmin * rfd->rfdpun / 100.0, 2);
//            vwze::dao::RfdDAO::getInstance()->update(con, rfdAnt);
//            delete rfdAnt;
//        }
//        rfdAnt = rfd;
//
//    }
//
//    delete rfc;
//
//    LOG4CXX_INFO(logger, "<----- Fin");
//}

double ParserTarifa::round(const double valor, const unsigned int precision) {
    double aux = pow(10.0, (double) precision);
    double result = boost::math::lround(valor * aux);
    result /= aux;
    return result;
}

/**
 * Parsea tarifa limpiando caracteres especiales
 * 
 * @param str
 * @return 
 */
double ParserTarifa::parse(const std::string & str) {
    std::string retval = boost::replace_all_copy(str, ",", ".");
    retval = boost::replace_all_copy(retval, "\r", "");
    return boost::lexical_cast<double, std::string>(retval);
}

