#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <log4cxx/logger.h>
#include <iostream>
#include <stdlib.h>
#include <tntdb/result.h>
#include <tntdb/error.h>

#include "Loader.h"
#include "vwze_dao.h"
#include "ParserTarifa.h"

log4cxx::LoggerPtr Loader::logger = log4cxx::Logger::getLogger("Loader");

Loader::Loader(tntdb::Connection & con_) : con(con_) {
}

Loader::Loader(const Loader& orig) {
}

Loader::~Loader() {
    for (auto p : proMap) {
        if (p.second) {
            delete p.second;
        }
    }
    for (auto p : zonMap) {
        if (p.second) {
            delete p.second;
        }
    }
}

void Loader::cargarExpediciones(void) {
    LOG4CXX_INFO(logger, "-----> Inicio");

    if (true | false) {
        return;
    }

    borrarDatos();
    cargarMaps();

    //std::ifstream infile("vwze.csv");
    std::ifstream infile("/home/saulario/VWZE/1611_comprobaciones/vwze.csv");

    std::string line = "";

    std::getline(infile, line); // descarta textos
    std::getline(infile, line);
    while (!infile.eof()) {
        vwze::entity::Doc * doc = parsearLinea(line);
        if (doc->docexp.compare("NR239173") > 0) {
            insertarDocumento(doc);
        }
        if (doc) delete doc;
        std::getline(infile, line);
    }

    std::cerr << doccod << std::endl;
    infile.close();

    LOG4CXX_INFO(logger, "<----- Fin");
}

void Loader::cargarTarifas(void) {
    LOG4CXX_INFO(logger, "-----> Inicio");

    ParserTarifa pt(con);
    //    pt.borrarTarifas();
    pt.establecerNumeradores();

    //    cargarTarifasProveedor(pt);
    cargarTarifasPlanta(pt);

    LOG4CXX_INFO(logger, "<----- Fin");
}

void Loader::cargarTarifasPlanta(ParserTarifa & pt) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    std::ifstream infile("cc_plantas_v4.csv");

    std::string line = "";
    //std::getline(infile, line); // descarta textos
    std::getline(infile, line);
    while (!infile.eof()) {
        pt.insertarReglaPlanta(line);
        std::getline(infile, line);
    }

    infile.close();

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Loader::cargarTarifasProveedor(ParserTarifa & pt) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    std::ifstream infile("proveedor_cc_v4.csv");

    std::string line = "";
    std::getline(infile, line);
    while (!infile.eof()) {
        pt.insertarReglaProveedor(line);
        std::getline(infile, line);
    }

    infile.close();

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Loader::calcularAgregados(void) {
    LOG4CXX_INFO(logger, "-----> Inicio");

    doecod = 0;
    tntdb::Result result = con.prepare("select max(doecod) doecod from doe").select();
    for (auto row : result) {
        doecod = row.getInt64("doecod");
        break;
    }

//            calcularAgregadosWA1();
    //    calcularAgregadosWA2();
        calcularAgregadosWA2_camion();
//            calcularAgregadosWE1();
        calcularAgregadosWE2_camion();
    //    calcularManipulaciones();
    // calcularManipulacionesAgregadas();

    LOG4CXX_INFO(logger, "<----- Fin");
}

