#include <iostream>
#include <Windows.h>

struct Data {
    int _size = 0;
    double* _data = nullptr;
    int _minIdx = 0;
    int _maxIdx = 0;
    double _average = 0.0;

    explicit Data(int size)
        : _size(size)
        , _data(new double[_size])
    {
    }

    ~Data()
    {
        delete[] _data;
    }
};

double get_average(double* data, int n)
{
    double sum = 0;
    for (int i = 0; i < n; ++i)
    {
        sum += data[i];
        Sleep(12);
    }

    return sum / static_cast<double>(n);
}

std::pair<int,int> get_min_max(double* data, int n)
{
    std::pair<int, int> result = { 0,0 };

    double min = data[0], max = data[0];

    for (int i = 0; i < n; ++i)
    {
        if (data[i] > max)
        {
            max = data[i];
            result.second = i;
        }
        Sleep(7);

        if(data[i] < min)
        {
            min = data[i];
            result.first = i;
        }
        Sleep(7);
    }

    return result;
}

DWORD WINAPI ThreadFuncMinMax(LPVOID p)
{
    Data* data = (Data*)p;
    std::pair<int, int> idx = get_min_max(data->_data, data->_size);

    data->_maxIdx = idx.second;
    data->_minIdx = idx.first;

    return 0;
}

DWORD WINAPI ThreadFuncAverage(LPVOID p)
{
    Data* data = (Data*)p;
    data->_average = get_average(data->_data, data->_size);

    return 0;
}

int main()
{
    int size = 0;
    std::cout << "Enter size of array: ";
    std::cin >> size;

    Data data(size);

    for (int i = 0; i < size; ++i)
    {
        int num;
        std::cout << "Enter " << i << " ellement of array: ";
        std::cin >> num;
        data._data[i] = num;
    }

    HANDLE hThreadArray[2];
    
    hThreadArray[0] = CreateThread(
        nullptr,
        0,
        ThreadFuncAverage,
        &data,
        0,
        nullptr
    );
    
    hThreadArray[1] = CreateThread(
        nullptr,
        0,
        ThreadFuncMinMax,
        &data,
        0,
        nullptr
    );

    WaitForMultipleObjects(2, hThreadArray, TRUE, INFINITE);
    
    for (int i = 0; i < 2; ++i)
    {
        CloseHandle(hThreadArray[i]);
    }

    data._data[data._minIdx] = data._average;
    data._data[data._maxIdx] = data._average;


    for (int i = 0; i < size; ++i)
    {
        std::cout << (int)data._data[i] << " ";
    }
}
