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

int Loader::run(int argc, char ** argv) {
    LOG4CXX_INFO(logger, "-----> Inicio");

    borrarDatos();
    cargarDatos();

    //std::ifstream infile("vwze.csv");
    std::ifstream infile("vwzewe.csv");

    std::string line = "";

    std::getline(infile, line); // descarta textos
    std::getline(infile, line);
    while (!infile.eof()) {

        vwze::entity::Doc * doc = parsearLinea(line);
        insertarDocumento(doc);
        if (doc) delete doc;

        if (doccod > 1000000) {
            break;
        }

        std::getline(infile, line);
    }

    std::cerr << doccod << std::endl;
    infile.close();

    LOG4CXX_INFO(logger, "<----- Fin");
}

void Loader::borrarDatos(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    con.prepare("delete from dod").execute();
    con.prepare("delete from doc").execute();
    con.prepare("delete from pro").execute();

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Loader::cargarDatos(void) {
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

    doc->docpes = parsearDouble(fields[20]);
    doc->docvol = parsearDouble(fields[21]);
    doc->docpef = parsearDouble(fields[22]);

    LOG4CXX_TRACE(logger, "<----- Fin");
    return doc;
}