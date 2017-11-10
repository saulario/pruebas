#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <tntdb/error.h>
#include "vwze_dao.h"
using namespace vwze::dao;

void CommonDAO::createQueries(void) {
    insertQuery = "insert into " + table + "(" + columns + ")"
            " values("
            ;
    std::vector<std::string> fields;
    bool first = true;
    boost::algorithm::split(fields, columns, boost::algorithm::is_any_of(","));
    for (std::string f : fields) {
        if (!first) {
            insertQuery += ",";
        }
        first = false;
        insertQuery += ":" + f;
    }
    insertQuery += ")";
    readQuery = "select " + columns + " from " + table + " where ";
    first = true;
    boost::algorithm::split(fields, keyColumns, boost::algorithm::is_any_of(","));
    for (std::string f : fields) {
        if (!first) {
            readQuery += " and ";
        }
        first = false;
        readQuery += f + "=:" + f + "PK";
    }
    removeQuery = "delete from " + table + " where ";
    first = true;
    boost::algorithm::split(fields, keyColumns, boost::algorithm::is_any_of(","));
    for (std::string f : fields) {
        if (!first) {
            removeQuery += " and ";
        }
        first = false;
        removeQuery += f + "=:" + f + "PK";
    }
    updateQuery = "update " + table + " set ";
    first = true;
    boost::algorithm::split(fields, columns, boost::algorithm::is_any_of(","));
    for (std::string f : fields) {
        if (!first) {
            updateQuery += ",";
        }
        first = false;
        updateQuery += f + "=:" + f;
    }
    updateQuery += " where ";
    first = true;
    boost::algorithm::split(fields, keyColumns, boost::algorithm::is_any_of(","));
    for (std::string f : fields) {
        if (!first) {
            updateQuery += " and ";
        }
        first = false;
        updateQuery += f + "=:" + f + "PK";
    }
}

std::string CommonDAO::getInsertQuery(void) {
    return insertQuery;
}

std::string CommonDAO::getReadQuery(void) {
    return readQuery;
}

std::string CommonDAO::getRemoveQuery(void) {
    return removeQuery;
}

std::string CommonDAO::getUpdateQuery(void) {
    return updateQuery;
}

std::string CommonDAO::getColumns(void) {
    return columns;
}

std::string CommonDAO::getTable(void) {
    return table;
}


DocDAO * DocDAO::dao = NULL;
boost::mutex DocDAO::mtx;

DocDAO::~DocDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

DocDAO * DocDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new DocDAO();
        dao->table = "doc";
        dao->keyColumns = "doccod";
        dao->columns = "doccod,docrel,docexp,docfec"
                ",docorgzon,docorgpob,docdeszon,docdespob,docflu"
                ",docfab,docdun,docpro,dockcc,docpes"
                ",docvol,docpef";
        dao->createQueries();
    }
    return dao;
}

vwze::entity::Doc * DocDAO::insert(tntdb::Connection & con, vwze::entity::Doc * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<vwze::entity::Doc *> DocDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<vwze::entity::Doc *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        vwze::entity::Doc * e = new vwze::entity::Doc;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

vwze::entity::Doc * DocDAO::read(tntdb::Connection & con, const long & doccod) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    vwze::entity::Doc * e = NULL;
    try {
        stmt.set("doccodPK", doccod);
        tntdb::Row row = stmt.selectRow();
        e = new vwze::entity::Doc;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type DocDAO::remove(tntdb::Connection & con, const long & doccod) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("doccodPK", doccod);
    return stmt.execute();
}

vwze::entity::Doc * DocDAO::update(tntdb::Connection & con, vwze::entity::Doc * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("doccodPK", e->doccod);
    stmt.execute();
    return e;
}

void DocDAO::loadColumns(tntdb::Row & row, vwze::entity::Doc * e) {
    int index = 0;
    e->doccod = row.getInt64(index++);
    e->docrel = row.getString(index++);
    e->docexp = row.getString(index++);
    e->docfec = row.getDate(index++);
    e->docorgzon = row.getString(index++);
    e->docorgpob = row.getString(index++);
    e->docdeszon = row.getString(index++);
    e->docdespob = row.getString(index++);
    e->docflu = row.getString(index++);
    e->docfab = row.getString(index++);
    e->docdun = row.getString(index++);
    e->docpro = row.getString(index++);
    e->dockcc = row.getString(index++);
    e->docpes = row.getInt(index++);
    e->docvol = row.getDecimal(index++).getDouble();
    e->docpef = row.getInt(index++);
}

void DocDAO::setColumns(tntdb::Statement & stmt, const vwze::entity::Doc * e) {
    stmt.setInt64("doccod", e->doccod);
    stmt.setString("docrel", e->docrel);
    stmt.setString("docexp", e->docexp);
    stmt.setDate("docfec", e->docfec);
    stmt.setString("docorgzon", e->docorgzon);
    stmt.setString("docorgpob", e->docorgpob);
    stmt.setString("docdeszon", e->docdeszon);
    stmt.setString("docdespob", e->docdespob);
    stmt.setString("docflu", e->docflu);
    stmt.setString("docfab", e->docfab);
    stmt.setString("docdun", e->docdun);
    stmt.setString("docpro", e->docpro);
    stmt.setString("dockcc", e->dockcc);
    stmt.setInt("docpes", e->docpes);
    stmt.setDouble("docvol", e->docvol);
    stmt.setInt("docpef", e->docpef);
}


DodDAO * DodDAO::dao = NULL;
boost::mutex DodDAO::mtx;

DodDAO::~DodDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

DodDAO * DodDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new DodDAO();
        dao->table = "dod";
        dao->keyColumns = "dodcod";
        dao->columns = "dodcod,dodrel,dodexp,dodtip"
                ",dodfec,dodorgzon,dodorgpob,doddeszon,doddespob"
                ",dodflu,dodfab,doddun,dodpro,dodpes"
                ",dodvol,dodpef,dodkey";
        dao->createQueries();
    }
    return dao;
}

