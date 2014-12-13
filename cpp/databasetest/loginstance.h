#ifndef LOGINSTANCE_H
#define LOGINSTANCE_H
#include <stdio.h>
#include "commondefine.h"
class CLogInstance
{
 public:
    CLogInstance(FILE *filep);  
    ~CLogInstance();
 public:
    void printf(const char *format,...);
    
 public:
    FILE *m_filep;
};


#endif /* LOGINSTANCE_H */
