#include "mysqldatabasep.h"
#include "stdio.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
CMySqlDataBasePlus::CMySqlDataBasePlus()
{
    m_driver = get_driver_instance();
    m_connection = NULL;
    m_stmt = NULL;
}

CMySqlDataBasePlus::~CMySqlDataBasePlus()
{
    if (m_stmt)
    {
        delete m_stmt;
        m_stmt = NULL;
    }
    if (m_connection)
    {
        delete m_connection;
        m_connection = NULL;
    }
}
int CMySqlDataBasePlus::Connect(const std::string &ipaddr,unsigned int port,const std::string &username,const std::string &password,const std::string &dbname)
{
    char szBuf[128];
    snprintf(szBuf,128,"tcp://%s:%d",ipaddr.c_str(),port);
    m_logInst->LogInfo("%s", szBuf);
    try
    {
        m_connection = m_driver->connect(szBuf,username.c_str(),password.c_str());
        m_connection->setSchema(dbname.c_str());
        m_stmt = m_connection->createStatement();
    
    }
    catch (sql::SQLException &e)
    {
        m_logInst->LogInfo("Exception %s : %d errorreason:%s",__FILE__,__LINE__,e.what());
    }
    m_logInst->LogInfo("Connect DB OK!");
    return 0;
}
void CMySqlDataBasePlus::CloseDB()
{
    m_logInst->LogInfo("Close DB ......");
    if (m_stmt)
    {
        delete m_stmt;
        m_stmt = NULL;
    }
    if (m_connection)
    {
        m_connection->close();
        delete m_connection;
        m_connection = NULL;
    }
}
//About the Logs
bool CMySqlDataBasePlus::Query(const std::string &sql)
{
    if (!m_stmt) return false;
    try
    {
        m_logInst->LogInfo("Query %s",sql.c_str());
        //m_stmt->executeQuery(sql.c_str());
        m_stmt->execute(sql.c_str());
        m_logInst->LogInfo("Query OK");
    }
    catch(sql::SQLException &e)
    {
        m_logInst->LogInfo("Exception %s : %d errorreason: %s",__FILE__,__LINE__,e.what());
    }
    
    return true;
}
    
