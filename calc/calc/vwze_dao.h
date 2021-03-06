#ifndef VWZE_DAO_H
#define VWZE_DAO_H
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <tntdb/connection.h>
#include <tntdb/statement.h>
#include "vwze_entity.h"
namespace vwze {
  namespace dao {
        
class CommonDAO {
private:
    std::string insertQuery;
    std::string readQuery;
    std::string removeQuery;
    std::string updateQuery;
protected:
    std::string table;
    std::string keyColumns;
    std::string columns;
    void createQueries(void);
public:
    std::string getInsertQuery(void);
    std::string getReadQuery(void);
    std::string getRemoveQuery(void);
    std::string getUpdateQuery(void);
    std::string getColumns(void);
    std::string getTable(void);
};    


class DocDAO : public CommonDAO {
private:
    static DocDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, vwze::entity::Doc *);
    void setColumns(tntdb::Statement &, const vwze::entity::Doc *);
public:
    ~DocDAO();
    static DocDAO * getInstance(void);
    vwze::entity::Doc * insert(tntdb::Connection &, vwze::entity::Doc *);
    std::list<vwze::entity::Doc *> query(tntdb::Connection &, tntdb::Statement &);
    vwze::entity::Doc * read(tntdb::Connection &, const long &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const long &);
    vwze::entity::Doc * update(tntdb::Connection &, vwze::entity::Doc *);
};

class DodDAO : public CommonDAO {
private:
    static DodDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, vwze::entity::Dod *);
    void setColumns(tntdb::Statement &, const vwze::entity::Dod *);
public:
    ~DodDAO();
    static DodDAO * getInstance(void);
    vwze::entity::Dod * insert(tntdb::Connection &, vwze::entity::Dod *);
    std::list<vwze::entity::Dod *> query(tntdb::Connection &, tntdb::Statement &);
    vwze::entity::Dod * read(tntdb::Connection &, const long &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const long &);
    vwze::entity::Dod * update(tntdb::Connection &, vwze::entity::Dod *);
};

class DoeDAO : public CommonDAO {
private:
    static DoeDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, vwze::entity::Doe *);
    void setColumns(tntdb::Statement &, const vwze::entity::Doe *);
public:
    ~DoeDAO();
    static DoeDAO * getInstance(void);
    vwze::entity::Doe * insert(tntdb::Connection &, vwze::entity::Doe *);
    std::list<vwze::entity::Doe *> query(tntdb::Connection &, tntdb::Statement &);
    vwze::entity::Doe * read(tntdb::Connection &, const long &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const long &);
    vwze::entity::Doe * update(tntdb::Connection &, vwze::entity::Doe *);
};

class EltDAO : public CommonDAO {
private:
    static EltDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, vwze::entity::Elt *);
    void setColumns(tntdb::Statement &, const vwze::entity::Elt *);
public:
    ~EltDAO();
    static EltDAO * getInstance(void);
    vwze::entity::Elt * insert(tntdb::Connection &, vwze::entity::Elt *);
    std::list<vwze::entity::Elt *> query(tntdb::Connection &, tntdb::Statement &);
    vwze::entity::Elt * read(tntdb::Connection &, const int &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const int &);
    vwze::entity::Elt * update(tntdb::Connection &, vwze::entity::Elt *);
};

class FltDAO : public CommonDAO {
private:
    static FltDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, vwze::entity::Flt *);
    void setColumns(tntdb::Statement &, const vwze::entity::Flt *);
public:
    ~FltDAO();
    static FltDAO * getInstance(void);
    vwze::entity::Flt * insert(tntdb::Connection &, vwze::entity::Flt *);
    std::list<vwze::entity::Flt *> query(tntdb::Connection &, tntdb::Statement &);
};

class KccDAO : public CommonDAO {
private:
    static KccDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, vwze::entity::Kcc *);
    void setColumns(tntdb::Statement &, const vwze::entity::Kcc *);
public:
    ~KccDAO();
    static KccDAO * getInstance(void);
    vwze::entity::Kcc * insert(tntdb::Connection &, vwze::entity::Kcc *);
    std::list<vwze::entity::Kcc *> query(tntdb::Connection &, tntdb::Statement &);
    vwze::entity::Kcc * read(tntdb::Connection &, const std::string &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const std::string &);
    vwze::entity::Kcc * update(tntdb::Connection &, vwze::entity::Kcc *);
};

class KostenDAO : public CommonDAO {
private:
    static KostenDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, vwze::entity::Kosten *);
    void setColumns(tntdb::Statement &, const vwze::entity::Kosten *);
public:
    ~KostenDAO();
    static KostenDAO * getInstance(void);
    vwze::entity::Kosten * insert(tntdb::Connection &, vwze::entity::Kosten *);
    std::list<vwze::entity::Kosten *> query(tntdb::Connection &, tntdb::Statement &);
    vwze::entity::Kosten * read(tntdb::Connection &, const std::string &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const std::string &);
    vwze::entity::Kosten * update(tntdb::Connection &, vwze::entity::Kosten *);
};