vwze::entity::Dod * DodDAO::insert(tntdb::Connection & con, vwze::entity::Dod * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<vwze::entity::Dod *> DodDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<vwze::entity::Dod *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        vwze::entity::Dod * e = new vwze::entity::Dod;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

vwze::entity::Dod * DodDAO::read(tntdb::Connection & con, const long & dodcod) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    vwze::entity::Dod * e = NULL;
    try {
        stmt.set("dodcodPK", dodcod);
        tntdb::Row row = stmt.selectRow();
        e = new vwze::entity::Dod;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type DodDAO::remove(tntdb::Connection & con, const long & dodcod) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("dodcodPK", dodcod);
    return stmt.execute();
}

vwze::entity::Dod * DodDAO::update(tntdb::Connection & con, vwze::entity::Dod * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("dodcodPK", e->dodcod);
    stmt.execute();
    return e;
}

void DodDAO::loadColumns(tntdb::Row & row, vwze::entity::Dod * e) {
    int index = 0;
    e->dodcod = row.getInt64(index++);
    e->dodrel = row.getString(index++);
    e->dodexp = row.getString(index++);
    e->dodtip = row.getInt(index++);
    e->dodfec = row.getDate(index++);
    e->dodorgzon = row.getString(index++);
    e->dodorgpob = row.getString(index++);
    e->doddeszon = row.getString(index++);
    e->doddespob = row.getString(index++);
    e->dodflu = row.getString(index++);
    e->dodfab = row.getString(index++);
    e->doddun = row.getString(index++);
    e->dodpro = row.getString(index++);
    e->dodpes = row.getInt(index++);
    e->dodvol = row.getDecimal(index++).getDouble();
    e->dodpef = row.getInt(index++);
    e->dodkey = row.getString(index++);
}

void DodDAO::setColumns(tntdb::Statement & stmt, const vwze::entity::Dod * e) {
    stmt.setInt64("dodcod", e->dodcod);
    stmt.setString("dodrel", e->dodrel);
    stmt.setString("dodexp", e->dodexp);
    stmt.setInt("dodtip", e->dodtip);
    stmt.setDate("dodfec", e->dodfec);
    stmt.setString("dodorgzon", e->dodorgzon);
    stmt.setString("dodorgpob", e->dodorgpob);
    stmt.setString("doddeszon", e->doddeszon);
    stmt.setString("doddespob", e->doddespob);
    stmt.setString("dodflu", e->dodflu);
    stmt.setString("dodfab", e->dodfab);
    stmt.setString("doddun", e->doddun);
    stmt.setString("dodpro", e->dodpro);
    stmt.setInt("dodpes", e->dodpes);
    stmt.setDouble("dodvol", e->dodvol);
    stmt.setInt("dodpef", e->dodpef);
    stmt.setString("dodkey", e->dodkey);
}


DoeDAO * DoeDAO::dao = NULL;
boost::mutex DoeDAO::mtx;

DoeDAO::~DoeDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

DoeDAO * DoeDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new DoeDAO();
        dao->table = "doe";
        dao->keyColumns = "doecod";
        dao->columns = "doecod,doerel,doetip,doefec"
                ",doeorgzon,doeorgpob,doedeszon,doedespob,doeflu"
                ",doeexp,doedun,doepro,doepes,doevol"
                ",doepef,doecnt,doepun,doetot,doekey";
        dao->createQueries();
    }
    return dao;
}

