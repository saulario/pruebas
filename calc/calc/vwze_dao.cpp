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
                ",docfab,docdun,docpro";
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
        dao->columns = "zoncod,zondes";
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
}

void ZonDAO::setColumns(tntdb::Statement & stmt, const vwze::entity::Zon * e) {
    stmt.setString("zoncod", e->zoncod);
    stmt.setString("zondes", e->zondes);
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

