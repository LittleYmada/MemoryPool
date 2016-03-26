
#ifndef MEMPOOL
#define MEMPOOL
#include<iostream>
#include<stdlib.h>
class simplepool{
private:
    struct memUnit{
        struct memUnit *prev;
        struct memUnit *next;
    } ;
    void*  mpAddr;
    unsigned long memUnitSize;
    unsigned long memBlockSize;
    struct memUnit* allocaddr;
    struct memUnit* freeaddr;
public:
    simplepool(unsigned long musize=1024,unsigned long munum=50);
    ~simplepool();
    void* Allocate(unsigned long ulSize, bool bUseMemPool = true);
    void Free(void* p);

};



#endif
