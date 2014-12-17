#ifndef RESULTDATA_H
#define RESULTDATA_H
#include <list>
#include "rowdata.h"

class CResultData
{
public:
    typedef std::list<rowdata> LIST_ROWDATA;
public:
    CResultData();
    virtual ~CResultData();
public:
};



#endif /* RESULTDATA_H */
