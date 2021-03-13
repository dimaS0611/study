#include <iostream>
#include <Windows.h>
#include <string>

HANDLE wait_Execute(const std::string& cmdLine, bool wait)
{
    int flags = 0;

    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };

    std::wstring wcmdLine(cmdLine.begin(), cmdLine.end());

    if (!CreateProcessW(nullptr, // имя исполняемого модуля
        (WCHAR*)wcmdLine.data(), // командная строка 
        nullptr,                // защита процесса
        nullptr,                // защита потока
        false,                  // дескриптор параметра наследования
        flags,                 // флажки создания
        nullptr,               // новый блок конфигурации
        nullptr,                // имя текущего каталога
        &si,                    // информация предустановки
        &pi))                   // информация о процессе
        return 0;

    if (wait)
    {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        return 0;
    }

    return pi.hProcess;
}

int main()
{
    std::string filename_bin;
    std::cout << "Enter the name of the binary file: ";
    std::cin >> filename_bin;

    int records = 0;    
    std::cout << "Enter the number of records: ";
    std::cin >> records;

    std::cout << "\n-----------------------------------------------------------\n";

    std::string createrCmdLine = "Creator.exe " + filename_bin + " " + std::to_string(records);
    wait_Execute(createrCmdLine, 1);

    std::cout << "\n-----------------------------------------------------------\n";

    std::string filename_txt;
    std::cout << "Enter the name of the text file: ";
    std::cin >> filename_txt;

    double salary;
    std::cout << "Enter an hour's payment: ";
    std::cin >> salary;

    std::cout << "\n-----------------------------------------------------------\n";

    std::string reporterCmdLine = "Reporter.exe " + filename_bin + " " + filename_txt + " " + std::to_string(salary);
    wait_Execute(reporterCmdLine, 1);

    std::cout << "\n-----------------------------------------------------------\n";

    return 0;
}
