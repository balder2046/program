#ifndef MYSQLDATABASEP_H
#define MYSQLDATABASEP_H
#include "databaseclient.h"
#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"
#include <memory.h>
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
    virtual void Test(const std::string &name);
    
    
private:
    sql::Driver *m_driver;
    
    
    std::auto_ptr<sql::PreparedStatement> m_prestmt;
protected:
    sql::Statement *m_stmt;
    sql::Connection *m_connection;
    
};



#endif /* MYSQLDATABASEP_H */
