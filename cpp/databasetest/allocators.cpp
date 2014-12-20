#include "allocators.h"
#include "stdlib.h"
static DefaultAllocator g_Allocator;
AllocatorBase *AllocatorBase::GetDefaultAllocator()
{
    return &g_Allocator;
}



void *DefaultAllocator::Alloc(size_t size)
{
    return malloc(size);
}
void DefaultAllocator::Free(void *ptr)
{
    if (ptr)
    {
        free(ptr);
    }
}
