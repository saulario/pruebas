#include <boost/lexical_cast.hpp>
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

    for (auto p : eltMap) {
        delete p.second;
    }
    for (auto p : rfcMap) {
        delete p.second;
    }
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

void Tarificador::cargarEntorno(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    // esta stmt se crea por ganar tiempo

    stmtRegla = con.prepare(" select rfd.* from rfc join rfd on rfd.rfdrfccod = rfc.rfccod "
            " where "
            "       rfc.rfcrul = :rfcrul "
            "   and rfd.rfdmin < :rfcmin "
            " order by rfd.rfdmin desc "
            " limit 1");

    tntdb::Statement stmt = con.prepare("select * from zon");
    std::list<vwze::entity::Zon*> zonList = vwze::dao::ZonDAO::getInstance()->query(con, stmt);
    for (auto zon : zonList) {
        zonMap.insert(std::pair<std::string, vwze::entity::Zon *>(zon->zoncod, zon));
    }

    stmt = con.prepare("select * from rfc");
    std::list<vwze::entity::Rfc *> rfcList = vwze::dao::RfcDAO::getInstance()->query(con, stmt);
    for (auto rfc : rfcList) {
        rfcMap.insert(std::pair<unsigned long, vwze::entity::Rfc *>(rfc->rfccod, rfc));
    }

    stmt = con.prepare("select * from elt");
    std::list<vwze::entity::Elt *> eltList = vwze::dao::EltDAO::getInstance()->query(con, stmt);
    for (auto elt : eltList) {
        eltMap.insert(std::pair<std::string, vwze::entity::Elt *>(elt->eltorg, elt));
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Tarificador::tarificar(void) {
    LOG4CXX_INFO(logger, "-----> Inicio");

    cargarEntorno();
    tarificarTipo(1);
    tarificarTipo(2);
    tarificarTipo(-1);
    tarificarTipo(-2);
    tarificarTipo(3);
    tarificarTipo(-3);

    LOG4CXX_INFO(logger, "<----- Fin");
}

void Tarificador::tarificarCC(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    //    borrarImportes(0);

    tntdb::Statement stmt = con.prepare("select * from doe where doetip = :doetip");
    stmt.setInt("doetip", 0);
    auto doeList = vwze::dao::DoeDAO::getInstance()->query(con, stmt);
    for (auto doe : doeList) {
        if (doe->doetot == 0) {
            auto zon = zonMap.find(doe->doeorgzon)->second;
            if (zon) {
                doe->doepun = zon->zonman;
                doe->doetot = Math::round(doe->doepun * doe->doepef / 100.0, 2);
                vwze::dao::DoeDAO::getInstance()->update(con, doe);
            }
        }
        delete doe;
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Tarificador::tarificarTipo(int tipo) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    tntdb::Statement stmt = con.prepare("select * from doe where doetip = :doetip");
    stmt.setInt("doetip", tipo);
    auto doeList = vwze::dao::DoeDAO::getInstance()->query(con, stmt);
    for (auto doe : doeList) {
        if (doe->doetot == 0) {
            vwze::entity::Rfd * rfd = localizarRegla(doe);
            if (rfd) {
                doe->doepun = rfd->rfdpun;
                doe->doetot = Math::round(doe->doepun * doe->doepef / 100.0, 2);
                // comprobación de máximo
                if (rfd->rfdmef && doe->doetot > rfd->rfdmef) {
                    doe->doepun = 0;
                    doe->doetot = rfd->rfdmef;
                }
                // comprobacón de mínimo
                vwze::entity::Rfc * rfc = rfcMap.find(rfd->rfdrfccod)->second;
                if (rfc->rfcmin && doe->doetot < rfc->rfcmin) {
                    doe->doepun = 0;
                    doe->doetot = rfc->rfcmin;
                }
                delete rfd;
                vwze::dao::DoeDAO::getInstance()->update(con, doe);
            }
        }
        delete doe;
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}

//vwze::entity::Rfd * Tarificador::localizarRegla(const vwze::entity::Doe * doe) {
//    LOG4CXX_TRACE(logger, "-----> Inicio");
//
//    std::string rfcrul = boost::lexical_cast<std::string, int>(doe->doetip)
//            + ":" + doe->doeorgzon + ":" + doe->doedeszon;
//
//    int rfccod = 0;
//    tntdb::Result result = con.prepare("select rfccod from rfc where rfcrul = :rfcrul limit 1")
//            .setString("rfcrul", rfcrul)
//            .select();
//    for (auto row : result) {
//        rfccod = row.getInt64("doecod");
//        break;
//    }
//    if (rfccod == 0) {
//        return NULL;
//    }
//
//    vwze::entity::Rfd * rfd = NULL;
//    
//    tntdb::Statement stmt = con.prepare("select " 
//            + vwze::dao::RfdDAO::getInstance()->getColumns() +
//            " from " 
//            + vwze::dao::RfdDAO::getInstance()->getTable() +
//            " where "
//            " rfdrfccod = :rfdrfccod "
//            " and rfdmin < :rfdmin "
//            " order by rfdmin desc "
//            " limit 1")
//            .setInt("rfdrfccod", rfccod)
//            .setDouble("rfdmin", doe->doepef);
//    
//    auto rfdList = vwze::dao::RfdDAO::getInstance()->query(con, stmt);
//    if (!rfdList.empty()) {
//        rfd = rfdList.front();
//    }
//
//    LOG4CXX_TRACE(logger, "<----- Fin");
//    return rfd;
//}

std::string Tarificador::componerRegla(vwze::entity::Doe * doe) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    std::string orgzon = doe->doeorgzon;
    std::string deszon = doe->doedeszon;

    // traducción de la zona de facturación
    if (doe->doetip > 1) {
        if (eltMap.find(doe->doedeszon) != eltMap.end()) {
            auto elt = eltMap.find(doe->doedeszon)->second;
            deszon = elt->eltdes;
            doe->doedespob = deszon;
        }
    } else if (doe->doetip < -1) {
        if (eltMap.find(doe->doeorgzon) != eltMap.end()) {
            auto elt = eltMap.find(doe->doeorgzon)->second;
            orgzon = elt->eltdes;
            doe->doeorgpob = orgzon;
        }
    }

    std::string regla = "";

    if (doe->doetip == -2) {
        regla = boost::lexical_cast<std::string, int>(abs(doe->doetip))
                + ":" + deszon + ":" + orgzon;
    } else {
        regla = boost::lexical_cast<std::string, int>(doe->doetip)
                + ":" + orgzon + ":" + deszon;
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
    return regla;
}

vwze::entity::Rfd * Tarificador::localizarRegla(vwze::entity::Doe * doe) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    //    std::string rfcrul = boost::lexical_cast<std::string, int>(doe->doetip)
    //            + ":" + doe->doeorgzon + ":" + doe->doedeszon;
    std::string rfcrul = componerRegla(doe);

    vwze::entity::Rfd * rfd = NULL;

    stmtRegla.setString("rfcrul", rfcrul);
    stmtRegla.setDouble("rfcmin", doe->doepef);
    auto rfdList = vwze::dao::RfdDAO::getInstance()->query(con, stmtRegla);
    if (!rfdList.empty()) {
        rfd = rfdList.front();
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
    return rfd;
}


