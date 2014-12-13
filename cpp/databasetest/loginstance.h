#ifndef LOGINSTANCE_H
#define LOGINSTANCE_H
#include <stdio.h>
#include "commondefine.h"
class CLogInstance
{
 public:
    enum {LOG_INFO = 0,LOG_WARNNING = 1,LOG_ERROR = 2};
 public:
    CLogInstance(FILE *filep);  
    ~CLogInstance();
 public:
    void printf(const char *format,...);
    void Log(int error,const char *format,...);
    void LogError(const char *format,...);
    void LogWarnning(const char *format,...);
    void LogInfo(const char *format,...);
 private:
    void LogV(int error,const char *format,va_list args);


    
 public:
    FILE *m_filep;
};


#endif /* LOGINSTANCE_H */