vwze::entity::Doe * DoeDAO::insert(tntdb::Connection & con, vwze::entity::Doe * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<vwze::entity::Doe *> DoeDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<vwze::entity::Doe *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        vwze::entity::Doe * e = new vwze::entity::Doe;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

vwze::entity::Doe * DoeDAO::read(tntdb::Connection & con, const long & doecod) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    vwze::entity::Doe * e = NULL;
    try {
        stmt.set("doecodPK", doecod);
        tntdb::Row row = stmt.selectRow();
        e = new vwze::entity::Doe;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type DoeDAO::remove(tntdb::Connection & con, const long & doecod) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("doecodPK", doecod);
    return stmt.execute();
}

vwze::entity::Doe * DoeDAO::update(tntdb::Connection & con, vwze::entity::Doe * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("doecodPK", e->doecod);
    stmt.execute();
    return e;
}

void DoeDAO::loadColumns(tntdb::Row & row, vwze::entity::Doe * e) {
    int index = 0;
    e->doecod = row.getInt64(index++);
    e->doerel = row.getString(index++);
    e->doetip = row.getInt(index++);
    e->doefec = row.getDate(index++);
    e->doeorgzon = row.getString(index++);
    e->doeorgpob = row.getString(index++);
    e->doedeszon = row.getString(index++);
    e->doedespob = row.getString(index++);
    e->doeflu = row.getString(index++);
    e->doeexp = row.getString(index++);
    e->doedun = row.getString(index++);
    e->doepro = row.getString(index++);
    e->doepes = row.getInt(index++);
    e->doevol = row.getDecimal(index++).getDouble();
    e->doepef = row.getInt(index++);
    e->doecnt = row.getInt(index++);
    e->doepun = row.getDecimal(index++).getDouble();
    e->doetot = row.getDecimal(index++).getDouble();
    e->doekey = row.getString(index++);
}

void DoeDAO::setColumns(tntdb::Statement & stmt, const vwze::entity::Doe * e) {
    stmt.setInt64("doecod", e->doecod);
    stmt.setString("doerel", e->doerel);
    stmt.setInt("doetip", e->doetip);
    stmt.setDate("doefec", e->doefec);
    stmt.setString("doeorgzon", e->doeorgzon);
    stmt.setString("doeorgpob", e->doeorgpob);
    stmt.setString("doedeszon", e->doedeszon);
    stmt.setString("doedespob", e->doedespob);
    stmt.setString("doeflu", e->doeflu);
    stmt.setString("doeexp", e->doeexp);
    stmt.setString("doedun", e->doedun);
    stmt.setString("doepro", e->doepro);
    stmt.setInt("doepes", e->doepes);
    stmt.setDouble("doevol", e->doevol);
    stmt.setInt("doepef", e->doepef);
    stmt.setInt("doecnt", e->doecnt);
    stmt.setDouble("doepun", e->doepun);
    stmt.setDouble("doetot", e->doetot);
    stmt.setString("doekey", e->doekey);
}


FltDAO * FltDAO::dao = NULL;
boost::mutex FltDAO::mtx;

FltDAO::~FltDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

FltDAO * FltDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new FltDAO();
        dao->table = "flt";
        dao->keyColumns = "";
        dao->columns = "fltcod";
        dao->createQueries();
    }
    return dao;
}

vwze::entity::Flt * FltDAO::insert(tntdb::Connection & con, vwze::entity::Flt * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<vwze::entity::Flt *> FltDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<vwze::entity::Flt *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        vwze::entity::Flt * e = new vwze::entity::Flt;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

void FltDAO::loadColumns(tntdb::Row & row, vwze::entity::Flt * e) {
    int index = 0;
    e->fltcod = row.getString(index++);
}

void FltDAO::setColumns(tntdb::Statement & stmt, const vwze::entity::Flt * e) {
    stmt.setString("fltcod", e->fltcod);
}


KccDAO * KccDAO::dao = NULL;
boost::mutex KccDAO::mtx;

KccDAO::~KccDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

KccDAO * KccDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new KccDAO();
        dao->table = "kcc";
        dao->keyColumns = "kcccod";
        dao->columns = "kcccod,kccnom";
        dao->createQueries();
    }
    return dao;
}

