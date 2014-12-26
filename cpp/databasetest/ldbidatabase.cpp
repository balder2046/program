#include "ldbidatabase.h"
CLdbiDataBase *CreateLDBIDataBase(CLogInstance *inst)
{
    CLdbiDataBase *base = new CLdbiDataBase;
    base->SetLogInstance(inst);
    return base;
}
CLdbiDataBase::CLdbiDataBase()
{
    
}
CLdbiDataBase::~CLdbiDataBase()
{

    
}
void CLdbiDataBase::addProcedure(const std::string &name,const std::string &procstatement,const std::string &retstatement)
{
    CProcedureInfo *info = new CProcedureInfo();
    info->sqlReturn = retstatement;
    sql::PreparedStatement *stmt = m_connection->prepareStatement(procstatement);
    info->m_stmt = stmt;
    m_mapState[name] = info;
}
void CLdbiDataBase::onConnected()
{
    addProcedure("CreateUser","call _LDBI_CreateUserCore(?,?,@retcode);","select @retcode;");
}
void CLdbiDataBase::CloseDB()
{
    for (auto iter = m_mapState.begin(); iter != m_mapState.end(); ++iter)
    {
        SAFE_DELETE(iter->second);
    }
    return CMySqlDataBasePlus::CloseDB();
}
bool CLdbiDataBase::CreateUser(const std::string &username, const std::string &password, int &ncode)
{
    CProcedureInfo *pInfo = NULL;
    ncode = -1;
    auto iter = m_mapState.find("CreateUser");
    if (iter == m_mapState.end())
    {
        return false;
    }
    pInfo = iter->second;
    sql::PreparedStatement *pstate = pInfo->m_stmt;
    ncode = 0;
    pstate->setString(1,username);
    pstate->setString(2, password);
    //no need the out parameter
    pstate->execute();
    m_logInst->LogInfo("query sql %s",pInfo->sqlReturn.c_str());
    sql::ResultSet *res = m_stmt->executeQuery(pInfo->sqlReturn);
    res->first();
    ncode = res->getInt(1);
    delete res;
    return true;
}
