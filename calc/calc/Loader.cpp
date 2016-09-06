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
        std::exception e;
        throw e;
    }

    borrarDatos();
    cargarMaps();

    //std::ifstream infile("vwze.csv");
    std::ifstream infile("vwze.csv");

    std::string line = "";

    std::getline(infile, line); // descarta textos
    std::getline(infile, line);
    while (!infile.eof()) {
        vwze::entity::Doc * doc = parsearLinea(line);
        insertarDocumento(doc);
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
   
    calcularAgregadosWA1();
    calcularAgregadosWA2();
    calcularAgregadosWE1();
    calcularAgregadosWE2();
    calcularManipulaciones();

    
    LOG4CXX_INFO(logger, "<----- Fin");
}

void Loader::calcularAgregadosWA1(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");
    
    con.prepare("delete from doe where doetip = -1").execute();    
    
    std::string sql = "select dodfec, dodflu, dodorgzon, dodorgpob, doddun, dodpro, doddeszon, doddespob"
            ", sum(dodpes) p, sum(dodvol) v, count(dodcod) c "
            " from dod "
            " where "
            "    dodtip = -1"
            " group by dodfec, dodflu, dodorgzon, dodorgpob, doddun, dodpro, doddeszon, doddespob ";
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
        doe->doedespob = row.getString("doddespob");
        doe->doepro = row.getString("dodpro");
        doe->doedun = row.getString("doddun");
        
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
    
    con.prepare("delete from doe where doetip = -2").execute();
    
    std::string sql = "select dodfec, dodflu, dodorgzon, dodorgpob, doddeszon, doddespob"
            ", sum(dodpes) p, sum(dodvol) v, count(dodcod) c "
            " from dod "
            " where "
            "   dodtip = -2 "
            " group by dodfec, dodflu, dodorgzon, dodorgpob, doddeszon, doddespob";
    
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
 * Recogidas de proveedor a CC
 */
void Loader::calcularAgregadosWE1(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");
    
    con.prepare("delete from doe where doetip = 1").execute();
    
    std::string sql = "select dodfec, dodflu, dodorgzon, dodorgpob, doddun, dodpro, doddeszon, doddespob"
            ", sum(dodpes) p, sum(dodvol) v, count(dodcod) c "
            " from dod "
            " where "
            "    dodtip = 1"
            " group by dodfec, dodflu, dodorgzon, dodorgpob, doddun, dodpro, doddeszon, doddespob ";
    tntdb::Result r = con.prepare(sql).select();
    for (auto row : r) {
        vwze::entity::Doe * doe = new vwze::entity::Doe;
        doe->doecod = ++doecod;
        doe->doetip = 1;
        doe->doefec = row.getDate("dodfec");
        doe->doeflu = row.getString("dodflu");
        doe->doeorgzon = row.getString("dodorgzon");
        doe->doeorgpob = row.getString("dodorgpob");
        doe->doedeszon = row.getString("doddeszon");
        doe->doedespob = row.getString("doddespob");
        doe->doepro = row.getString("dodpro");
        doe->doedun = row.getString("doddun");
        
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
    
    con.prepare("delete from doe where doetip = 2").execute();
    
    std::string sql = "select dodfec, dodflu, dodorgzon, dodorgpob, doddeszon, doddespob"
            ", sum(dodpes) p, sum(dodvol) v, count(dodcod) c "
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

void Loader::calcularManipulaciones(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");
    
    if (true | false ) {
        return;
    }

    con.prepare("delete from doe where doetip = 0").execute();
    
    std::string sql = "select docexp, docdun, docpro, docfec, docflu, docdeszon, docpes, docvol, docpef"
            " , zon.* from doc "
            "   join zoo on zoopcp = docdeszon "
            "   join zon on zoncod = zoozoncod "
            " where docflu = 'WA' and docpef < 6000 "
            " union"
            " select docexp, docdun, docpro, docfec, docflu, docorgzon, docpes, docvol, docpef"
            " , zon.* from doc "
            "   join zoo on zoopcp = docorgzon"
            "   join zon on zoncod = zoozoncod "
            " where docflu = 'WE' and docpef < 6000";
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
        doe->doeorgzon = row.getString("zoncod");
        doe->doeorgpob = row.getString("zondes");
        doe->doedeszon = doe->doeorgzon;
        doe->doedespob = doe->doeorgpob;
        
        doe->doepes = row.getDouble("docpes");
        doe->doevol = row.getDouble("docvol");
        doe->doepef = row.getDouble("docpef");
        doe->doecnt = 1;
        
        vwze::dao::DoeDAO::getInstance()->insert(con, doe);
        delete doe;        
    }
    
    LOG4CXX_TRACE(logger, "<----- Fin");    
}

void Loader::borrarDatos(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    con.prepare("delete from dod").execute();
    con.prepare("delete from doc").execute();
    con.prepare("delete from pro").execute();

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Loader::cargarMaps(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    // inicializando códigos
    doccod = 0;
    dodcod = 0;

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
    if (!boost::starts_with(doc->docrel, "Pflicht")) {
        LOG4CXX_TRACE(logger, "<----- Return 1");
        return;
    }

    // sólo zonas tarificadas
    std::string zoopcp = "";
    if (boost::starts_with(doc->docflu, "WE")) {
        zoopcp = doc->docorgzon;
    } else if (boost::starts_with(doc->docflu, "WA")) {
        zoopcp = doc->docdeszon;
    }
    if (zonMap.find(zoopcp) == zonMap.end()) {
        LOG4CXX_TRACE(logger, "<----- Return 2");
        return;
    }

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

    doc->docrel = fields[0];
    doc->docexp = fields[1];
    doc->docfec = parsearDate(fields[2]);
    doc->docorgzon = fields[7];
    doc->docorgpob = fields[10];
    doc->docdeszon = fields[13];
    doc->docdespob = fields[14];
    doc->docflu = boost::trim_copy(fields[17]);
    doc->docfab = fields[19];
    doc->docdun = fields[18];
    doc->docpro = boost::trim_copy(fields[28]);
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