vwze::entity::Kcc * KccDAO::insert(tntdb::Connection & con, vwze::entity::Kcc * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<vwze::entity::Kcc *> KccDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<vwze::entity::Kcc *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        vwze::entity::Kcc * e = new vwze::entity::Kcc;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

vwze::entity::Kcc * KccDAO::read(tntdb::Connection & con, const std::string & kcccod) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    vwze::entity::Kcc * e = NULL;
    try {
        stmt.set("kcccodPK", kcccod);
        tntdb::Row row = stmt.selectRow();
        e = new vwze::entity::Kcc;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type KccDAO::remove(tntdb::Connection & con, const std::string & kcccod) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("kcccodPK", kcccod);
    return stmt.execute();
}

vwze::entity::Kcc * KccDAO::update(tntdb::Connection & con, vwze::entity::Kcc * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("kcccodPK", e->kcccod);
    stmt.execute();
    return e;
}

void KccDAO::loadColumns(tntdb::Row & row, vwze::entity::Kcc * e) {
    int index = 0;
    e->kcccod = row.getString(index++);
    e->kccnom = row.getString(index++);
}

void KccDAO::setColumns(tntdb::Statement & stmt, const vwze::entity::Kcc * e) {
    stmt.setString("kcccod", e->kcccod);
    stmt.setString("kccnom", e->kccnom);
}


KostenDAO * KostenDAO::dao = NULL;
boost::mutex KostenDAO::mtx;

KostenDAO::~KostenDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

KostenDAO * KostenDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new KostenDAO();
        dao->table = "kosten";
        dao->keyColumns = "exped";
        dao->columns = "exped,relevanz,wewa,gebiet"
                ",sender,receiver,planta,transportista,escenario"
                ",menge,kosten,fratch";
        dao->createQueries();
    }
    return dao;
}

vwze::entity::Kosten * KostenDAO::insert(tntdb::Connection & con, vwze::entity::Kosten * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<vwze::entity::Kosten *> KostenDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<vwze::entity::Kosten *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        vwze::entity::Kosten * e = new vwze::entity::Kosten;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

vwze::entity::Kosten * KostenDAO::read(tntdb::Connection & con, const std::string & exped) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    vwze::entity::Kosten * e = NULL;
    try {
        stmt.set("expedPK", exped);
        tntdb::Row row = stmt.selectRow();
        e = new vwze::entity::Kosten;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type KostenDAO::remove(tntdb::Connection & con, const std::string & exped) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("expedPK", exped);
    return stmt.execute();
}

vwze::entity::Kosten * KostenDAO::update(tntdb::Connection & con, vwze::entity::Kosten * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("expedPK", e->exped);
    stmt.execute();
    return e;
}

void KostenDAO::loadColumns(tntdb::Row & row, vwze::entity::Kosten * e) {
    int index = 0;
    e->exped = row.getString(index++);
    e->relevanz = row.getString(index++);
    e->wewa = row.getString(index++);
    e->gebiet = row.getString(index++);
    e->sender = row.getString(index++);
    e->receiver = row.getString(index++);
    e->planta = row.getString(index++);
    try {
        e->setTransportista(row.getString(index++));
    } catch (tntdb::NullValue) {
        e->setNullTransportista();
    }
    try {
        e->setEscenario(row.getString(index++));
    } catch (tntdb::NullValue) {
        e->setNullEscenario();
    }
    e->menge = row.getInt(index++);
    e->kosten = row.getDecimal(index++).getDouble();
    e->fratch = row.getDecimal(index++).getDouble();
}

void KostenDAO::setColumns(tntdb::Statement & stmt, const vwze::entity::Kosten * e) {
    stmt.setString("exped", e->exped);
    stmt.setString("relevanz", e->relevanz);
    stmt.setString("wewa", e->wewa);
    stmt.setString("gebiet", e->gebiet);
    stmt.setString("sender", e->sender);
    stmt.setString("receiver", e->receiver);
    stmt.setString("planta", e->planta);
    if (e->isNullTransportista()) {
        stmt.setNull("transportista");
    } else {
        stmt.setString("transportista", e->getTransportista());
    }
    if (e->isNullEscenario()) {
        stmt.setNull("escenario");
    } else {
        stmt.setString("escenario", e->getEscenario());
    }
    stmt.setInt("menge", e->menge);
    stmt.setDouble("kosten", e->kosten);
    stmt.setDouble("fratch", e->fratch);
}


ProDAO * ProDAO::dao = NULL;
boost::mutex ProDAO::mtx;

ProDAO::~ProDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

ProDAO * ProDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new ProDAO();
        dao->table = "pro";
        dao->keyColumns = "produn";
        dao->columns = "produn,proraz";
        dao->createQueries();
    }
    return dao;
}