void Loader::calcularAgregadosWA1(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    //    if (true | false) {
    //        return;
    //    }

    con.prepare("delete from doe where doetip = -1").execute();

    //    std::string sql = "select dodfec, dodflu, dodorgzon, dodorgpob, doddun, dodpro, doddeszon, doddespob"
    //            ", sum(dodpes) p, sum(dodvol) v, count(dodcod) c, sum(dodpef) pf "
    //            " from dod "
    //            " where "
    //            "    dodtip = -1"
    //            " group by dodfec, dodflu, dodorgzon, dodorgpob, doddun, dodpro, doddeszon, doddespob";

    std::string sql = "select dodfec, dodflu, dodrel, dodorgzon, dodorgpob, doddeszon, doddun "
            ", sum(dodpes) p, sum(dodvol) v, count(dodcod) c, sum(dodpef) pf "
            " from dod "
            " where "
            "    dodtip = -1"
            " group by dodfec, dodflu, dodrel, dodorgzon, dodorgpob, doddeszon, doddun";

    tntdb::Result r = con.prepare(sql).select();
    for (auto row : r) {
        vwze::entity::Doe * doe = new vwze::entity::Doe;
        doe->doecod = ++doecod;
        doe->doetip = -1;
        doe->doefec = row.getDate("dodfec");
        doe->doeflu = row.getString("dodflu");
        doe->doeorgzon = row.getString("dodorgzon");
        doe->doeorgpob = row.getString("dodorgpob");
        doe->doedeszon = row.getString("doddeszon");
        //        doe->doedespob = row.getString("doddespob");
        //        doe->doepro = row.getString("dodpro");
        doe->doedun = row.getString("doddun");

        doe->doepro = row.getString("dodrel");

        doe->doepes = row.getDouble("p");
        doe->doevol = row.getDouble("v");
        doe->doecnt = row.getInt64("c");

        double pef = doe->doevol * 250;
        doe->doepef = doe->doepes > pef ? doe->doepes : pef;

        vwze::dao::DoeDAO::getInstance()->insert(con, doe);
        delete doe;
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Loader::calcularAgregadosWA2(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    //    if (true | false) {
    //        return;
    //    }

    con.prepare("delete from doe where doetip = -2").execute();

    std::string sql = "select dodfec, dodflu, dodrel, dodorgzon, dodorgpob, doddeszon, doddespob"
            ", sum(dodpes) p, sum(dodvol) v, count(dodcod) c, sum(dodpef) pf "
            " from dod "
            " where "
            "   dodtip = -2 "
            " group by dodfec, dodflu, dodrel, dodorgzon, dodorgpob, doddeszon, doddespob";

    tntdb::Result r = con.prepare(sql).select();
    for (auto row : r) {
        vwze::entity::Doe * doe = new vwze::entity::Doe;
        doe->doecod = ++doecod;
        doe->doetip = -2;
        doe->doefec = row.getDate("dodfec");
        doe->doeflu = row.getString("dodflu");
        doe->doeorgzon = row.getString("dodorgzon");
        doe->doeorgpob = row.getString("dodorgpob");
        doe->doedeszon = row.getString("doddeszon");
        doe->doedespob = row.getString("doddespob");

        doe->doepro = row.getString("dodrel");

        doe->doepes = row.getDouble("p");
        doe->doevol = row.getDouble("v");
        doe->doecnt = row.getInt64("c");

        double pef = doe->doevol * 250;
        doe->doepef = doe->doepes > pef ? doe->doepes : pef;

        vwze::dao::DoeDAO::getInstance()->insert(con, doe);
        delete doe;
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Loader::calcularAgregadosWA2_camion(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    //    if (true | false) {
    //        return;
    //    }

    con.prepare("delete from doe where doetip = -2").execute();

    auto dodDao = vwze::dao::DodDAO::getInstance();

    std::string sql = "select " + dodDao->getColumns()
            + " from " + dodDao->getTable()
            + " where "
            + " dodtip = :dodtip "
            + " order by dodfec, dodrel, dodorgzon, doddeszon ";


    tntdb::Statement stmt = con.prepare(sql)
            .setInt("dodtip", -2);
    auto dodList = dodDao->query(con, stmt);

    std::string docs = "\t";

    bool primero = true;
    vwze::entity::Doe * doe = new vwze::entity::Doe;

    for (vwze::entity::Dod * dod : dodList) {

        if (primero) {
            primero ^= primero;
            doe->doetip = -2;
            doe->doefec = dod->dodfec;
            doe->doeorgzon = dod->dodorgzon;
            doe->doeorgpob = dod->dodorgpob;
            doe->doedeszon = dod->doddeszon;
            doe->doeflu = dod->dodflu;
            doe->doepro = dod->dodrel;

            docs += dod->dodexp;
        }

        double limitePeso = 18000;
        double limiteVolumen = 99999;
        //double peso = doe->doepes + dod->dodpes;

        double peso = doe->doepef + dod->dodpef;
        double volumen = doe->doevol + dod->dodvol;

        bool exceso = false;
        if (peso > limitePeso | volumen > limiteVolumen) {
            exceso = true;
        }

        if (doe->doefec != dod->dodfec
                || doe->doeorgzon != dod->dodorgzon
                || doe->doedeszon != dod->doddeszon
                || doe->doepro != dod->dodrel
                || exceso) {

            doe->doecod = ++doecod;
            double pef = doe->doevol * 250;
            doe->doepef = doe->doepes > pef ? doe->doepes : pef;
            vwze::dao::DoeDAO::getInstance()->insert(con, doe);

            std::string message = "\tInsertando transporte " + boost::lexical_cast<std::string, long>(doe->doecod)
                    + ":" + docs;
            LOG4CXX_INFO(logger, message);
            delete doe;

            doe = new vwze::entity::Doe;
            doe->doetip = -2;
            doe->doefec = dod->dodfec;
            doe->doeorgzon = dod->dodorgzon;
            doe->doeorgpob = dod->dodorgpob;
            doe->doedeszon = dod->doddeszon;
            doe->doeflu = dod->dodflu;

            doe->doepro = dod->dodrel;

            docs = "\t";
        }

        doe->doecnt++;
        doe->doepes += dod->dodpes;
        doe->doepef += dod->dodpef;
        doe->doevol += dod->dodvol;

        docs += ":" + dod->dodexp;

    }

    doe->doecod = ++doecod;
    double pef = doe->doevol * 250;
    doe->doepef = doe->doepes > pef ? doe->doepes : pef;
    vwze::dao::DoeDAO::getInstance()->insert(con, doe);
    delete doe;

    LOG4CXX_TRACE(logger, "<----- Fin");
}

/**
 * Recogidas de proveedor a CC
 */
void Loader::calcularAgregadosWE1(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    //    if (true | false) {
    //        return;
    //    }

    con.prepare("delete from doe where doetip = 1").execute();

    // " group by dodfec, dodflu, dodrel, dodorgzon, dodorgpob, doddeszon, doddun";        

    std::string sql = "select dodfec, dodflu, dodrel, dodorgzon, doddun, doddeszon, doddespob "
            ", sum(dodpes) p, sum(dodvol) v, count(dodcod) c, sum(dodpef) pf "
            " from dod "
            " where "
            "    dodtip = 1"
            " group by dodfec, dodflu, dodrel, dodorgzon, doddun, doddeszon, doddespob ";

    tntdb::Result r = con.prepare(sql).select();
    for (auto row : r) {
        vwze::entity::Doe * doe = new vwze::entity::Doe;
        doe->doecod = ++doecod;
        doe->doetip = 1;
        doe->doefec = row.getDate("dodfec");
        doe->doeflu = row.getString("dodflu");
        doe->doeorgzon = row.getString("dodorgzon");
        //doe->doeorgpob = row.getString("dodorgpob");
        doe->doedeszon = row.getString("doddeszon");
        doe->doedespob = row.getString("doddespob");
        //doe->doepro = row.getString("dodpro");
        doe->doedun = row.getString("doddun");

        doe->doepro = row.getString("dodrel");

        doe->doepes = row.getDouble("p");
        doe->doevol = row.getDouble("v");
        doe->doecnt = row.getInt64("c");

        double pef = doe->doevol * 250;
        doe->doepef = doe->doepes > pef ? doe->doepes : pef;

        vwze::dao::DoeDAO::getInstance()->insert(con, doe);
        delete doe;
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}

/**
 * Entregas de CC a planta
 */
void Loader::calcularAgregadosWE2(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    //    if (true | false) {
    //        return;
    //    }

    con.prepare("delete from doe where doetip = 2").execute();

    std::string sql = "select dodfec, dodflu, dodorgzon, dodorgpob, doddeszon, doddespob"
            ", sum(dodpes) p, sum(dodvol) v, count(dodcod) c, sum(dodpef) pf "
            " from dod "
            " where "
            "   dodtip = 2 "
            " group by dodfec, dodflu, dodorgzon, dodorgpob, doddeszon, doddespob";

    tntdb::Result r = con.prepare(sql).select();
    for (auto row : r) {
        vwze::entity::Doe * doe = new vwze::entity::Doe;
        doe->doecod = ++doecod;
        doe->doetip = 2;
        doe->doefec = row.getDate("dodfec");
        doe->doeflu = row.getString("dodflu");
        doe->doeorgzon = row.getString("dodorgzon");
        doe->doeorgpob = row.getString("dodorgpob");
        doe->doedeszon = row.getString("doddeszon");
        doe->doedespob = row.getString("doddespob");

        doe->doepes = row.getDouble("p");
        doe->doevol = row.getDouble("v");
        doe->doecnt = row.getInt64("c");

        double pef = doe->doevol * 250;
        doe->doepef = doe->doepes > pef ? doe->doepes : pef;

        vwze::dao::DoeDAO::getInstance()->insert(con, doe);
        delete doe;
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}

/**
 * Entregas de CC a planta
 */
void Loader::calcularAgregadosWE2_camion(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    //    if (true | false) {
    //        return;
    //    }

    con.prepare("delete from doe where doetip = 2").execute();

    auto dodDao = vwze::dao::DodDAO::getInstance();

    std::string sql = "select " + dodDao->getColumns()
            + " from " + dodDao->getTable()
            + " where "
            + " dodtip = :dodtip "
            + " order by dodfec, dodrel, dodorgzon, doddeszon ";


    tntdb::Statement stmt = con.prepare(sql)
            .setInt("dodtip", 2);
    auto dodList = dodDao->query(con, stmt);

    std::string docs = "\t";

    bool primero = true;
    vwze::entity::Doe * doe = new vwze::entity::Doe;

    for (vwze::entity::Dod * dod : dodList) {

        if (primero) {
            primero ^= primero;
            doe->doetip = 2;
            doe->doefec = dod->dodfec;
            doe->doeorgzon = dod->dodorgzon;
            doe->doeorgpob = dod->dodorgpob;
            doe->doedeszon = dod->doddeszon;
            doe->doeflu = dod->dodflu;
            doe->doepro = dod->dodrel;

            docs += dod->dodexp;
        }

        /*
         * Si pasa de 27000 no puede agregar la carga actual. VW optimiza, pero
         * ahora nosotros no tenemos tiempo para llegar a plazo
         */

        double limitePeso = 18000;
        double limiteVolumen = 99999;
        //double peso = doe->doepes + dod->dodpes;

        double peso = doe->doepef + dod->dodpef;
        double volumen = doe->doevol + dod->dodvol;

        bool exceso = false;
        if (peso > limitePeso | volumen > limiteVolumen) {
            exceso = true;
        }

        if (doe->doefec != dod->dodfec
                || doe->doeorgzon != dod->dodorgzon
                || doe->doedeszon != dod->doddeszon
                || doe->doepro != dod->dodrel
                || exceso) {

            doe->doecod = ++doecod;
            double pef = doe->doevol * 250;
            doe->doepef = doe->doepes > pef ? doe->doepes : pef;
            vwze::dao::DoeDAO::getInstance()->insert(con, doe);

            std::string message = "\tInsertando transporte " + boost::lexical_cast<std::string, long>(doe->doecod)
                    + ":" + docs;
            LOG4CXX_INFO(logger, message);
            delete doe;

            doe = new vwze::entity::Doe;
            doe->doetip = 2;
            doe->doefec = dod->dodfec;
            doe->doeorgzon = dod->dodorgzon;
            doe->doeorgpob = dod->dodorgpob;
            doe->doedeszon = dod->doddeszon;
            doe->doeflu = dod->dodflu;

            doe->doepro = dod->dodrel;

            docs = "\t";
        }

        doe->doecnt++;
        doe->doepes += dod->dodpes;
        doe->doepef += dod->dodpef;
        doe->doevol += dod->dodvol;

        docs += ":" + dod->dodexp;

    }

    doe->doecod = ++doecod;
    double pef = doe->doevol * 250;
    doe->doepef = doe->doepes > pef ? doe->doepes : pef;
    vwze::dao::DoeDAO::getInstance()->insert(con, doe);
    delete doe;

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Loader::calcularManipulaciones(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    //    if (true | false) {
    //        return;
    //    }

    con.prepare("delete from doe where doetip = 0").execute();

    std::string sql = "select doc.* , zon.* from doc "
            "   join zoo on zoopcp = docdeszon "
            "   join zon on zoncod = zoozoncod "
            " where docflu = 'WA' and docpef between 70 and 6000 "
            " union"
            " select doc.*, zon.* from doc "
            "   join zoo on zoopcp = docorgzon"
            "   join zon on zoncod = zoozoncod "
            " where docflu = 'WE' and docpef between 70 and 6000";

    //    std::string sql = "select doc.*, zoncod from doc "
    //            " join zoo on zoopcp = docorgzon "
    //            " join zon on zoncod = zoozoncod "
    //            " where  docpef <= 6000 ";

    tntdb::Result result = con.prepare(sql).select();
    for (tntdb::Row row : result) {
        vwze::entity::Doe * doe = new vwze::entity::Doe;
        doe->doecod = ++doecod;
        doe->doetip = 0;
        doe->doefec = row.getDate("docfec");
        doe->doeflu = row.getString("docflu");
        doe->doeexp = row.getString("docexp");
        doe->doedun = row.getString("docdun");
        doe->doepro = row.getString("docpro");
        doe->doedun = row.getString("docdun");

        doe->doeorgzon = row.getString("zoncod");
        doe->doeorgpob = row.getString("zondes");
        doe->doedeszon = row.getString("zoncod");
        doe->doedespob = row.getString("zondes");

        doe->doepes = row.getDouble("docpes");
        doe->doevol = row.getDouble("docvol");
        doe->doepef = row.getDouble("docpef");
        doe->doecnt = 1;

        std::string zoncod = row.getString("zoncod");
        if (zoncod.compare("DE38") == 0) {
            doe->doepun = 1.96;
        } else if (zoncod.compare("DE59") == 0) {
            doe->doepun = 1.49;
        } else if (zoncod.compare("DE74") == 0) {
            doe->doepun = 1.62;
        }

        doe->doetot = doe->doepef * doe->doepun / 100;


        if (doe->doeflu.compare("WA") == 0) {
            LOG4CXX_TRACE(logger, "     AQUÍ ESTOY");
        }

        vwze::dao::DoeDAO::getInstance()->insert(con, doe);
        delete doe;
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Loader::calcularManipulacionesAgregadas(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    cargarMaps();

    con.prepare("delete from doe where doetip = 0").execute();
    con.prepare("delete from dof where doftip = 0").execute();

    unsigned long doecod = 0;
    try {
        doecod = con.prepare("select max(doecod) from doe").selectValue()
                .getUnsignedLong();
    } catch (tntdb::NotFound) {
        doecod = 0;
    }
    doecod++; // debe ir preincrementado por las inserciones en dof

    unsigned long dofcod = 0;
    try {
        dofcod = con.prepare("select max(dofcod) from dof").selectValue()
                .getUnsignedLong();
    } catch (tntdb::NotFound) {
        dofcod = 0;
    }

    tntdb::Statement psInsert = con.prepare("insert into dof values"
            "(:dofcod, :doftip, :dofdoecod, :dofexp)");

    bool primero = true;
    vwze::entity::Doe * doe = new vwze::entity::Doe;

    std::string sql = "select " + vwze::dao::DocDAO::getInstance()->getColumns()
            + " from " + vwze::dao::DocDAO::getInstance()->getTable()
            + " where "
            + " docpef <= :docpef "
            + " order by docflu, docfec, docrel, docdun, docfab";
    tntdb::Statement stmt = con.prepare(sql).setDouble("docpef", 6000);
    auto docList = vwze::dao::DocDAO::getInstance()->query(con, stmt);
    for (vwze::entity::Doc * doc : docList) {

        if (primero) {
            primero = false;
            doe->doetip = 0;
            doe->doeflu = doc->docflu;
            doe->doefec = doc->docfec;
            doe->doepro = doc->docrel;
            doe->doedun = doc->docdun;
            doe->doeexp = doc->docfab;
        }

        if (doe->doeflu != doc->docflu
                || doe->doefec != doc->docfec
                || doe->doepro != doc->docrel
                || doe->doedun != doc->docdun
                || doe->doeexp != doc->docfab) {

            vwze::entity::Zon * zon = NULL;
            if (doe->doeflu == "WE") {
                zon = zonMap.find(doe->doeorgzon)->second;
            } else if (doe->doeflu == "WA") {
                zon = zonMap.find(doe->doedeszon)->second;
            }
            doe->doeorgzon = doe->doedeszon = zon->zoncod;
            doe->doeorgpob = doe->doedespob = zon->zondes;

            doe->doecod = doecod++;
            double pef = doe->doevol * 250;
            doe->doepef = doe->doepes > pef ? doe->doepes : pef;

            if (doe->doeorgzon.compare("DE38") == 0) {
                doe->doepun = 1.96;
            } else if (doe->doeorgzon.compare("DE59") == 0) {
                doe->doepun = 1.49;
            } else if (doe->doeorgzon.compare("DE74") == 0) {
                doe->doepun = 1.62;
            }

            if (doe->doepef <= 6000) {
                doe->doetot = doe->doepef * doe->doepun / 100;
            }
            vwze::dao::DoeDAO::getInstance()->insert(con, doe);

            delete doe;

            doe = new vwze::entity::Doe;
            doe->doetip = 0;
            doe->doeflu = doc->docflu;
            doe->doefec = doc->docfec;
            doe->doepro = doc->docrel;
            doe->doedun = doc->docdun;
            doe->doeexp = doc->docfab;

        }

        doe->doeorgzon = doc->docorgzon;
        doe->doedeszon = doc->docdeszon;

        doe->doepes += doc->docpes;
        doe->doevol += doc->docvol;
        doe->doecnt++;

        psInsert
                .setInt64("dofcod", ++dofcod)
                .setInt64("dofdoecod", doecod)
                .setInt("doftip", doe->doetip)
                .setString("dofexp", doc->docexp)
                .execute();

    }

    vwze::entity::Zon * zon = NULL;
    if (doe->doeflu == "WE") {
        zon = zonMap.find(doe->doeorgzon)->second;
    } else if (doe->doeflu == "WA") {
        zon = zonMap.find(doe->doedeszon)->second;
    }
    doe->doeorgzon = doe->doedeszon = zon->zoncod;
    doe->doeorgpob = doe->doedespob = zon->zondes;

    doe->doecod = doecod++;
    double pef = doe->doevol * 250;
    if (doe->doepef <= 6000) {
        doe->doepef = doe->doepes > pef ? doe->doepes : pef;
    }

    if (doe->doeorgzon.compare("DE38") == 0) {
        doe->doepun = 1.96;
    } else if (doe->doeorgzon.compare("DE59") == 0) {
        doe->doepun = 1.49;
    } else if (doe->doeorgzon.compare("DE74") == 0) {
        doe->doepun = 1.62;
    }

    doe->doetot = doe->doepef * doe->doepun / 100;

    vwze::dao::DoeDAO::getInstance()->insert(con, doe);

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Loader::borrarDatos(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    con.prepare("delete from doe").execute();
    con.prepare("delete from dod").execute();
    con.prepare("delete from doc").execute();

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Loader::cargarMaps(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    // inicializando códigos
    doccod = 0;
    tntdb::Result result = con.prepare("select max(doccod) doccod from doc").select();
    for (auto row : result) {
        doccod = row.getInt64("doccod");
        break;
    }
    dodcod = 0;
    result = con.prepare("select max(dodcod) dodcod from dod").select();
    for (auto row : result) {
        dodcod = row.getInt64("dodcod");
        break;
    }

    tntdb::Statement stmt = con.prepare("select zoopcp, zoncod from zon join zoo on zoozoncod = zoncod");
    for (tntdb::Row row : stmt.select()) {
        std::string zoopcp = row.getString(0);
        std::string zoncod = row.getString(1);
        zonMap.insert(std::pair<std::string, vwze::entity::Zon *>(zoopcp,
                vwze::dao::ZonDAO::getInstance()->read(con, zoncod)));
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Loader::insertarDocumento(vwze::entity::Doc * doc) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    // sólo comprometidos
    //    if (!boost::starts_with(doc->docrel, "Pflicht")) {
    //        LOG4CXX_TRACE(logger, "<----- Return 1");
    //        return;
    //    }

    // sólo zonas tarificadas
    //    if (zonMap.find(doc->docorgzon) == zonMap.end()) {
    //        LOG4CXX_TRACE(logger, "<----- Return 2");
    //        return;
    //    }

    doc->doccod = ++doccod;
    vwze::dao::DocDAO::getInstance()->insert(con, doc);

    if (boost::starts_with(doc->docflu, "WE")) {
        insertarDocumentosWE(doc);
    } else if (boost::starts_with(doc->docflu, "WA")) {
        insertarDocumentosWA(doc);
    } else {
        LOG4CXX_WARN(logger, "\tIgnorando documento " + doc->docexp + " flujo desconocido");
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}

/**
 * Estos siempre se dividen entre dos tramos
 * 
 *  1. planta y cc
 *  2. cc y proveedor
 * 
 * @param doc
 */
void Loader::insertarDocumentosWA(vwze::entity::Doc * doc) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    vwze::entity::Zon * zon = zonMap.find(doc->docdeszon)->second;

    vwze::entity::Dod * dod = new vwze::entity::Dod;

    dod->dodrel = doc->docrel;
    dod->dodexp = doc->docexp;
    dod->dodfec = doc->docfec;

    dod->dodflu = doc->docflu;
    dod->dodfab = doc->docfab;
    dod->doddun = doc->docdun;
    dod->dodpro = doc->docpro;
    dod->dodpes = doc->docpes;
    dod->dodvol = doc->docvol;
    dod->dodpef = doc->docpef;

    dod->dodorgzon = doc->docorgzon;
    dod->dodorgpob = doc->docorgpob;
    if (!doc->dockcc.empty()) {
        dod->dodorgzon = doc->dockcc;
        dod->dodorgpob = getKccDescripcion(doc->dockcc);
    }

    dod->doddeszon = zon->zoncod;
    dod->doddespob = zon->zondes;

    dod->dodcod = ++dodcod;
    dod->dodtip = -2;
    vwze::dao::DodDAO::getInstance()->insert(con, dod);

    dod->dodorgzon = zon->zoncod;
    dod->dodorgpob = zon->zondes;
    dod->doddeszon = doc->docdeszon;
    dod->doddespob = doc->docdespob;

    dod->dodcod = ++dodcod;
    dod->dodtip = -1;
    vwze::dao::DodDAO::getInstance()->insert(con, dod);

    delete dod;

    LOG4CXX_TRACE(logger, "<----- Fin");
}

/**
 * Estos siempre se dividen entre dos tramos
 * 
 *  1. proveedor y cc
 *  2. cc y planta
 * 
 * @param doc
 */
void Loader::insertarDocumentosWE(vwze::entity::Doc * doc) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    if (zonMap.find(doc->docorgzon) == zonMap.end()) {
        LOG4CXX_DEBUG(logger, "     " + doc->docorgzon + " no encontrado");
    }
    vwze::entity::Zon * zon = zonMap.find(doc->docorgzon)->second;

    vwze::entity::Dod * dod = new vwze::entity::Dod;

    dod->dodrel = doc->docrel;
    dod->dodexp = doc->docexp;
    dod->dodfec = doc->docfec;

    dod->dodflu = doc->docflu;
    dod->dodfab = doc->docfab;
    dod->doddun = doc->docdun;
    dod->dodpro = doc->docpro;
    dod->dodpes = doc->docpes;
    dod->dodvol = doc->docvol;
    dod->dodpef = doc->docpef;

    dod->dodorgzon = doc->docorgzon;
    dod->dodorgpob = doc->docorgpob;
    dod->doddeszon = zon->zoncod;
    dod->doddespob = zon->zondes;

    dod->dodcod = ++dodcod;
    dod->dodtip = 1;
    vwze::dao::DodDAO::getInstance()->insert(con, dod);

    dod->dodorgzon = zon->zoncod;
    dod->dodorgpob = zon->zondes;
    dod->doddeszon = doc->docdeszon;
    dod->doddespob = doc->docdespob;
    if (!doc->dockcc.empty()) {
        dod->doddeszon = doc->dockcc;
        dod->doddespob = getKccDescripcion(doc->dockcc);
    }

    dod->dodcod = ++dodcod;
    dod->dodtip = 2;
    vwze::dao::DodDAO::getInstance()->insert(con, dod);

    delete dod;

    LOG4CXX_TRACE(logger, "<----- Fin");
}

tntdb::Date Loader::parsearDate(const std::string & p) {
    LOG4CXX_TRACE(logger, "-----> Inicio");
    LOG4CXX_TRACE(logger, "\t(p): " + p);
    tntdb::Date d;

    std::vector<std::string> fields;
    boost::algorithm::split(fields, p, boost::algorithm::is_any_of("."));

    if (fields.size() < 3) {
        LOG4CXX_DEBUG(logger, "\t(p): " + p + " error");
    }

    unsigned short dd = boost::lexical_cast<unsigned short, std::string>(fields[0]);
    unsigned short mm = boost::lexical_cast<unsigned short, std::string>(fields[1]);
    unsigned short aa = boost::lexical_cast<unsigned short, std::string>(fields[2]);

    d = tntdb::Date(aa, mm, dd);

    LOG4CXX_TRACE(logger, "<----- Fin");
    return d;
}

double Loader::parsearDouble(const std::string & p) {
    LOG4CXX_TRACE(logger, "-----> Inicio");
    LOG4CXX_TRACE(logger, "\t(p): " + p);

    double d = boost::lexical_cast<double, std::string>(boost::replace_all_copy(p, ",", "."));

    LOG4CXX_TRACE(logger, "<----- Fin");
    return d;
}

/**
 * 0 - Urgencia
 * 1 - Expedición
 * 2 - Fecha
 * 7 - Zona origen
 * 10 - Población origen
 * 13 - Zona destino
 * 14 - Población destino
 * 17 - Tipo de flujo
 * 18 - DUNS
 * 19 - Fábrica
 * 20 - Peso bruto
 * 21 - Volumen
 * 22 - Peso facturable
 * 28 - Nombre proveedor
 * 
 * @param linea
 * @return 
 */
vwze::entity::Doc * Loader::parsearLinea(const std::string & linea) {
    LOG4CXX_TRACE(logger, "-----> Inicio");
    vwze::entity::Doc * doc = new vwze::entity::Doc;

    std::vector<std::string> fields;
    boost::algorithm::split(fields, linea, boost::algorithm::is_any_of(";"));

    doc->docrel = boost::replace_all_copy(boost::trim_copy(fields[0]), "\"", "");
    doc->docexp = fields[1];
    doc->docfec = parsearDate(fields[2]);
    doc->docorgzon = fields[7];
    doc->docorgpob = boost::replace_all_copy(boost::trim_copy(fields[10]), "\"", "");
    doc->docdeszon = fields[13];
    doc->docdespob = boost::replace_all_copy(boost::trim_copy(fields[14]), "\"", "");
    doc->docflu = boost::trim_copy(fields[17]);
    doc->docfab = boost::replace_all_copy(boost::trim_copy(fields[19]), "\"", "");
    doc->docdun = boost::replace_all_copy(boost::trim_copy(fields[18]), "\"", "");
    doc->docpro = boost::replace_all_copy(boost::trim_copy(fields[28]), "\"", "");
    doc->dockcc = getKccCodigo(boost::trim_copy(fields[26]));

    doc->docpes = parsearDouble(fields[20]);
    doc->docvol = parsearDouble(fields[21]);
    doc->docpef = parsearDouble(fields[22]);

    LOG4CXX_TRACE(logger, "<----- Fin");
    return doc;
}

/**
 * Direkt.............
 * Heilbronn.......... DE74
 * Ingolstadt......... DE85
 * Kassel............. DE34
 * nicht im Netzwerk . N/A, queda en blanco 
 *  
 * @param p
 * @return 
 */
std::string Loader::getKccCodigo(const std::string & p) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    std::string result = "";
    if (boost::starts_with(p, "Heilbronn")) {
        result = "DE74";
    } else if (boost::starts_with(p, "Ingolstadt")) {
        result = "DE85";
    } else if (boost::starts_with(p, "Kassel")) {
        result = "DE34";
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
    return result;
}

std::string Loader::getKccDescripcion(const std::string & p) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    std::string result = "";
    if (boost::starts_with(p, "DE74")) {
        result = "Heilbronn";
    } else if (boost::starts_with(p, "DE85")) {
        result = "Ingolstadt";
    } else if (boost::starts_with(p, "DE34")) {
        result = "Kassel";
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
    return result;
}

void Loader::reconstruirDocumentos(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    cargarMaps();
    auto docDao = vwze::dao::DocDAO::getInstance();

    tntdb::Statement stmt = con.prepare("select "
            + docDao->getColumns()
            + " from doc where "
            " docexp > :docexp"
            " order by docexp")
            .setString("docexp", "");
    auto docList = docDao->query(con, stmt);
    for (vwze::entity::Doc * doc : docList) {

        std::string zona = "";
        if (doc->docflu.compare("WE") == 0) {
            zona = doc->docorgzon;
        } else if (doc->docflu.compare("WA") == 0) {
            zona = doc->docdeszon;
        }
        if (zonMap.find(zona) == zonMap.end()) {
            LOG4CXX_WARN(logger, "\tIgnorando documento " + doc->docexp + ", " + zona + " zona desconocida");
            continue;
        }

        if (boost::starts_with(doc->docflu, "WE")) {
            insertarDocumentosWE(doc);
        } else if (boost::starts_with(doc->docflu, "WA")) {
            insertarDocumentosWA(doc);
        } else {
            LOG4CXX_WARN(logger, "\tIgnorando documento " + doc->docexp + " flujo desconocido");
        }

        LOG4CXX_INFO(logger, "     " + doc->docexp + " OK");
    }
    for (auto doc : docList) {
        delete doc;
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Loader::calcularAgregadosWA1_VW(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    if (true | false) {
        return;
    }

    con.prepare("delete from doe where doetip = -1").execute();

    //    std::string sql = "select dodfec, dodflu, dodorgzon, dodorgpob, doddun, dodpro, doddeszon, doddespob"
    //            ", sum(dodpes) p, sum(dodvol) v, count(dodcod) c, sum(dodpef) pf "
    //            " from dod "
    //            " where "
    //            "    dodtip = -1"
    //            " group by dodfec, dodflu, dodorgzon, dodorgpob, doddun, dodpro, doddeszon, doddespob";

    std::string sql = "select transport_id dodorgpob, "
            " min(zoozoncod) dodorgzon, min(docdeszon) doddeszon, min(docfec) dodfec, "
            " count(distinct docexp) c, sum(docpes) p , sum(docvol) v, sum(docpef) doddespob, "
            " count(distinct zoozoncod) dodpro, count(distinct docdeszon) doddun "
            " from auftrage "
            " join doc on doc.docexp = envio "
            " join zoo on zoo.zoopcp = docdeszon "
            " where "
            " tipo = 'Sammelgut' and flujo = 'WA' "
            " group by 1"
            " order by transport_id";

    tntdb::Result r = con.prepare(sql).select();
    for (auto row : r) {
        vwze::entity::Doe * doe = new vwze::entity::Doe;
        doe->doecod = ++doecod;
        doe->doetip = -1;
        doe->doefec = row.getDate("dodfec");
        doe->doeflu = "WA";
        doe->doeorgzon = row.getString("dodorgzon");
        doe->doeorgpob = row.getString("dodorgpob");
        doe->doedeszon = row.getString("doddeszon");
        doe->doedespob = row.getString("doddespob");
        doe->doepro = row.getString("dodpro");
        doe->doedun = row.getString("doddun");
        //        doe->doeexp = row.getString("dodrel");

        doe->doepes = row.getDouble("p");
        doe->doevol = row.getDouble("v");
        doe->doecnt = row.getInt64("c");

        double pef = doe->doevol * 250;
        doe->doepef = doe->doepes > pef ? doe->doepes : pef;
        //doe->doepef = row.getDouble("pf");

        vwze::dao::DoeDAO::getInstance()->insert(con, doe);
        delete doe;

        LOG4CXX_INFO(logger, "\t" + doe->doeorgpob + " OK");
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Loader::calcularAgregadosWA2_VW(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    //    if (true | false) {
    //        return;
    //    }

    con.prepare("delete from doe where doetip = -2").execute();

    //    std::string sql = "select dodfec, dodflu, dodorgzon, dodorgpob, doddeszon, doddespob"
    //            ", sum(dodpes) p, sum(dodvol) v, count(dodcod) c, sum(dodpef) pf "
    //            " from dod "
    //            " where "
    //            "   dodtip = -2 "
    //            " group by dodfec, dodflu, dodorgzon, dodorgpob, doddeszon, doddespob";

    std::string sql = R"SQL(
select transport_id dodorgpob, 
        min(docdeszon) dodorgzon, min(zoozoncod) doddeszon,
        min(docfec) dodfec,
        count(distinct docexp) c, sum(docpes) p, sum(docvol) v, sum(docpef) doddespob,
    count(distinct docdeszon) dodpro, count(distinct zoozoncod) doddun    
    from auftrage 
                join doc on doc.docexp = envio
        join zoo on zoo.zoopcp = docorgzon
    where 
                tipo = 'Hauptlauf' and flujo = 'WA'
group by 1)SQL";

    tntdb::Result r = con.prepare(sql).select();
    for (auto row : r) {
        vwze::entity::Doe * doe = new vwze::entity::Doe;
        doe->doecod = ++doecod;
        doe->doetip = -2;
        doe->doefec = row.getDate("dodfec");
        doe->doeflu = "WA";
        doe->doeorgzon = row.getString("dodorgzon");
        doe->doeorgpob = row.getString("dodorgpob");
        doe->doedeszon = row.getString("doddeszon");
        doe->doedespob = row.getString("doddespob");
        doe->doepro = row.getString("dodpro");
        doe->doedun = row.getString("doddun");


        //        doe->doeexp = row.getString("dodrel");

        doe->doepes = row.getDouble("p");
        doe->doevol = row.getDouble("v");
        doe->doecnt = row.getInt64("c");

        double pef = doe->doevol * 250;
        doe->doepef = doe->doepes > pef ? doe->doepes : pef;
        //        doe->doepef = row.getDouble("pf");

        vwze::dao::DoeDAO::getInstance()->insert(con, doe);
        delete doe;

        LOG4CXX_INFO(logger, "\t" + doe->doeorgpob + " OK");
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Loader::calcularAgregadosWE1_VW(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    if (true | false) {
        return;
    }

    con.prepare("delete from doe where doetip = 1").execute();

    //    std::string sql = "select dodfec, dodflu, dodorgzon, dodorgpob, doddun, dodpro, doddeszon, doddespob "
    //            ", sum(dodpes) p, sum(dodvol) v, count(dodcod) c, sum(dodpef) pf "
    //            " from dod "
    //            " where "
    //            "    dodtip = 1"
    //            " group by dodfec, dodflu, dodorgzon, dodorgpob, doddun, dodpro, doddeszon, doddespob ";

    std::string sql = "select transport_id dodorgpob, docorgzon dodorgzon, zoozoncod doddeszon, min(docfec) dodfec, "
            " count(distinct docexp) c, sum(docpes) p , sum(docvol) v, sum(docpef) doddespob"
            " from auftrage "
            " join doc on doc.docexp = envio "
            " join zoo on zoo.zoopcp = docorgzon "
            " where "
            " tipo = 'Sammelgut' and flujo = 'WE' "
            " group by 1, 2, 3"
            " order by transport_id";


    tntdb::Result r = con.prepare(sql).select();
    for (auto row : r) {
        vwze::entity::Doe * doe = new vwze::entity::Doe;
        doe->doecod = ++doecod;
        doe->doetip = 1;
        doe->doefec = row.getDate("dodfec");
        doe->doeflu = "WE";
        doe->doeorgzon = row.getString("dodorgzon");
        doe->doeorgpob = row.getString("dodorgpob");
        doe->doedeszon = row.getString("doddeszon");
        doe->doedespob = row.getString("doddespob");
        //        doe->doepro = row.getString("dodpro");
        //        doe->doedun = row.getString("doddun");
        //        doe->doeexp = row.getString("dodrel");

        doe->doepes = row.getDouble("p");
        doe->doevol = row.getDouble("v");
        doe->doecnt = row.getInt64("c");

        double pef = doe->doevol * 250;
        doe->doepef = doe->doepes > pef ? doe->doepes : pef;
        //        doe->doepef = row.getDouble("pf");


        vwze::dao::DoeDAO::getInstance()->insert(con, doe);
        delete doe;

        LOG4CXX_INFO(logger, "\t" + doe->doeorgpob + " OK");
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}

/**
 * Entregas de CC a planta
 */
void Loader::calcularAgregadosWE2_VW(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    if (true | false) {
        return;
    }

    con.prepare("delete from doe where doetip = 2").execute();

    //    std::string sql = "select dodfec, dodflu, dodorgzon, dodorgpob, doddeszon, doddespob"
    //            ", sum(dodpes) p, sum(dodvol) v, count(dodcod) c, sum(dodpef) pf "
    //            " from dod "
    //            " where "
    //            "   dodtip = 2 "
    //            " group by dodfec, dodflu, dodorgzon, dodorgpob, doddeszon, doddespob";

    std::string sql = R"SQL(
            select transport_id dodorgpob, 
                min(zoozoncod) dodorgzon, min(docdeszon) doddeszon, 
                min(docfec) dodfec,
                count(distinct docexp) c, sum(docpes) p, sum(docvol) v, sum(docpef) doddespob,
                count(distinct zoozoncod) dodpro,count(distinct docdeszon) doddun
            from auftrage 
		join doc on doc.docexp = envio
                join zoo on zoo.zoopcp = docorgzon
            where 
                tipo = 'Hauptlauf' and flujo = 'WE' and dockcc  = ''
            group by 1
            union
            select transport_id dodorgpob, 
                min(zoozoncod) dodorgzon, min(dockcc) doddeszon, 
                min(docfec) dodfec,
                count(distinct docexp) c, sum(docpes) p, sum(docvol) v, sum(docpef) doddespob,
                count(distinct zoozoncod) dodpro,count(distinct dockcc) doddun
            from auftrage 
		join doc on doc.docexp = envio
                join zoo on zoo.zoopcp = docorgzon
            where 
                tipo = 'Hauptlauf' and flujo = 'WE' and dockcc  <> ''
            group by 1)SQL";

    tntdb::Result r = con.prepare(sql).select();
    for (auto row : r) {
        vwze::entity::Doe * doe = new vwze::entity::Doe;
        doe->doecod = ++doecod;
        doe->doetip = 2;
        doe->doefec = row.getDate("dodfec");
        doe->doeflu = "WE";
        doe->doeorgzon = row.getString("dodorgzon");
        doe->doeorgpob = row.getString("dodorgpob");
        doe->doedeszon = row.getString("doddeszon");
        doe->doedespob = row.getString("doddespob");
        doe->doepro = row.getString("dodpro");
        doe->doedun = row.getString("doddun");
        //        doe->doeexp = row.getString("dodrel");

        doe->doepes = row.getDouble("p");
        doe->doevol = row.getDouble("v");
        doe->doecnt = row.getInt64("c");

        double pef = doe->doevol * 250;
        doe->doepef = doe->doepes > pef ? doe->doepes : pef;
        //        doe->doepef = row.getDouble("pf");

        vwze::dao::DoeDAO::getInstance()->insert(con, doe);
        delete doe;

        LOG4CXX_INFO(logger, "\t" + doe->doeorgpob + " OK");
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}
