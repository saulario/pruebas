#include <boost/algorithm/string.hpp>
#include <boost/math/special_functions/round.hpp>
#include <iostream>
#include <log4cxx/logger.h>
#include <tntdb/result.h>
#include <tntdb/row.h>
#include <boost/lexical_cast.hpp>

#include "ParserTarifa.h"
#include "vwze_entity.h"
#include "vwze_dao.h"

log4cxx::LoggerPtr ParserTarifa::logger = log4cxx::Logger::getLogger("ParserTarifa");

ParserTarifa::ParserTarifa(tntdb::Connection & con_) : con(con_), rfccod(0L), rfdcod(0L) {
}

ParserTarifa::~ParserTarifa() {

}

void ParserTarifa::borrarTarifas(void) {
    LOG4CXX_INFO(logger, "-----> Inicio");

    con.prepare("delete from rfd").execute();
    con.prepare("delete from rfc").execute();

    LOG4CXX_INFO(logger, "<----- Fin");
}

void ParserTarifa::insertarReglaPlanta(const std::string & linea) {
    LOG4CXX_INFO(logger, "-----> Inicio");

    std::vector<std::string> fields;
    boost::algorithm::split(fields, linea, boost::algorithm::is_any_of(";"));

    vwze::entity::Rfc * rfc = new vwze::entity::Rfc;
    rfc->rfcrul = getReglaPlanta(fields);
    rfc->rfccod = ++rfccod;
    vwze::dao::RfcDAO::getInstance()->insert(con, rfc);

    vwze::entity::Rfd * rfd = new vwze::entity::Rfd;
    rfd->rfdrfccod = rfc->rfccod;
    rfd->rfdmin = 0;
    rfd->rfdpun = boost::lexical_cast<double, std::string>(boost::replace_all_copy(fields[4], ",", "."));
    rfd->rfdcod = ++rfdcod;
    vwze::dao::RfdDAO::getInstance()->insert(con, rfd);
    
    delete rfd;
    delete rfc;
    
    LOG4CXX_INFO(logger, "<----- Fin");
}

void ParserTarifa::insertarReglaProveedor(const std::string & linea) {
    LOG4CXX_INFO(logger, "-----> Inicio");

    std::vector<std::string> fields;
    boost::algorithm::split(fields, linea, boost::algorithm::is_any_of(";"));

    vwze::entity::Rfc * rfc = new vwze::entity::Rfc;

    rfc->rfcrul = getReglaProveedor(fields);
    try {
        rfc->rfcmin = boost::lexical_cast<double, std::string>(boost::replace_all_copy(fields[6], ",", "."));
    } catch (boost::bad_lexical_cast) {
        rfc->rfcmin = 0;
    }
    try {
        rfc->rfckmt = boost::lexical_cast<double, std::string>(boost::replace_all_copy(fields[4], ",", "."));
    } catch (boost::bad_lexical_cast) {
        rfc->rfckmt = 0;
    }
    rfc->rfczon = boost::trim_copy(fields[5]);

    rfc->rfccod = ++rfccod;
    vwze::dao::RfcDAO::getInstance()->insert(con, rfc);

    vwze::entity::Rfd * rfdAnt = NULL;

    for (int i = 7; i <= 40; i++) {
        vwze::entity::Rfd * rfd = new vwze::entity::Rfd;
        rfd->rfdrfccod = rfc->rfccod;
        rfd->rfdmin = getIntervaloProveedor(i);
        try {
            rfd->rfdpun = boost::lexical_cast<double, std::string>(boost::replace_all_copy(fields[i], ",", "."));
        } catch (boost::bad_lexical_cast) {
            rfd->rfdpun = 0;
        }
        rfd->rfdpun = round(rfd->rfdpun, 2);
        rfd->rfdcod = ++rfdcod;
        vwze::dao::RfdDAO::getInstance()->insert(con, rfd);

        if (rfdAnt) {
            rfdAnt->rfdmef = round(rfd->rfdmin * rfd->rfdpun / 100.0, 2);
            vwze::dao::RfdDAO::getInstance()->update(con, rfdAnt);
            delete rfdAnt;
        }
        rfdAnt = rfd;

    }

    delete rfc;

    LOG4CXX_INFO(logger, "<----- Fin");
}

int ParserTarifa::getIntervaloProveedor(const int i) {
    LOG4CXX_TRACE(logger, "-----> Inicio");
    int result = 0;

    if (i == 8) {
        result = 251;
    } else if (i == 9) {
        result = 501;
    } else if (i == 10) {
        result = 1001;
    } else if (i >= 11) {
        result = (i - 10) * 2500 + 1;
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
    return result;
}

std::string ParserTarifa::getReglaPlanta(const std::vector<std::string> & fields) {
    LOG4CXX_TRACE(logger, "-----> Inicio");
    std::string result = "";

    std::string flujo = boost::trim_copy(fields[3]);
    if (flujo == "WA") {
        result += "-2:";
        result += fields[1] + ":";
        result += fields[2];
    } else if (flujo == "WE") {
        result += "2:";
        result += fields[0] + ":";
        result += fields[1];
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
    return result;
}

std::string ParserTarifa::getReglaProveedor(const std::vector<std::string> & fields) {
    LOG4CXX_TRACE(logger, "-----> Inicio");
    std::string result = "";

    std::string flujo = boost::trim_copy(fields[3]);
    if (flujo == "WA") {
        result += "-1:";
        result += texto2zona(fields[1]) + ":";
        result += fields[2];
    } else if (flujo == "WE") {
        result += "1:";
        result += fields[0] + ":";
        result += texto2zona(fields[1]);
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
    return result;
}

double ParserTarifa::round(const double valor, const unsigned int precision) {
    double aux = pow(10.0, (double) precision);
    double result = boost::math::lround(valor * aux);
    result /= aux;
    return result;
}

std::string ParserTarifa::zona2texto(const std::string & s) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    std::string result = "";
    if (boost::starts_with(s, "DE38")) {
        result = "ZONA 1";
    } else if (boost::starts_with(s, "DE74")) {
        result = "ZONA 2";
    } else if (boost::starts_with(s, "DE59")) {
        result = "ZONA 3";
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
    return result;
}

std::string ParserTarifa::texto2zona(const std::string & s) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    std::string result = "";
    if (boost::starts_with(s, "ZONA 1")) {
        result = "DE38";
    } else if (boost::starts_with(s, "ZONA 2")) {
        result = "DE74";
    } else if (boost::starts_with(s, "ZONA 3")) {
        result = "DE59";
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
    return result;
}