vwze::entity::Pro * ProDAO::insert(tntdb::Connection & con, vwze::entity::Pro * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<vwze::entity::Pro *> ProDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<vwze::entity::Pro *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        vwze::entity::Pro * e = new vwze::entity::Pro;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

vwze::entity::Pro * ProDAO::read(tntdb::Connection & con, const std::string & produn) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    vwze::entity::Pro * e = NULL;
    try {
        stmt.set("produnPK", produn);
        tntdb::Row row = stmt.selectRow();
        e = new vwze::entity::Pro;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type ProDAO::remove(tntdb::Connection & con, const std::string & produn) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("produnPK", produn);
    return stmt.execute();
}

vwze::entity::Pro * ProDAO::update(tntdb::Connection & con, vwze::entity::Pro * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("produnPK", e->produn);
    stmt.execute();
    return e;
}

void ProDAO::loadColumns(tntdb::Row & row, vwze::entity::Pro * e) {
    int index = 0;
    e->produn = row.getString(index++);
    e->proraz = row.getString(index++);
}

void ProDAO::setColumns(tntdb::Statement & stmt, const vwze::entity::Pro * e) {
    stmt.setString("produn", e->produn);
    stmt.setString("proraz", e->proraz);
}


RfcDAO * RfcDAO::dao = NULL;
boost::mutex RfcDAO::mtx;

RfcDAO::~RfcDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

RfcDAO * RfcDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new RfcDAO();
        dao->table = "rfc";
        dao->keyColumns = "rfccod";
        dao->columns = "rfccod,rfcrul,rfcmin,rfckmt"
                ",rfczon";
        dao->createQueries();
    }
    return dao;
}

vwze::entity::Rfc * RfcDAO::insert(tntdb::Connection & con, vwze::entity::Rfc * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<vwze::entity::Rfc *> RfcDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<vwze::entity::Rfc *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        vwze::entity::Rfc * e = new vwze::entity::Rfc;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

vwze::entity::Rfc * RfcDAO::read(tntdb::Connection & con, const long & rfccod) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    vwze::entity::Rfc * e = NULL;
    try {
        stmt.set("rfccodPK", rfccod);
        tntdb::Row row = stmt.selectRow();
        e = new vwze::entity::Rfc;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type RfcDAO::remove(tntdb::Connection & con, const long & rfccod) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("rfccodPK", rfccod);
    return stmt.execute();
}

vwze::entity::Rfc * RfcDAO::update(tntdb::Connection & con, vwze::entity::Rfc * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("rfccodPK", e->rfccod);
    stmt.execute();
    return e;
}

void RfcDAO::loadColumns(tntdb::Row & row, vwze::entity::Rfc * e) {
    int index = 0;
    e->rfccod = row.getInt64(index++);
    e->rfcrul = row.getString(index++);
    e->rfcmin = row.getDecimal(index++).getDouble();
    e->rfckmt = row.getInt(index++);
    e->rfczon = row.getString(index++);
}

void RfcDAO::setColumns(tntdb::Statement & stmt, const vwze::entity::Rfc * e) {
    stmt.setInt64("rfccod", e->rfccod);
    stmt.setString("rfcrul", e->rfcrul);
    stmt.setDouble("rfcmin", e->rfcmin);
    stmt.setInt("rfckmt", e->rfckmt);
    stmt.setString("rfczon", e->rfczon);
}


RfdDAO * RfdDAO::dao = NULL;
boost::mutex RfdDAO::mtx;

RfdDAO::~RfdDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

RfdDAO * RfdDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new RfdDAO();
        dao->table = "rfd";
        dao->keyColumns = "rfdcod";
        dao->columns = "rfdcod,rfdrfccod,rfdmin,rfdmef"
                ",rfdpun";
        dao->createQueries();
    }
    return dao;
}

