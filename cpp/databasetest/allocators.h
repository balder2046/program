#ifndef ALLOCATORS_H
#define ALLOCATORS_H
#include "stdlib.h"
class AllocatorBase
{
public:
    AllocatorBase()
        {

        }
    virtual ~AllocatorBase()
        {

        }
public:
    virtual void *Alloc(size_t size) = 0;
    virtual void Free(void *ptr) = 0;
public:
    static AllocatorBase *GetDefaultAllocator();
};

class DefaultAllocator : public AllocatorBase
{
    virtual void *Alloc(size_t size);
    virtual void Free(void *ptr);
};


#endif /* ALLOCATORS_H */
