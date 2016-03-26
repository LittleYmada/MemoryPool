#include <windows.h>
#include <iostream>
#include "simplepool.h"
#include "CMemPool.h"
/*char buf[4100];
class CTestClass
{
    char m_chBuf[4096];
};

class SimplePool{
    char m_buffer[4096];
public:
    void *operator new(unsigned int uiSie){
        return (void *)buf;
    }
    void operator delete(void *p)
    {

    }
};*/
int main()
{
    DWORD count = GetTickCount();
    simplepool spool(4100,200);

    for(unsigned int i=0; i<10000000; i++)
    {
        char *p = (char*)spool.Allocate(4096);
        spool.Free(p);
    }

    std::cout << "Interval = " << GetTickCount()-count << " ms" <<std:: endl;
    count = GetTickCount();

    for(unsigned int i=0; i<0xffffff; i++)
    {
        char *p = new char[4096];
        delete(p);
    }
     std::cout << "Interval = " << GetTickCount()-count << " ms" <<std:: endl;
    return 0;
}
