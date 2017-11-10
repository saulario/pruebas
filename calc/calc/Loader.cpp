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
    for (auto p : zonMap) {
        if (p.second) {
            delete p.second;
        }
    }
    for (auto p : kccMap) {
        if (p.second) {
            delete p.second;
        }
    }
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
    calcularDirectosWA();
    calcularAgregadosWE1();
    calcularAgregadosWE2();
    calcularDirectosWE();

    LOG4CXX_INFO(logger, "<----- Fin");
}

void Loader::calcularAgregados(int tipo) {

    con.prepare("delete from doe where doetip = :doetip")
            .setInt("doetip", tipo)
            .execute();

    std::string sql = "select dodkey, dodfec, dodflu, dodorgzon, doddeszon "
            ", sum(dodpes) p, sum(dodvol) v, count(dodcod) c "
            " from dod "
            " where "
            "   dodtip = :dodtip "
            " group by dodkey, dodfec, dodflu, dodorgzon, doddeszon";

    tntdb::Result r = con.prepare(sql).setInt("dodtip", tipo).select();
    for (auto row : r) {
        vwze::entity::Doe * doe = new vwze::entity::Doe;
        doe->doecod = ++doecod;
        doe->doekey = row.getString("dodkey");
        doe->doetip = tipo;
        doe->doefec = row.getDate("dodfec");
        doe->doeflu = row.getString("dodflu");
        doe->doeorgzon = row.getString("dodorgzon");
        doe->doedeszon = row.getString("doddeszon");

        doe->doepes = row.getDouble("p");
        doe->doevol = row.getDouble("v");
        doe->doecnt = row.getInt64("c");

        double pef = doe->doevol * 250;
        doe->doepef = doe->doepes > pef ? doe->doepes : pef;

        vwze::dao::DoeDAO::getInstance()->insert(con, doe);
        delete doe;
    }
}

void Loader::calcularAgregadosWA1(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    //    if (true | false) {
    //        return;
    //    }
    calcularAgregados(-1);

    LOG4CXX_TRACE(logger, "<----- Fin");
}

void Loader::calcularAgregadosWA2(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    //    if (true | false) {
    //        return;
    //    }
    calcularAgregados(-2);

    LOG4CXX_TRACE(logger, "<----- Fin");
}

/**
 * Agrega para directos WA
 * 
 */
void Loader::calcularDirectosWA(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    //    if (true | false) {
    //        return;
    //    }
    calcularAgregados(-3);

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
    calcularAgregados(1);

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
    calcularAgregados(2);

    LOG4CXX_TRACE(logger, "<----- Fin");
}

/**
 * Agrega para directos WE
 * 
 */
void Loader::calcularDirectosWE(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    //    if (true | false) {
    //        return;
    //    }
    calcularAgregados(3);

    LOG4CXX_TRACE(logger, "<----- Fin");
}

/**
 * 
 */
void Loader::borrarDatos(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    con.prepare("delete from dod").execute();
    con.prepare("delete from doe").execute();

    LOG4CXX_TRACE(logger, "<----- Fin");
}

/**
 * 
 */
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

    stmt = con.prepare("select * from kcc");
    for (auto kcc : vwze::dao::KccDAO::getInstance()->query(con, stmt)) {
        kccMap.insert(std::pair<std::string, vwze::entity::Kcc *>(kcc->kcccod, kcc));
    };


    // previsión de directos en todos los sentidos
    const char * sql = R"foo(select concat(docflu, ':', docfec, ':',
	docdun, ':', 
        if (dockcc <> '', concat(dockcc, "_", kccnom), concat(docdeszon, "_", docdespob)),':', 
        docrel) codigo, 
        round(sum(docpef)) sum_menge, round(sum(docvol * 250)) menge_calculado, 
        round(sum(docpes)) peso_total, count(docexp) documentos 
        from doc left join kcc on kcccod = dockcc
        where 
            docflu = 'we' 
        group by codigo
        having (menge_calculado > 8000 or peso_total > 8000)
        union
    select concat(docflu, ':', docfec, ':', 
        if (dockcc <> '', concat(dockcc, "_", kccnom), concat(docorgzon, "_", docorgpob)),':', 
        docdun, ':', 
        docrel) codigo, 
        round(sum(docpef)) sum_menge, round(sum(docvol * 250)) menge_calculado,
        round(sum(docpes)) peso_total, count(docexp) documentos   
        from doc left join kcc on kcccod = dockcc
        where 
            docflu = 'wa' 
        group by codigo 
        having (menge_calculado > 8000 or peso_total > 8000))foo";
    stmt = con.prepare(sql);
    for (tntdb::Row row : stmt.select()) {
        std::string codigo = row.getString("codigo");
        double menge_calculado = row.getDouble("menge_calculado");
        double peso_total = row.getDouble("peso_total");
        directosMap.insert(std::pair<std::string, double>(codigo, (menge_calculado > peso_total ? menge_calculado : peso_total)));
    }

    std::cerr << directosMap.size() << std::endl;

    LOG4CXX_TRACE(logger, "<----- Fin");
}

