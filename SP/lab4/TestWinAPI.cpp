// TestWinAPI.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "TestWinAPI.h"

#include <tlhelp32.h>
#include <malloc.h>
#include <conio.h>
#include <stdio.h>
#include <wingdi.h>

// ===================================================================================
struct Canvas
{
    HDC hdc;
    int line;
};

void trace(struct Canvas* cv, const char* msg)
{
    TextOutA(cv->hdc, 8, cv->line * 16, msg, strlen(msg));
    cv->line++;
}

void traceW(struct Canvas* cv, const wchar_t* msg)
{
    TextOutW(cv->hdc, 8, cv->line * 16, msg, wcslen(msg));
    cv->line++;
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

void printThreads(struct Canvas* cv, DWORD pid)
{
#define MAX_COUNT 32
    THREADENTRY32 ths[MAX_COUNT];

    unsigned int count = getAllThreads(pid, ths, MAX_COUNT);

    for (unsigned i = 0; i < count; ++i)
    {
        char str[256];
        sprintf_s(str, 256, "thread ID=%d priority=%d", ths[i].th32ThreadID, ths[i].tpBasePri);
        trace(cv, str);
    }
}

void printAllModules(struct Canvas* cv, DWORD pid)
{
    unsigned count = getAllModules(pid, NULL, 0);

    MODULEENTRY32* mdl = (MODULEENTRY32*)malloc(count * sizeof(MODULEENTRY32));

    unsigned countMd = getAllModules(pid, mdl, count);

    for (unsigned i = 0; i < count; ++i)
    {
        char str[256];
        printf("\n\path: ");
        traceW(cv, mdl[i].szExePath);
        trace(cv, StrValueUInt(str, "count of modules", mdl[i].GlblcntUsage));
        trace(cv, StrValueUInt(str, "size", mdl[i].modBaseSize));
    }
}

void printAllProcesses(struct Canvas* cv)
{
    unsigned maxCount = getAllPIDs(NULL, 0);

    if (!maxCount)
    {
        trace(cv, "PIDS is empty.");
    }

    maxCount += 10;
    PROCESSENTRY32* pids = (PROCESSENTRY32*)malloc(maxCount * sizeof(PROCESSENTRY32));

    unsigned countPr = getAllPIDs(pids, maxCount);

    for (unsigned i = 0; i < countPr; ++i)
    {
        char str[256];
        trace(cv, StrValueUInt(str, "owner PID", pids[i].th32ProcessID));
        trace(cv, StrValueUInt(str, "parent PID", pids[i].th32ParentProcessID));
        trace(cv, StrValueUInt(str, "priority", pids[i].pcPriClassBase));
        trace(cv, StrValueUInt(str, "count of threads", pids[i].cntThreads));
        printThreads(cv, pids[i].th32ProcessID);
        printAllModules(cv, pids[i].th32ProcessID);
    }


    free(pids);
}

// ===================================================================================


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TESTWINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTWINAPI));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTWINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TESTWINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(
       szWindowClass,
       szTitle,
       WS_OVERLAPPEDWINDOW | WS_VSCROLL,
       CW_USEDEFAULT,   // x
       0,               // y

       CW_USEDEFAULT,   // w
       0,            // h
       nullptr,
       nullptr, 
       hInstance, 
       nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            Canvas cv;

            PAINTSTRUCT ps;
            cv.hdc = BeginPaint(hWnd, &ps);
            cv.line = 0;

            SetTextColor(cv.hdc, RGB(0, 0, 255));
            SetBkColor(cv.hdc, RGB(255, 255, 255));

            printAllProcesses(&cv);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
