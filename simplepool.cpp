#include "simplepool.h"

simplepool::simplepool(unsigned long musize,unsigned long munum):
    mpAddr(NULL), allocaddr(NULL), freeaddr(NULL),
    memBlockSize(munum * (musize+sizeof(struct memUnit))),
    memUnitSize(musize)
{
    mpAddr=malloc(memBlockSize);
    if(mpAddr!=NULL){
        for (int i=0;i<munum;i++){
            struct memUnit  *curPointer=(struct memUnit*)(i*(musize+sizeof(struct memUnit))+(char*)mpAddr);// don't understand
            curPointer->prev=NULL;
            curPointer->next=freeaddr;
            if(freeaddr!= NULL){
                freeaddr->prev=curPointer;
            }
            freeaddr=curPointer;
        }
    }

}
simplepool::~simplepool(){
    delete(mpAddr);
}

void* simplepool::Allocate(unsigned long ulSize, bool bUseMemPool){
    if (bUseMemPool!=true||ulSize>memUnitSize||freeaddr==NULL||mpAddr==NULL){
        return (void*)malloc(ulSize);
    }
    struct memUnit* curPointer=freeaddr;
    freeaddr=freeaddr->next;
    if (freeaddr!=NULL) freeaddr->prev=NULL;
    curPointer->next=allocaddr;
    if(allocaddr!=NULL){
       allocaddr->prev=curPointer;
    }
    allocaddr=curPointer;

    return (void*)((char*)curPointer+sizeof(struct memUnit));

}

void simplepool::Free(void* p){
    if (mpAddr<p && p<(memBlockSize+(char*)mpAddr)){
        struct memUnit* curPointer=(struct memUnit*)((char*)p-sizeof(struct memUnit));

        if(curPointer!=allocaddr ){
            struct memUnit* tempt=curPointer->prev;
            if(tempt!=NULL){
                tempt->next=curPointer->next;
            }
            if(curPointer->next!=NULL){
            curPointer->next->prev=tempt;}
        }else{
            allocaddr=curPointer->next;
            if(allocaddr!=NULL){allocaddr->prev=NULL;}
        }
        curPointer->next=freeaddr;
        if(freeaddr!=NULL){
            freeaddr->prev=curPointer;
        }
        freeaddr=curPointer;

    }else{
        delete(p);
    }


}