vwze::entity::Rfd * RfdDAO::insert(tntdb::Connection & con, vwze::entity::Rfd * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<vwze::entity::Rfd *> RfdDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<vwze::entity::Rfd *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        vwze::entity::Rfd * e = new vwze::entity::Rfd;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

vwze::entity::Rfd * RfdDAO::read(tntdb::Connection & con, const long & rfdcod) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    vwze::entity::Rfd * e = NULL;
    try {
        stmt.set("rfdcodPK", rfdcod);
        tntdb::Row row = stmt.selectRow();
        e = new vwze::entity::Rfd;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type RfdDAO::remove(tntdb::Connection & con, const long & rfdcod) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("rfdcodPK", rfdcod);
    return stmt.execute();
}

vwze::entity::Rfd * RfdDAO::update(tntdb::Connection & con, vwze::entity::Rfd * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("rfdcodPK", e->rfdcod);
    stmt.execute();
    return e;
}

void RfdDAO::loadColumns(tntdb::Row & row, vwze::entity::Rfd * e) {
    int index = 0;
    e->rfdcod = row.getInt64(index++);
    e->rfdrfccod = row.getInt64(index++);
    e->rfdmin = row.getDecimal(index++).getDouble();
    e->rfdmef = row.getDecimal(index++).getDouble();
    e->rfdpun = row.getDecimal(index++).getDouble();
}

void RfdDAO::setColumns(tntdb::Statement & stmt, const vwze::entity::Rfd * e) {
    stmt.setInt64("rfdcod", e->rfdcod);
    stmt.setInt64("rfdrfccod", e->rfdrfccod);
    stmt.setDouble("rfdmin", e->rfdmin);
    stmt.setDouble("rfdmef", e->rfdmef);
    stmt.setDouble("rfdpun", e->rfdpun);
}


TodoDAO * TodoDAO::dao = NULL;
boost::mutex TodoDAO::mtx;

TodoDAO::~TodoDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

TodoDAO * TodoDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new TodoDAO();
        dao->table = "todo";
        dao->keyColumns = "documento";
        dao->columns = "documento,relevancia,fecha,orgpais"
                ",orgcp,orgzon,orgpob,despais,descp"
                ",deszon,despob,flujo,proveedor,planta"
                ",peso,volumen,pesofac,ruta,kcc"
                ",nombreprov";
        dao->createQueries();
    }
    return dao;
}

vwze::entity::Todo * TodoDAO::insert(tntdb::Connection & con, vwze::entity::Todo * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<vwze::entity::Todo *> TodoDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<vwze::entity::Todo *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        vwze::entity::Todo * e = new vwze::entity::Todo;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

vwze::entity::Todo * TodoDAO::read(tntdb::Connection & con, const std::string & documento) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    vwze::entity::Todo * e = NULL;
    try {
        stmt.set("documentoPK", documento);
        tntdb::Row row = stmt.selectRow();
        e = new vwze::entity::Todo;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type TodoDAO::remove(tntdb::Connection & con, const std::string & documento) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("documentoPK", documento);
    return stmt.execute();
}

vwze::entity::Todo * TodoDAO::update(tntdb::Connection & con, vwze::entity::Todo * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("documentoPK", e->documento);
    stmt.execute();
    return e;
}

void TodoDAO::loadColumns(tntdb::Row & row, vwze::entity::Todo * e) {
    int index = 0;
    e->documento = row.getString(index++);
    e->relevancia = row.getString(index++);
    e->fecha = row.getDatetime(index++);
    e->orgpais = row.getString(index++);
    e->orgcp = row.getString(index++);
    e->orgzon = row.getString(index++);
    e->orgpob = row.getString(index++);
    e->despais = row.getString(index++);
    e->descp = row.getString(index++);
    e->deszon = row.getString(index++);
    e->despob = row.getString(index++);
    e->flujo = row.getString(index++);
    e->proveedor = row.getString(index++);
    e->planta = row.getString(index++);
    e->peso = row.getInt(index++);
    e->volumen = row.getDecimal(index++).getDouble();
    e->pesofac = row.getInt(index++);
    e->ruta = row.getString(index++);
    e->kcc = row.getString(index++);
    e->nombreprov = row.getString(index++);
}

void TodoDAO::setColumns(tntdb::Statement & stmt, const vwze::entity::Todo * e) {
    stmt.setString("documento", e->documento);
    stmt.setString("relevancia", e->relevancia);
    stmt.set("fecha", e->fecha.getIso());
    stmt.setString("orgpais", e->orgpais);
    stmt.setString("orgcp", e->orgcp);
    stmt.setString("orgzon", e->orgzon);
    stmt.setString("orgpob", e->orgpob);
    stmt.setString("despais", e->despais);
    stmt.setString("descp", e->descp);
    stmt.setString("deszon", e->deszon);
    stmt.setString("despob", e->despob);
    stmt.setString("flujo", e->flujo);
    stmt.setString("proveedor", e->proveedor);
    stmt.setString("planta", e->planta);
    stmt.setInt("peso", e->peso);
    stmt.setDouble("volumen", e->volumen);
    stmt.setInt("pesofac", e->pesofac);
    stmt.setString("ruta", e->ruta);
    stmt.setString("kcc", e->kcc);
    stmt.setString("nombreprov", e->nombreprov);
}


VkostenDAO * VkostenDAO::dao = NULL;
boost::mutex VkostenDAO::mtx;

VkostenDAO::~VkostenDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

VkostenDAO * VkostenDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new VkostenDAO();
        dao->table = "vkosten";
        dao->keyColumns = "";
        dao->columns = "doccod,docrel,docexp,docfec"
                ",docorgzon,docorgpob,docdeszon,docdespob,docflu"
                ",docfab,docdun,docpro,dockcc,docpes"
                ",docvol,docpef,exped,relevanz,wewa"
                ",gebiet,sender,receiver,planta,transportista"
                ",escenario,menge,kosten,fratch";
        dao->createQueries();
    }
    return dao;
}