/**
 * Inserta directos tanto de WA como de WE. La diferencia está en la clave y en el tipo
 * 
 * @param doc
 * @param codigo
 * @param dodtip
 */
void Loader::insertarDirecto(const vwze::entity::Doc * doc, const std::string & dodkey,
        int dodtip) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    vwze::entity::Dod * dod = getInstance(doc);
    dod->dodcod = ++dodcod;
    dod->dodkey = dodkey;
    dod->dodtip = dodtip;

    // excepciones KCC
    if (!doc->dockcc.empty()) {
        if (dodtip == 3) {
            dod->doddeszon = doc->dockcc;
            dod->doddespob = getKccDescripcion(doc->dockcc);
        } else if (dodtip == -3) {
            dod->dodorgzon = doc->dockcc;
            dod->dodorgpob = getKccDescripcion(doc->dockcc);
        }
    }

    vwze::dao::DodDAO::getInstance()->insert(con, dod);
    delete dod;

    LOG4CXX_TRACE(logger, "<----- Fin");
}

/**
 * Decide qué tipos de documento se insertan para flujo WA
 * 
 * @param doc
 */
void Loader::procesarDocumentoWA(const vwze::entity::Doc * doc) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    std::string clave = getCodigoWA(doc);
    if (directosMap.find(clave) != directosMap.end()) {
        LOG4CXX_DEBUG(logger, "\t(clave directo): " + clave);
        insertarDirecto(doc, clave, -3);
    } else {
        insertarDocumentosWA(doc);
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
void Loader::insertarDocumentosWA(const vwze::entity::Doc * doc) {
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
    dod->dodkey = getCodigoWA(dod);
    vwze::dao::DodDAO::getInstance()->insert(con, dod);

    dod->dodorgzon = zon->zoncod;
    dod->dodorgpob = zon->zondes;
    dod->doddeszon = doc->docdeszon;
    dod->doddespob = doc->docdespob;

    dod->dodcod = ++dodcod;
    dod->dodtip = -1;
    dod->dodkey = getCodigoWA(dod);
    vwze::dao::DodDAO::getInstance()->insert(con, dod);

    delete dod;

    LOG4CXX_TRACE(logger, "<----- Fin");
}

/**
 * Define qué tipos de documento se insertan para flujo WE
 * 
 * @param doc
 */
void Loader::procesarDocumentoWE(const vwze::entity::Doc * doc) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    std::string clave = getCodigoWE(doc);
    if (directosMap.find(clave) != directosMap.end()) {
        LOG4CXX_DEBUG(logger, "\t(clave directo): " + clave);
        insertarDirecto(doc, clave, 3);
    } else {
        insertarDocumentosWE(doc);
    }

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
void Loader::insertarDocumentosWE(const vwze::entity::Doc * doc) {
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
    dod->dodkey = getCodigoWE(dod);

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
    dod->dodkey = getCodigoWE(dod);

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
 * Genera clave de directos para WA
 * 
 * @param doc
 * @return 
 */
inline std::string Loader::getCodigoWA(const vwze::entity::Doc * doc) {

    std::string aux = "";
    if (!doc->dockcc.empty()) {
        aux = doc->dockcc + "_" + kccMap.find(doc->dockcc)->second->kccnom;
    } else {
        aux = doc->docorgzon + "_" + doc->docorgpob;
    }

    std::stringstream ss;
    ss << doc->docflu
            << ":" << doc->docfec.getIso()
            << ":" << aux
            << ":" << doc->docdun
            << ":" << doc->docrel
            ;
    return ss.str();
}

/**
 * Genera clave para documentos WE
 * 
 * @param doc
 * @return 
 */
inline std::string Loader::getCodigoWA(const vwze::entity::Dod * dod) {

    std::stringstream ss;
    switch (dod->dodtip) {
        case -1:
            ss << dod->dodflu
                    << ":" << dod->dodfec.getIso()
                    << ":" << dod->dodorgzon + "_" + dod->dodorgpob
                    << ":" << dod->doddun
                    << ":" << dod->dodrel
                    ;
            break;
        case -2:
            ss << dod->dodflu
                    << ":" << dod->dodfec.getIso()
                    << ":" << dod->dodorgzon + "_" + dod->dodorgpob
                    << ":" << dod->doddeszon + "_" + dod->doddespob
                    << ":" << dod->dodrel
                    ;
            break;
    }

    return ss.str();
}

/**
 * Genera clave de directos para WE
 * 
 * @param doc
 * @return 
 */
inline std::string Loader::getCodigoWE(const vwze::entity::Doc * doc) {

    std::string aux = "";
    if (!doc->dockcc.empty()) {
        aux = doc->dockcc + "_" + kccMap.find(doc->dockcc)->second->kccnom;
    } else {
        aux = doc->docdeszon + "_" + doc->docdespob;
    }

    std::stringstream ss;
    ss << doc->docflu
            << ":" << doc->docfec.getIso()
            << ":" << doc->docdun
            << ":" << aux
            << ":" << doc->docrel
            ;
    return ss.str();
}

/**
 * Genera clave para documentos WE
 * 
 * @param doc
 * @return 
 */
inline std::string Loader::getCodigoWE(const vwze::entity::Dod * dod) {

    std::stringstream ss;
    switch (dod->dodtip) {
        case 1:
            ss << dod->dodflu
                    << ":" << dod->dodfec.getIso()
                    << ":" << dod->doddun
                    << ":" << dod->doddeszon + "_" + dod->doddespob
                    << ":" << dod->dodrel
                    ;
            break;
        case 2:
            ss << dod->dodflu
                    << ":" << dod->dodfec.getIso()
                    << ":" << dod->dodorgzon + "_" + dod->dodorgpob
                    << ":" << dod->doddeszon + "_" + dod->doddespob
                    << ":" << dod->dodrel
                    ;
            break;
    }

    return ss.str();
}

/**
 * Genera instancia dod a partir de doc
 * 
 * @param doc
 * @return 
 */
vwze::entity::Dod * Loader::getInstance(const vwze::entity::Doc * doc) {
    vwze::entity::Dod * dod = new vwze::entity::Dod;

    dod->dodcod = 0;
    dod->dodrel = doc->docrel;
    dod->dodexp = doc->docexp;
    dod->dodfec = doc->docfec;
    dod->dodtip = 0;

    dod->dodorgzon = doc->docorgzon;
    dod->dodorgpob = doc->docorgpob;
    dod->doddeszon = doc->docdeszon;
    dod->doddespob = doc->docdespob;

    dod->dodflu = doc->docflu;
    dod->dodfab = doc->docfab;
    dod->doddun = doc->docdun;
    dod->dodpro = doc->docpro;

    dod->dodpes = doc->docpes;
    dod->dodvol = doc->docvol;
    dod->dodpef = doc->docpef;

    return dod;
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
        result = "KCC Heilbronn";
    } else if (boost::starts_with(p, "DE85")) {
        result = "KCC Ingolstadt";
    } else if (boost::starts_with(p, "DE34")) {
        result = "KCC Baunatal";
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
    return result;
}

/**
 * Partiendo de los datos originales se generan las operaciones teóricas. Este
 * método está habitualmente protegido contra ejecución.
 * 
 */
void Loader::reconstruirDocumentos(void) {
    LOG4CXX_TRACE(logger, "-----> Inicio");

    // protección
    //    if (true | false) {
    //        return;
    //    }

    borrarDatos();
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
            procesarDocumentoWE(doc);
        } else if (boost::starts_with(doc->docflu, "WA")) {
            procesarDocumentoWA(doc);
        } else {
            LOG4CXX_WARN(logger, "\tIgnorando documento " + doc->docexp + " flujo desconocido");
        }

        LOG4CXX_INFO(logger, "     " + doc->docexp + " OK ");
    }
    for (auto doc : docList) {
        delete doc;
    }

    LOG4CXX_TRACE(logger, "<----- Fin");
}
