#include <string.h>
#include <windows.h>

extern __declspec(dllexport)
BOOL get_author(char* Str, int maxLen, DWORD* pBytesWritten)
{
    strncpy_s(Str, maxLen, "\nI'm Dzmitry Semianovich 13gr.\n", maxLen);
    if (pBytesWritten)
        *pBytesWritten = strlen(Str);
    return TRUE;
}

extern __declspec(dllexport)
BOOL get_description(char* Str, int maxLen, DWORD* pBytesWritten)
{
    strncpy_s(Str, maxLen, "description2: Show system info\n", maxLen);
    if (pBytesWritten)
        *pBytesWritten = strlen(Str);
    return TRUE;
}

extern __declspec(dllexport)
void exec()
{
    system("msinfo32");
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // ���������� ������ DLL
    DWORD fdwReason,     // ������� ������ �������
    LPVOID lpvReserved   // �����������������
)
{
    return TRUE;
}
