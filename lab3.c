#include <stdio.h>
#include <Windows.h>
#include <tlhelp32.h>
#include <malloc.h>
#include <conio.h>

void trace(const char* msg)
{
    printf("%s\n", msg);
}

void traceW(const wchar_t* msg)
{
    printf("%ls\n", msg);
}

void wait_any_key()
{
    while (!_kbhit()) {
        Sleep(1);
    }
}

void pressAnyKey()
{
    trace("Press any key...");
    wait_any_key();
}

char* StrFloat(char* str, double v, int m)
{
    sprintf_s(str, 256, "%0.3f", v);
    return str;
}

char* StrUInt(char* str, DWORD v)
{
    sprintf_s(str, 256, "%d", v);
    return str;
}

char* StrValueUInt(char* str, const char* title, DWORD v)
{
    sprintf_s(str, 256, "%s: %d", title, v);
    return str;
}

unsigned int getAllPIDs(PROCESSENTRY32* list, unsigned maxCount)
{
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnap == INVALID_HANDLE_VALUE)
        return 0;

    unsigned result = 0;

    PROCESSENTRY32 pr32;
    pr32.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hProcessSnap, &pr32))
    { 
        for (unsigned ok = 1; ok;)
        {
            if (!list)
                ++result;
            else if (result < maxCount) {
                *list++ = pr32;
                ++result;
            }

            ok = Process32Next(hProcessSnap, &pr32);
        }

        CloseHandle(hProcessSnap);
    }

    return result;
}

unsigned int getAllThreads(DWORD pid, THREADENTRY32* list, unsigned maxCount)
{
    HANDLE hThreadsSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pid);

    if (hThreadsSnap == INVALID_HANDLE_VALUE)
        return 0;

    unsigned result = 0;

    THREADENTRY32 th32;
    th32.dwSize = sizeof(THREADENTRY32);
    if (Thread32First(hThreadsSnap, &th32))
    { 
        for (unsigned ok = 1; ok;)
        {
            if (!list)
                ++result;
            else if (result < maxCount) {
                *list++ = th32;
                ++result;
            }
            
            ok = Thread32Next(hThreadsSnap, &th32);
        }

        CloseHandle(hThreadsSnap);
    }

    return result;
}
unsigned int getAllModules(DWORD pid, MODULEENTRY32* list, unsigned maxCount)
{
    HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);

    if (hModuleSnap == INVALID_HANDLE_VALUE)
        return 0;

    unsigned result = 0;

    MODULEENTRY32 md32;
    md32.dwSize = sizeof(MODULEENTRY32);
    if (Module32First(hModuleSnap, &md32))
    { 
        for (unsigned ok = 1; ok;)
        {
            if (!list)
            ++result;
            else if (result < maxCount) {
                *list++ = md32;
                ++result;
            }
            
            ok = Module32Next(hModuleSnap, &md32);
        }

        CloseHandle(hModuleSnap);
    }

    return result;
}

void printThreads(DWORD pid)
{
    #define MAX_COUNT 32
    THREADENTRY32 ths[MAX_COUNT];

    unsigned int count = getAllThreads(pid, ths, MAX_COUNT);

    for (unsigned i = 0; i < count; ++i)
    {
        char str[256];
        trace(StrValueUInt(str, "\t\tthread ID", ths[i].th32ThreadID));
        trace(StrValueUInt(str, "\t\tpriority", ths[i].tpBasePri));
    }
}

void printAllModules(DWORD pid)
{
    unsigned count = getAllModules(pid, NULL, 0);

    MODULEENTRY32* mdl = malloc(count * sizeof(MODULEENTRY32));

    unsigned countMd = getAllModules(pid, mdl, count);

    for (unsigned i = 0; i < count; ++i)
    {
        char str[256];
        printf("\n\path: ");
        traceW(mdl[i].szExePath);
        trace(StrValueUInt(str, "count of modules", mdl[i].GlblcntUsage));
        trace(StrValueUInt(str, "size", mdl[i].modBaseSize));
    }


}

int main()
{
    unsigned maxCount = getAllPIDs(NULL, 0);

    if (!maxCount)
    {
        trace("PIDS is empty.");
        return -1;
    }

    maxCount += 10;
    PROCESSENTRY32* pids = malloc(maxCount * sizeof(PROCESSENTRY32));

    unsigned countPr = getAllPIDs(pids, maxCount);
    
    for(unsigned i = 0; i < countPr; ++i)
    {
        char str[256];
        trace(StrValueUInt(str, "owner PID", pids[i].th32ProcessID));
        trace(StrValueUInt(str, "parent PID", pids[i].th32ParentProcessID));
        trace(StrValueUInt(str, "priority", pids[i].pcPriClassBase));
        trace(StrValueUInt(str, "count of threads", pids[i].cntThreads));
        printThreads(pids[i].th32ProcessID);
        printAllModules(pids[i].th32ProcessID);
        printf("\n******************\n");
    }


    free(pids);
    return 0;
}

