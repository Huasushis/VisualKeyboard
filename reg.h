#ifndef REG_H
#define REG_H
#include "cmyini.h"
#include <windows.h>
#include <tchar.h>
using namespace std;

class Reg
{
private:

    void init();
    bool is_ok();
    void StringToWstring(std::string& szDst, wchar_t*wchar);
public:
    CMyINI *p;
    Reg();
    ~Reg();
    bool check(int what);
    string checkinf(int what);
    void change(bool to);
    BOOL EnableDebugPrivilege();
};

#endif // REG_H
