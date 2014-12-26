#include "mysqldatabasep.h"
#include "stdio.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/prepared_statement.h"
CMySqlDataBasePlus::CMySqlDataBasePlus()
{
    m_driver = get_driver_instance();
    m_connection = NULL;
    m_stmt = NULL;
    m_prestmt.reset(NULL);
}

CMySqlDataBasePlus::~CMySqlDataBasePlus()
{
    m_prestmt.release();
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
        m_prestmt.reset(m_connection->prepareStatement("call _LDBI_CreateUserCore(?,?,@retcode)"));
        m_prestmt->clearParameters();
        onConnected();
        
        
    
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
    SAFE_DELETE(m_stmt);
    SAFE_DELETE(m_connection);
    
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
    
void CMySqlDataBasePlus::Test(const std::string &name)
{

    if (name == "proc")
    {
        if (!m_prestmt.get()) return ;
      
        m_prestmt->clearParameters();
        m_prestmt->setString(1, "zhangsan");

        m_prestmt->setString(2,"111111");
        m_logInst->LogInfo("Start Call Procedure ....");
        m_prestmt->execute();
        
        std::auto_ptr<sql::ResultSet> res(m_stmt->executeQuery("select @retcode as ret;"));
        res->first();
        m_logInst->LogInfo("return code %d",res->getInt(1));        
    }
}
