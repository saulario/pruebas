#include <cstdlib>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
#include <tntdb/connect.h>
#include <tntdb/connection.h>
#include <tntdb/result.h>
#include <tntdb/statement.h>
#include <tntdb/error.h>

#include "Loader.h"
#include "Tarificador.h"
#include "vwze_dao.h"

using namespace std;

static log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger("main");

void corregirDocumentos(tntdb::Connection &);

/*
 * 
 */
int main(int argc, char** argv) {
    int rv = EXIT_SUCCESS;

    log4cxx::PropertyConfigurator::configure("log4cxx.properties");
    LOG4CXX_INFO(logger, "-----> Inicio");

    tntdb::Connection con = tntdb::connect("mysql:db=vwze_1711_z3e4;user=vwze;passwd=vwzexx");

    try {
        
//        ParserTarifa pt(con);
//        pt.cargarTarifaDirectos("/home/saulario/VWZE/1711_definitivo/TARIFA_DIRECTOS.csv");
//        pt.cargarTarifaCapilar("/home/saulario/VWZE/1711_definitivo/TARIFA_CAPILAR.csv");

        
//        Loader l(con);
////        l.reconstruirDocumentos();
//        l.calcularAgregados();

        Tarificador t(con);
        t.tarificar();

    } catch (std::exception &e) {
        LOG4CXX_ERROR(logger, std::string(e.what()));
        rv = 1;
    }

    con.close();
    LOG4CXX_INFO(logger, "<----- Fin");

    return rv;
}

/**
 * Correcciones varias de documentos
 * 
 */
void corregirDocumentos(tntdb::Connection &con) {

    int doccod = 132000;

    tntdb::Statement stmt = con.prepare("select * from doc where "
            " docflu = :docflu "
            " and docfab = :docfab "
            " limit 1");

    tntdb::Result result = con.prepare("select * from bewertung where "
            " not auftragsnummer in (select docexp from doc)")
            .select();
    for (tntdb::Row row : result) {
        vwze::entity::Doc * doc = new vwze::entity::Doc;

        doc->docrel = row.getString("relevanz");
        if (doc->docrel.length() > 20) {
            doc->docrel = "Pflicht Drittgeschaf";
        }

        doc->docexp = row.getString("auftragsnummer");
        doc->docfec = row.getDate("datum");

        std::string wewa = row.getString("wewa");
        std::string gebiet = row.getString("gebiet");
        std::string sender = row.getString("senderlocation");
        std::string empfanger = row.getString("empfangerlocation");
        std::string werk = row.getString("werk");

        std::string zo = "";
        std::string zd = "";

        if (werk.compare("Stuttgart") == 0) {
            zo = zd = "DE70";
        } else if (werk.compare("Valmet Automotive GmbH") == 0) {
            zo = zd = "DE49";
        } else {
            stmt.setString("docflu", wewa);
            stmt.setString("docfab", werk.substr(0, 2));
            try {
                tntdb::Row fabrica = stmt.selectRow();
                zo = fabrica.getString("docorgzon");
                zd = fabrica.getString("docdeszon");
            } catch (tntdb::NotFound) {
                std::cerr << "Ignorando " << werk << std::endl;
                continue;
            }
        }

        doc->docflu = wewa;
        doc->docfab = werk;
        if (doc->docfab.length() > 20) {
            doc->docfab = doc->docfab.substr(0, 20);
        }

        doc->docorgpob = sender;
        doc->docdespob = empfanger;

        if (wewa.compare("WE") == 0) {
            doc->docorgzon = gebiet;
            doc->docdeszon = zd;
            doc->docdun = sender.substr(0, 9);
            doc->docpro = sender;
        } else if (wewa.compare("WA") == 0) {
            doc->docorgzon = zo;
            doc->docdeszon = gebiet;
            doc->docdun = empfanger.substr(0, 9);
            doc->docpro = empfanger;
        } else {
            throw std::exception();
        }


        // no tengo el peso real, así que asumo que es un volumen equivalente
        double menge = row.getDecimal("berechnetes").getDouble();
        doc->docpes = menge;
        doc->docpef = menge;
        doc->docvol = menge / 255;

        doc->doccod = ++doccod;
        vwze::dao::DocDAO::getInstance()->insert(con, doc);
        delete doc;
    }

    std::cerr << doccod << std::endl;

}

