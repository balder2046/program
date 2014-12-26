#ifndef LDBIDATABASE_H
#define LDBIDATABASE_H
#include <string>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "mysqldatabasep.h"
#include <map>
class CProcedureBase
{
public:
    std::string name;
    sql::PreparedStatement *m_state;
    
};



class CLdbiDataBase : public CMySqlDataBasePlus
{
public:
    class CProcedureInfo
    {
    public:
        std::string sqlReturn;
        sql::PreparedStatement *m_stmt;  
    };
public:
    CLdbiDataBase();
    virtual ~CLdbiDataBase();
public:
    bool CreateUser(const std::string &name,const std::string &password,int &nCode);

    void CloseDB();
protected:
    void onConnected();
private:
    void addProcedure(const std::string &name,const std::string &procstatement,const std::string &retstatement);
protected:
    std::map<std::string,CProcedureInfo *> m_mapState;
};

CLdbiDataBase *CreateLDBIDataBase(CLogInstance *inst);


#endif /* LDBIDATABASE_H */