class ProDAO : public CommonDAO {
private:
    static ProDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, vwze::entity::Pro *);
    void setColumns(tntdb::Statement &, const vwze::entity::Pro *);
public:
    ~ProDAO();
    static ProDAO * getInstance(void);
    vwze::entity::Pro * insert(tntdb::Connection &, vwze::entity::Pro *);
    std::list<vwze::entity::Pro *> query(tntdb::Connection &, tntdb::Statement &);
    vwze::entity::Pro * read(tntdb::Connection &, const std::string &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const std::string &);
    vwze::entity::Pro * update(tntdb::Connection &, vwze::entity::Pro *);
};

class RfcDAO : public CommonDAO {
private:
    static RfcDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, vwze::entity::Rfc *);
    void setColumns(tntdb::Statement &, const vwze::entity::Rfc *);
public:
    ~RfcDAO();
    static RfcDAO * getInstance(void);
    vwze::entity::Rfc * insert(tntdb::Connection &, vwze::entity::Rfc *);
    std::list<vwze::entity::Rfc *> query(tntdb::Connection &, tntdb::Statement &);
    vwze::entity::Rfc * read(tntdb::Connection &, const long &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const long &);
    vwze::entity::Rfc * update(tntdb::Connection &, vwze::entity::Rfc *);
};

class RfdDAO : public CommonDAO {
private:
    static RfdDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, vwze::entity::Rfd *);
    void setColumns(tntdb::Statement &, const vwze::entity::Rfd *);
public:
    ~RfdDAO();
    static RfdDAO * getInstance(void);
    vwze::entity::Rfd * insert(tntdb::Connection &, vwze::entity::Rfd *);
    std::list<vwze::entity::Rfd *> query(tntdb::Connection &, tntdb::Statement &);
    vwze::entity::Rfd * read(tntdb::Connection &, const long &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const long &);
    vwze::entity::Rfd * update(tntdb::Connection &, vwze::entity::Rfd *);
};

class SendungsdateDAO : public CommonDAO {
private:
    static SendungsdateDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, vwze::entity::Sendungsdate *);
    void setColumns(tntdb::Statement &, const vwze::entity::Sendungsdate *);
public:
    ~SendungsdateDAO();
    static SendungsdateDAO * getInstance(void);
    vwze::entity::Sendungsdate * insert(tntdb::Connection &, vwze::entity::Sendungsdate *);
    std::list<vwze::entity::Sendungsdate *> query(tntdb::Connection &, tntdb::Statement &);
    vwze::entity::Sendungsdate * read(tntdb::Connection &, const std::string &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const std::string &);
    vwze::entity::Sendungsdate * update(tntdb::Connection &, vwze::entity::Sendungsdate *);
};

class TransportDAO : public CommonDAO {
private:
    static TransportDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, vwze::entity::Transport *);
    void setColumns(tntdb::Statement &, const vwze::entity::Transport *);
public:
    ~TransportDAO();
    static TransportDAO * getInstance(void);
    vwze::entity::Transport * insert(tntdb::Connection &, vwze::entity::Transport *);
    std::list<vwze::entity::Transport *> query(tntdb::Connection &, tntdb::Statement &);
    vwze::entity::Transport * read(tntdb::Connection &, const int &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const int &);
    vwze::entity::Transport * update(tntdb::Connection &, vwze::entity::Transport *);
};

class ZonDAO : public CommonDAO {
private:
    static ZonDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, vwze::entity::Zon *);
    void setColumns(tntdb::Statement &, const vwze::entity::Zon *);
public:
    ~ZonDAO();
    static ZonDAO * getInstance(void);
    vwze::entity::Zon * insert(tntdb::Connection &, vwze::entity::Zon *);
    std::list<vwze::entity::Zon *> query(tntdb::Connection &, tntdb::Statement &);
    vwze::entity::Zon * read(tntdb::Connection &, const std::string &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const std::string &);
    vwze::entity::Zon * update(tntdb::Connection &, vwze::entity::Zon *);
};

class ZooDAO : public CommonDAO {
private:
    static ZooDAO * dao;
    static boost::mutex mtx;
    void loadColumns(tntdb::Row &, vwze::entity::Zoo *);
    void setColumns(tntdb::Statement &, const vwze::entity::Zoo *);
public:
    ~ZooDAO();
    static ZooDAO * getInstance(void);
    vwze::entity::Zoo * insert(tntdb::Connection &, vwze::entity::Zoo *);
    std::list<vwze::entity::Zoo *> query(tntdb::Connection &, tntdb::Statement &);
    vwze::entity::Zoo * read(tntdb::Connection &, const long &);
    tntdb::Statement::size_type remove(tntdb::Connection &, const long &);
    vwze::entity::Zoo * update(tntdb::Connection &, vwze::entity::Zoo *);
};
  }
}
#endif
