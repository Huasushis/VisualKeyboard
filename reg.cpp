#include "reg.h"

bool Reg::is_ok()
{
    ifstream ifs;
    ifs.open("vk.ini", ios::in);
    if (!ifs.is_open())
    {
        ifs.close();
        return 0;
    }
    char c;
    ifs >> c;
    if (ifs.eof())
    {
        ifs.close();
        return 0;
    }
    ifs.close();
    return 1;
}

void Reg::StringToWstring(std::string& szDst, wchar_t*wchar)
{
    wchar_t * wText = wchar;
    DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,wText,-1,NULL,0,NULL,FALSE);//WideCharToMultiByte的运用
    char *psText;  // psText为char*的临时数组，作为赋值给std::string的中间变量
    psText = new char[dwNum];
    WideCharToMultiByte (CP_OEMCP,NULL,wText,-1,psText,dwNum,NULL,FALSE);//WideCharToMultiByte的再次运用
    szDst = psText;// std::string赋值
    delete []psText;// psText的清除
}

void Reg::init()
{
    ofstream tmp("vk.ini");
    wchar_t dp[MAX_PATH];
    CMyINI *tt=new CMyINI();
    tt->SetValue("Orig","self-starting","false");
    GetModuleFileName(NULL,dp,MAX_PATH);
    string noname;
    StringToWstring(noname,dp);
    tt->SetValue("Orig","path",noname);
    tt->SetValue("Orig","start","false");
    tt->SetValue("Orig","show_message","true");
    tt->SetValue("WinSetting","bgColor","#ff000000");
    tt->SetValue("WinSetting","wdColor","#ffffffff");
    tt->SetValue("WinSetting","posx","0");
    tt->SetValue("WinSetting","posy","0");
    tt->WriteINI("vk.ini");
}

Reg::Reg()
{
    if(!is_ok()) init();
    p=new CMyINI();
    p->ReadINI("vk.ini");
    string path,start,self_starting,np;
    wchar_t npp[MAX_PATH];
    path=p->GetValue("Orig","path");
    self_starting=p->GetValue("Orig","self-starting");
    GetModuleFileName(NULL,npp,MAX_PATH);
    StringToWstring(np,npp);
    if(np!=path){
        p->SetValue("Orig","path",np);
        if(self_starting=="true"){
            change(0);
            p->SetValue("Orig","self-starting","false");
        }
    }
    p->WriteINI("vk.ini");
}

bool Reg::check(int what)
{
    p->ReadINI("vk.ini");
    switch(what){
    case 0: return p->GetValue("Orig","start")==string("true");
    case 1: return p->GetValue("Orig","self-starting")==string("true");
    case 2: return p->GetValue("Orig","show_message")==string("true");
    }
    return 0;
}

string Reg::checkinf(int what)
{
    p->ReadINI("vk.ini");
    switch(what){
    case 0: return p->GetValue("WinSetting","bgColor");
    case 1: return p->GetValue("WinSetting","wdColor");
    case 2: return p->GetValue("WinSetting","posx");
    case 3: return p->GetValue("WinSetting","posy");
    }
    return "\0";
}
void Reg::change(bool to)
{
    if(to){
        HKEY hKey;
        wchar_t strRegPath[] = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

            //1、找到系统的启动项
        if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) ///打开启动项
        {
                //2、得到本程序自身的全路径
            TCHAR strExeFullDir[MAX_PATH];
            GetModuleFileName(NULL, strExeFullDir, MAX_PATH);

                //3、判断注册表项是否已经存在
            TCHAR strDir[MAX_PATH] = {};
            DWORD nLength = MAX_PATH;
            long result = RegGetValue(hKey, nullptr, L"VisualKeyboard", RRF_RT_REG_SZ, 0, strDir, &nLength);

                //4、已经存在
            if (result != ERROR_SUCCESS || _tcscmp(strExeFullDir, strDir) != 0)
            {
                    //5、添加一个子Key,并设置值，"VisualKeyboard"是应用程序名字（不加后缀.exe）
                RegSetValueEx(hKey, L"VisualKeyboard", 0, REG_SZ, (LPBYTE)strExeFullDir, (lstrlen(strExeFullDir) + 1)*sizeof(TCHAR));

                    //6、关闭注册表
                RegCloseKey(hKey);
            }
        }
        else
        {
            throw 1;

        }
    }
    else{
        HKEY hKey;
        wchar_t strRegPath[] = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

            //1、找到系统的启动项
        if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
        {
                //2、删除值
            RegDeleteValue(hKey, L"VisualKeyboard");

                //3、关闭注册表
            RegCloseKey(hKey);
        }
    }
}

BOOL Reg::EnableDebugPrivilege() {
    HANDLE hToken;
    LUID sedebugnameValue;
    TOKEN_PRIVILEGES tkp;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        return   FALSE;
    }
    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue))
    {
        CloseHandle(hToken);
        return false;
    }
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Luid = sedebugnameValue;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL))
    {
        CloseHandle(hToken);
        return false;
    }
    return true;
}
Reg::~Reg() = default;
