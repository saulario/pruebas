#include <list>
#include <log4cxx/logger.h>
#include <tntdb/result.h>
#include <tntdb/statement.h>

#include "Tarificador.h"
#include "vwze_dao.h"
#include "Math.h"

log4cxx::LoggerPtr Tarificador::logger = log4cxx::Logger::getLogger("Tarificador");

Tarificador::Tarificador(tntdb::Connection & con_) : con(con_) {
}

Tarificador::~Tarificador() {
    
    for (auto p : zonMap) {
        delete p.second;
    }
    
}

void Tarificador::borrarImportes(int doetip) {
    LOG4CXX_TRACE(logger, "-----> Inicio");
    tntdb::Statement stmt = con.prepare("update doe set doepun = 0, doetot = 0 where doetip = :doetip");
    stmt.setInt("doetip", doetip);
    stmt.execute();
    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Tarificador::cargarMaps(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");
    tntdb::Statement stmt = con.prepare("select * from zon");
    std::list<vwze::entity::Zon*> zonList = vwze::dao::ZonDAO::getInstance()->query(con, stmt);
    for (auto zon : zonList) {
        zonMap.insert(std::pair<std::string, vwze::entity::Zon *>(zon->zoncod, zon));
    }
    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Tarificador::tarificar(void) {
    LOG4CXX_INFO(logger, "-----> Inicio");
    
    cargarMaps();
    tarificarCC();
    
    LOG4CXX_INFO(logger, "<----- Fin");
}

void Tarificador::tarificarCC(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");
    
    borrarImportes(0);
    
    tntdb::Statement stmt = con.prepare("select * from doe where doetip = :doetip");
    stmt.setInt("doetip", 0);
    auto doeList = vwze::dao::DoeDAO::getInstance()->query(con, stmt);
    for (auto doe : doeList) {
        auto zon = zonMap.find(doe->doeorgzon)->second;
        if (zon) {
            doe->doepun = zon->zonman;
            doe->doetot = Math::round(doe->doepun * doe->doepef / 100.0, 2);
            vwze::dao::DoeDAO::getInstance()->update(con, doe);
        }
        delete doe;
    }
    
    LOG4CXX_TRACE(logger, "<----- Fin");
}


