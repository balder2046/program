#ifndef MYSQLDATABASEP_H
#define MYSQLDATABASEP_H
#include "databaseclient.h"
#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/statement.h"
class CMySqlDataBasePlus : public CDataBaseClient
{
public:
    CMySqlDataBasePlus();
    virtual ~CMySqlDataBasePlus();
public:
    virtual int Connect(const std::string &ipaddr,unsigned int port,const std::string &username,const std::string &password,const std::string &dbname);
    virtual void CloseDB();
    //About the Logs
    virtual bool Query(const std::string &sql);
    
    
private:
    sql::Driver *m_driver;
    sql::Connection *m_connection;
    sql::Statement *m_stmt;
};



#endif /* MYSQLDATABASEP_H */