vwze::entity::Vkosten * VkostenDAO::insert(tntdb::Connection & con, vwze::entity::Vkosten * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<vwze::entity::Vkosten *> VkostenDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<vwze::entity::Vkosten *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        vwze::entity::Vkosten * e = new vwze::entity::Vkosten;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

void VkostenDAO::loadColumns(tntdb::Row & row, vwze::entity::Vkosten * e) {
    int index = 0;
    e->doccod = row.getInt64(index++);
    e->docrel = row.getString(index++);
    e->docexp = row.getString(index++);
    e->docfec = row.getDate(index++);
    e->docorgzon = row.getString(index++);
    e->docorgpob = row.getString(index++);
    e->docdeszon = row.getString(index++);
    e->docdespob = row.getString(index++);
    e->docflu = row.getString(index++);
    e->docfab = row.getString(index++);
    e->docdun = row.getString(index++);
    e->docpro = row.getString(index++);
    e->dockcc = row.getString(index++);
    e->docpes = row.getInt(index++);
    e->docvol = row.getDecimal(index++).getDouble();
    e->docpef = row.getInt(index++);
    e->exped = row.getString(index++);
    e->relevanz = row.getString(index++);
    e->wewa = row.getString(index++);
    e->gebiet = row.getString(index++);
    e->sender = row.getString(index++);
    e->receiver = row.getString(index++);
    e->planta = row.getString(index++);
    try {
        e->setTransportista(row.getString(index++));
    } catch (tntdb::NullValue) {
        e->setNullTransportista();
    }
    try {
        e->setEscenario(row.getString(index++));
    } catch (tntdb::NullValue) {
        e->setNullEscenario();
    }
    e->menge = row.getInt(index++);
    e->kosten = row.getDecimal(index++).getDouble();
    e->fratch = row.getDecimal(index++).getDouble();
}

void VkostenDAO::setColumns(tntdb::Statement & stmt, const vwze::entity::Vkosten * e) {
    stmt.setInt64("doccod", e->doccod);
    stmt.setString("docrel", e->docrel);
    stmt.setString("docexp", e->docexp);
    stmt.setDate("docfec", e->docfec);
    stmt.setString("docorgzon", e->docorgzon);
    stmt.setString("docorgpob", e->docorgpob);
    stmt.setString("docdeszon", e->docdeszon);
    stmt.setString("docdespob", e->docdespob);
    stmt.setString("docflu", e->docflu);
    stmt.setString("docfab", e->docfab);
    stmt.setString("docdun", e->docdun);
    stmt.setString("docpro", e->docpro);
    stmt.setString("dockcc", e->dockcc);
    stmt.setInt("docpes", e->docpes);
    stmt.setDouble("docvol", e->docvol);
    stmt.setInt("docpef", e->docpef);
    stmt.setString("exped", e->exped);
    stmt.setString("relevanz", e->relevanz);
    stmt.setString("wewa", e->wewa);
    stmt.setString("gebiet", e->gebiet);
    stmt.setString("sender", e->sender);
    stmt.setString("receiver", e->receiver);
    stmt.setString("planta", e->planta);
    if (e->isNullTransportista()) {
        stmt.setNull("transportista");
    } else {
        stmt.setString("transportista", e->getTransportista());
    }
    if (e->isNullEscenario()) {
        stmt.setNull("escenario");
    } else {
        stmt.setString("escenario", e->getEscenario());
    }
    stmt.setInt("menge", e->menge);
    stmt.setDouble("kosten", e->kosten);
    stmt.setDouble("fratch", e->fratch);
}


ZonDAO * ZonDAO::dao = NULL;
boost::mutex ZonDAO::mtx;

ZonDAO::~ZonDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

ZonDAO * ZonDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new ZonDAO();
        dao->table = "zon";
        dao->keyColumns = "zoncod";
        dao->columns = "zoncod,zondes,zonman,zontte";
        dao->createQueries();
    }
    return dao;
}

