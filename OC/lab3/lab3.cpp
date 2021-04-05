#include <iostream>
#include <Windows.h>

enum Status
{
    RUNNING,
    STOP,
    FINISHING,
    FINISHED
};

int arrSize = 0;
int threadNum = 0;

int* arr = nullptr;
int* threadStatus;

CRITICAL_SECTION criticalSection;

void marker(int indx)
{
    const int num = indx + 1;

    EnterCriticalSection(&criticalSection);
    std::cout << "\nThread num: " << num << " started\n";
    LeaveCriticalSection(&criticalSection);

    int idx = num - 1;
    srand(idx + 1);

    while (true)
    {
        int markElement = 0;
        while (threadStatus[idx] == RUNNING)
        {
            int digit = rand();
            digit %= arrSize;

            Sleep(1);

            EnterCriticalSection(&criticalSection);
            int arrValue = arr[digit];

            if (arrValue == 0)
            {
                Sleep(5);
                markElement++;
                arr[digit] = idx + 1;
                Sleep(5);
            }

            LeaveCriticalSection(&criticalSection);

            if (arrValue)
            {
                std::cout << "\nThread: " << idx + 1 << "\nNumber of marked elements = " << markElement << "\nDigit that couldn't mark: " << digit << "\n";
                threadStatus[idx] = STOP;
                break;
            }
        }

        if (threadStatus[idx] == FINISHING)
        {
            EnterCriticalSection(&criticalSection);
            for (int i = 0; i < arrSize; ++i)
            {
                if (arr[i] == idx + 1)
                {
                    arr[i] = 0;
                }
            }
            LeaveCriticalSection(&criticalSection);

            threadStatus[idx] = FINISHED;
            break;
        }
    }

    EnterCriticalSection(&criticalSection);
    Sleep(1);
    std::cout << "\nThread num: " << num << " killed\n";
    LeaveCriticalSection(&criticalSection);
}

bool checkThreads()
{
    for (int i = 0; i < threadNum; ++i)
    {
        Sleep(1);
        if (threadStatus[i] == RUNNING){
            return false;
        }
    }

    return true;
}

DWORD WINAPI thread_marker(LPVOID p)
{
    marker(reinterpret_cast<int>(p));
    return 0;
}

int main()
{
    InitializeCriticalSection(&criticalSection);

    std::cout << "Enter size of array: ";
    std::cin >> arrSize;

    arr = new int[arrSize] {0};

    std::cout << "\nEnter number of threads: ";
    std::cin >> threadNum;

    HANDLE* hThreadArray = new HANDLE[threadNum];
    threadStatus = new int[threadNum];

    for (int i = 0; i < threadNum; ++i)
    {
        threadStatus[i] = STOP;

        hThreadArray[i] = CreateThread(
            nullptr,
            0,
            thread_marker,
            LPVOID(i),
            0,
            nullptr
        );
    }

    for (int i = 0; i < threadNum; ++i)
    {
        threadStatus[i] = RUNNING;
    }

    while (true)
    {
        while(checkThreads() != true) { }

        std::cout << "\nArray = { ";

        for (int i = 0; i < arrSize; ++i)
        {
            std::cout << arr[i] << " ";
        }

        int idx = 0;
        std::cout << " }\n\nEnter thu number of thread to finish it: ";
        std::cin >> idx;
        Sleep(1);

        threadStatus[idx - 1] = FINISHING;

        while(threadStatus[idx-1] != FINISHING) { }

        std::cout << "\nChanged array = { ";
        
        for (int i = 0; i < arrSize; ++i)
        {
            std::cout << arr[i] << " ";
        }

        std::cout << " }\n";
        Sleep(1);

        for (int i = 0; i < threadNum; ++i)
        {
            if (threadStatus[i] == STOP) {
                threadStatus[i] = RUNNING;
            }
        }

        bool finished = true;

        for (int i = 0; i < threadNum; ++i)
        {
            Sleep(1);
            if (threadStatus[i] != FINISHED)
            {
                finished = false;
                break;
            }
        }

        if(finished){
            break;
        }
    }

    DeleteCriticalSection(&criticalSection);

    delete[] arr;
}