vwze::entity::Zon * ZonDAO::insert(tntdb::Connection & con, vwze::entity::Zon * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<vwze::entity::Zon *> ZonDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<vwze::entity::Zon *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        vwze::entity::Zon * e = new vwze::entity::Zon;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

vwze::entity::Zon * ZonDAO::read(tntdb::Connection & con, const std::string & zoncod) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    vwze::entity::Zon * e = NULL;
    try {
        stmt.set("zoncodPK", zoncod);
        tntdb::Row row = stmt.selectRow();
        e = new vwze::entity::Zon;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type ZonDAO::remove(tntdb::Connection & con, const std::string & zoncod) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("zoncodPK", zoncod);
    return stmt.execute();
}

vwze::entity::Zon * ZonDAO::update(tntdb::Connection & con, vwze::entity::Zon * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("zoncodPK", e->zoncod);
    stmt.execute();
    return e;
}

void ZonDAO::loadColumns(tntdb::Row & row, vwze::entity::Zon * e) {
    int index = 0;
    e->zoncod = row.getString(index++);
    e->zondes = row.getString(index++);
    e->zonman = row.getDecimal(index++).getDouble();
    e->zontte = row.getDecimal(index++).getDouble();
}

void ZonDAO::setColumns(tntdb::Statement & stmt, const vwze::entity::Zon * e) {
    stmt.setString("zoncod", e->zoncod);
    stmt.setString("zondes", e->zondes);
    stmt.setDouble("zonman", e->zonman);
    stmt.setDouble("zontte", e->zontte);
}


ZooDAO * ZooDAO::dao = NULL;
boost::mutex ZooDAO::mtx;

ZooDAO::~ZooDAO() {
    if (dao != NULL) {
        delete dao;
    }
}

ZooDAO * ZooDAO::getInstance(void) {
    boost::mutex::scoped_lock lock(mtx);
    if (dao == NULL) {
        dao = new ZooDAO();
        dao->table = "zoo";
        dao->keyColumns = "zoocod";
        dao->columns = "zoocod,zoozoncod,zoopcp";
        dao->createQueries();
    }
    return dao;
}

vwze::entity::Zoo * ZooDAO::insert(tntdb::Connection & con, vwze::entity::Zoo * e) {
    tntdb::Statement stmt = con.prepare(getInsertQuery());
    setColumns(stmt, e);
    stmt.execute();
    return e;
}

std::list<vwze::entity::Zoo *> ZooDAO::query(tntdb::Connection & con, tntdb::Statement & stmt) {
    std::list<vwze::entity::Zoo *> es;
    for (tntdb::Statement::const_iterator it = stmt.begin(); it != stmt.end(); ++it) {
        vwze::entity::Zoo * e = new vwze::entity::Zoo;
        tntdb::Row row = *it;
        loadColumns(row, e);
        es.push_back(e);
    }
    return es;
}

vwze::entity::Zoo * ZooDAO::read(tntdb::Connection & con, const long & zoocod) {
    tntdb::Statement stmt = con.prepare(getReadQuery());
    vwze::entity::Zoo * e = NULL;
    try {
        stmt.set("zoocodPK", zoocod);
        tntdb::Row row = stmt.selectRow();
        e = new vwze::entity::Zoo;
        loadColumns(row, e);
    } catch (tntdb::NotFound) {
    }
    return e;
}

tntdb::Statement::size_type ZooDAO::remove(tntdb::Connection & con, const long & zoocod) {
    tntdb::Statement stmt = con.prepare(getRemoveQuery());
    stmt.set("zoocodPK", zoocod);
    return stmt.execute();
}

vwze::entity::Zoo * ZooDAO::update(tntdb::Connection & con, vwze::entity::Zoo * e) {
    tntdb::Statement stmt = con.prepare(getUpdateQuery());
    setColumns(stmt, e);
    stmt.set("zoocodPK", e->zoocod);
    stmt.execute();
    return e;
}

void ZooDAO::loadColumns(tntdb::Row & row, vwze::entity::Zoo * e) {
    int index = 0;
    e->zoocod = row.getInt64(index++);
    e->zoozoncod = row.getString(index++);
    e->zoopcp = row.getString(index++);
}

void ZooDAO::setColumns(tntdb::Statement & stmt, const vwze::entity::Zoo * e) {
    stmt.setInt64("zoocod", e->zoocod);
    stmt.setString("zoozoncod", e->zoozoncod);
    stmt.setString("zoopcp", e->zoopcp);
}

